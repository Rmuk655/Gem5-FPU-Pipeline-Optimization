# Teammate programs (Maka Nehith) and final report

Copied unchanged from https://github.com/MakaNehith/Speeding-up-Integer-Programs-with-FPUs (group project; `FinalReport.pdf` lists both authors). Matrix multiplication and minimum-element are his; factorial and convolution here are the same kernels as in `Codes/` with a different test harness.

His `makefile` targets RISC-V gem5 (`riscv64-*-gcc`, `se.py --cpu-type=O3CPU --caches --l2cache`) and expects a `gem5/` checkout that is not included. The numbers in his report come from that setup and were not re-run here.

## What was re-checked on X86 gem5 (O3, default FU pool as in his Table 1)

gem5's default O3 FU pool (`DEFAULT_FU=1` in `../gem5/cfg.py`); `gcc -O3 -static`; one run each; my 32 kB L1 / 256 kB L2 rather than his `--caches --l2cache` defaults.

| Kernel | Variant | Cycles | Output |
|---|---|---|---|
| matmul 130x130 | swapped loops (int) | 6.82M | matches int |
| matmul 130x130 | complete int | 7.66M | matches |
| matmul 130x130 | swapped + unroll 10 (int) | 7.75M | matches |
| matmul 130x130 | swapped + unroll 10, 3 of 10 in float | 9.47M | **differs** |
| minElement 100k | Int / IntUnroll / FloatUnroll (whole program, init included: 9.93M) | 10.75M / 10.76M / 10.65M | all 64 |

- The float matmul variant is slower on this model and its output differs from the int versions: inputs are full-range `rand()`, so int accumulation overflows and float products lose precision. The report's Limitations (valid below 2^24) is not respected by that test.
- The only improvement is minElement FloatUnroll, about 1% of whole-program cycles (about 14% after subtracting initialisation). It issues about 40k FP ops (about 1% FPU utilisation), and integer ALUs were not saturated, so this does not show the FPU relieving a bottleneck; layout/branch effects were not ruled out.
- Convolution with `rand()` inputs overflows the int baseline (undefined behaviour); float/double results differ from int. With inputs masked to 8 bits all three variants match. Factorial n=20 is correct for all variants.
- In his factorial and convolution harnesses the factorial "time" divides each trial by `i`, so the printed value is not an average.
