#!/usr/bin/env bash
# Setup for Ubuntu/WSL.
#   bash setup.sh              native kernels + gem5 kernel binaries (gcc only), installs gem5 build deps
#   WITH_GEM5=1 bash setup.sh  also clones gem5 v25.1.0.1 into ~/gem5 and builds build/X86/gem5.opt
#                              (needs several GB of disk and RAM, and 30-90 min)
set -euo pipefail
cd "$(dirname "$0")"

sudo apt-get update
sudo apt-get install -y build-essential gawk git python3
# Teammate-Nehith-RISCV-gem5/makefile cross compilers
sudo apt-get install -y gcc-riscv64-unknown-elf gcc-riscv64-linux-gnu
# gem5 build dependencies (https://www.gem5.org/documentation/general_docs/building)
sudo apt-get install -y scons python3-dev python3-pip python3-venv python3-pydot m4 pkg-config \
    zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev \
    libboost-all-dev libhdf5-dev libcapstone-dev libpng-dev libelf-dev

# Native kernels (README "Building and running")
( cd "Codes/Factorial programs" && gcc -O2 Factorial_integrated.c -o Factorial_integrated.out -lm )

# Static x86 kernel binaries for the gem5 sweep (gem5/bin/)
( cd gem5 && bash build.sh )

if [ "${WITH_GEM5:-0}" = "1" ]; then
    if [ ! -d "$HOME/gem5/.git" ]; then
        git clone --branch v25.1.0.1 --depth 1 https://github.com/gem5/gem5 "$HOME/gem5"
    fi
    ( cd "$HOME/gem5" && scons build/X86/gem5.opt -j"$(nproc)" )
    echo "gem5 built: $HOME/gem5/build/X86/gem5.opt"
else
    echo "gem5 not built. To build it: WITH_GEM5=1 bash setup.sh"
fi
echo "Run native: cd 'Codes/Factorial programs' && echo 20 | ./Factorial_integrated.out"
echo "Run gem5 sweep (after the gem5 build): cd gem5 && xargs -P4 -L1 ./one.sh < jobs.txt"
