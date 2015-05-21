#!/bin/bash
#
# 簡単なテスト
#

ARGS=("./yasuna" "--file" "quotes/yasuna-quotes")
N=32
Q=6144

for ((i = 0; i < $N; i++)); do
    echo -n "loop $i: "
    for ((j = 1; j <= $Q; j++)); do
        ${ARGS[@]} | \
            grep null && \
            echo "$j" && \
            exit 1
    done
    echo "done."
done

exit 0
