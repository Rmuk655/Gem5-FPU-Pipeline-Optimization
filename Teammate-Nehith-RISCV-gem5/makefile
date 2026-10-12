GEM5DIR = gem5
SRCDIR  = src/minElement
ASMDIR  = asm
BINDIR  = bin
STATSDIR = stats

# COMPILER = riscv64-linux-gnu-gcc
COMPILER = riscv64-unknown-elf-gcc
OPTFLAGS = -O3 --static

GEM5_EXEC = $(GEM5DIR)/build/RISCV/gem5.opt
SIM_SCRIPT = $(GEM5DIR)/configs/deprecated/example/se.py

OOOFLAGS = --cpu-type=O3CPU --caches --l2cache

SRCFILES  = $(wildcard $(SRCDIR)/*.c)
ASMFILES  = $(patsubst $(SRCDIR)/%.c, $(ASMDIR)/%.s, $(SRCFILES))
BINFILES  = $(patsubst $(ASMDIR)/%.s, $(BINDIR)/%, $(ASMFILES))
STATSFILES = $(patsubst $(BINDIR)/%, $(STATSDIR)/%/stats.txt, $(BINFILES))

o3: $(STATSFILES)

$(ASMDIR)/%.s: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) $(OPTFLAGS) -S $< -o $@

$(BINDIR)/%: $(ASMDIR)/%.s
	@mkdir -p $(@D)
	$(COMPILER) $(OPTFLAGS) $< -o $@

$(STATSDIR)/%/stats.txt: $(BINDIR)/%
	@mkdir -p $(@D)
	$(GEM5_EXEC) --outdir=$(@D) --listener-mode=off $(SIM_SCRIPT) $(OOOFLAGS) -c $<


clean:
	rm -rf $(ASMDIR) $(BINDIR) $(STATSDIR)

.SECONDARY: $(ASMFILES) $(BINFILES)

.PHONY: o3 clean
