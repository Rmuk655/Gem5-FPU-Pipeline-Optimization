#!/bin/bash
# Builds the kernels used in the gem5 sweep (run from this folder after cloning the repo root one level up).
# macros IU_cycles/FPU_cycles are rewritten in a copy; harness calls the unmodified kernel functions.
F="../Codes/Factorial programs/Factorial_integrated.c"; C="../Codes/Integer Convolutions/Convolutions_Integrated.c"
M="../Codes/Matrix Multiplication programs/Matrix_Multiplication_Integrated.c"
mkdir -p src bin out
for p in "1 3" "2 4" "3 5"; do set -- $p
  sed "s/^#define IU_cycles .*/#define IU_cycles $1/; s/^#define FPU_cycles .*/#define FPU_cycles $2/" "$F" > src/fact_$1$2.c
  sed "s/^#define IU_cycles .*/#define IU_cycles $1/; s/^#define FPU_cycles .*/#define FPU_cycles $2/" "$C" > src/conv_$1$2.c
  for O in 0 2 3; do
    gcc -O$O -static -w -DSRC="\"src/fact_$1$2.c\"" h_fact.c -o bin/fact_$1$2_O$O -lm
    gcc -O$O -static -w -DSRC="\"src/conv_$1$2.c\"" -DDIM=500 -DDIM_M=500 -DDIM_N=500 h_conv.c -o bin/conv_$1$2_O$O -lm
  done
done
for O in 2 3; do gcc -O$O -static -w -DSRC="\"$M\"" -DDIM=32 h_mat.c -o bin/mat_13_O$O -lm; done
# jobs.txt columns: binary variant iterations IU_cycles FPU_cycles IU_count FPU_count ; run: xargs -P4 -L1 ./one.sh < jobs.txt
