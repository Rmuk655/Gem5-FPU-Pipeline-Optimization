import sys, os
import m5
from m5.objects import *

IU_N, IU_L = int(os.environ.get("IU", 4)), int(os.environ.get("IU_CYC", 1))
FP_N, FP_L = int(os.environ.get("FPU", 2)), int(os.environ.get("FPU_CYC", 3))
binary, args = sys.argv[1], sys.argv[2:]

from m5.objects.FuncUnitConfig import *
_fp = [o for fu in (FP_ALU, FP_MultDiv, SIMD_Unit) for o in fu.opList]
def _lat(n):
    return 12 if "Div" in n else 24 if "Sqrt" in n else FP_L
class MyIntALU(FUDesc):
    opList = [OpDesc(opClass="IntAlu", opLat=IU_L)]
    count = IU_N
class MyIntMultDiv(FUDesc):
    opList = [OpDesc(opClass="IntMult", opLat=IU_L), OpDesc(opClass="IntDiv", opLat=20, pipelined=False)]
    count = IU_N
class MyFPU(FUDesc):
    opList = [OpDesc(opClass=str(o.opClass), opLat=_lat(str(o.opClass)),
                     pipelined=not any(k in str(o.opClass) for k in ("Div", "Sqrt"))) for o in _fp]
    count = FP_N
class MyPool(FUPool):
    FUList = [MyIntALU(), MyIntMultDiv(), MyFPU(), ReadPort(), Matrix_Unit(),
              System_Unit(), PredALU(), WritePort(), RdWrPort()]
pool = DefaultFUPool() if os.environ.get("DEFAULT_FU") else MyPool()
print("FUPOOL: IU", IU_N, IU_L, "FPU", FP_N, FP_L, "fp op classes", len(MyFPU.opList))

class L1(Cache):
    size = "32kB"; assoc = 8; tag_latency = 2; data_latency = 2
    response_latency = 2; mshrs = 8; tgts_per_mshr = 16
class L2(Cache):
    size = "256kB"; assoc = 8; tag_latency = 10; data_latency = 10
    response_latency = 10; mshrs = 20; tgts_per_mshr = 12

system = System()
system.clk_domain = SrcClockDomain(clock="2GHz", voltage_domain=VoltageDomain())
system.mem_mode = "timing"
system.mem_ranges = [AddrRange("512MB")]
system.cpu = X86O3CPU(fuPool=pool)
system.membus = SystemXBar()
system.l2bus = L2XBar()
system.cpu.icache = L1(); system.cpu.dcache = L1(); system.l2 = L2()
system.cpu.icache.cpu_side = system.cpu.icache_port
system.cpu.dcache.cpu_side = system.cpu.dcache_port
system.cpu.icache.mem_side = system.l2bus.cpu_side_ports
system.cpu.dcache.mem_side = system.l2bus.cpu_side_ports
system.l2.cpu_side = system.l2bus.mem_side_ports
system.l2.mem_side = system.membus.cpu_side_ports
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.mem_side_ports
system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports
system.mem_ctrl = MemCtrl(dram=DDR3_1600_8x8(range=system.mem_ranges[0]))
system.mem_ctrl.port = system.membus.mem_side_ports
system.system_port = system.membus.cpu_side_ports
system.workload = SEWorkload.init_compatible(binary)
proc = Process(cmd=[binary] + args)
system.cpu.workload = proc
system.cpu.createThreads()
root = Root(full_system=False, system=system)
m5.instantiate()
ev = m5.simulate()
print("EXIT:", ev.getCause())
