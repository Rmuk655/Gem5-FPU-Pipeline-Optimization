#!/bin/bash
b=$1; v=$2; n=$3; d=out/${b}_${v}_${n}
~/gem5/build/X86/gem5.opt -q -d $d cfg.py ./$b $v $n >/dev/null 2>&1
fp=$(awk '/issuedInstType_0::/{split($1,a,"::"); c=a[2]; if ((c ~ /^Float/ || c ~ /^SimdFloat/) && c !~ /Mem/ && c !~ /Load|Store/) s+=$2} END{print s+0}' $d/stats.txt)
echo "$b $v $n $(grep -E '^simInsts' $d/stats.txt | awk '{print $2}') $(grep -E '^system.cpu.numCycles' $d/stats.txt | awk '{print $2}') $fp"
