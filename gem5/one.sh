#!/bin/bash
b=$1; v=$2; n=$3; ic=$4; fc=$5; iu=$6; fpu=$7
d=out/${b}_${v}_${n}_iu${iu}
IU=$iu IU_CYC=$ic FPU=$fpu FPU_CYC=$fc ~/gem5/build/X86/gem5.opt -q -d $d cfg.py ./bin/$b $v $n >/dev/null 2>&1
fp=$(awk '/issuedInstType_0::/{split($1,a,"::"); c=a[2]; if ((c ~ /^Float/ || c ~ /^SimdFloat/) && c !~ /Mem/) s+=$2} END{print s+0}' $d/stats.txt)
echo "$b $v $n iu$iu $ic $fc $(awk '/^system.cpu.numCycles/{print $2}' $d/stats.txt) $fp"
