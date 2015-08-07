#!/bin/bash
#
# 簡単なテスト
#

QUOTES="./quotes/yasuna-quotes"
ARGS=("$1" "--file" "$QUOTES")

function random_test() {
	local N=16
	local Q=512

	echo "random_test(): N = $N, Q = $Q"
	for ((i = 0; i < $N; i++)); do
		echo -n "loop $i: "
		for ((j = 1; j <= $Q; j++)); do
			${ARGS[@]}	| \
				grep null && \
				echo "$j" && \
				exit 1
		done
		echo "done."
	done

	return
}

function sequential_test() {
	echo -n "sequential_test(): "

	for ((i = 0; i < `cat $QUOTES | wc -l`; i++)); do
		${ARGS[@]} -n $i >> out.txt
	done

	diff out.txt $QUOTES 
	test $? -ne 0 && \
		rm out.txt && \
		echo "failed" && \
		return;

	rm out.txt
	echo "done"

	return 
}

random_test
echo ""
sequential_test

exit 0
