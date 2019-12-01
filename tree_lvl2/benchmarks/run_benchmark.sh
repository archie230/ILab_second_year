#! /bin/bash
#
# takes two argument: ($1, $2) <- range where benchmark runs
#
echo > benchmark_log
for((i = $1 ; i <= $2 ; i++)) do
./benchmarks $i >> benchmark_log
echo >> benchmark_log
done