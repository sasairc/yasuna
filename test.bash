#
# かんたんなてすと
#

export QUOTES="./quotes/yasuna-quotes"
export ARGS=("$1" "--file" "$QUOTES")

function cleanup() {
    echo "*** cleanup directory ***"
    make clean && \
        rm -r "$1"

    return $?
}

function install_all() {
    echo "*** target install-all ***"
    make CC="$1" PREFIX="$2" install && \
        tree "$2"

    return $?
}

function install_bin() {
    echo "*** target install-bin ***"
    make CC="$1" PREFIX="$2" install-bin && \
        tree "$2"

    return $?
}

function install_quotes() {
    echo "*** target install-quotes ***"
    make CC="$1" PREFIX="$2" install-quotes && \
        tree "$2"

    return $?
}

function install_man() {
    echo "*** target install-man ***"
    make CC="$1" PREFIX="$2" install-man && \
        tree "$2"

    return $?
}

function install_zsh_compdef() {
    echo "*** target install-zsh-compdef ***"
    make CC="$1" PREFIX="$2" install-zsh-compdef && \
        tree "$2"

    return $?
}

function random_test() {
    local QUOTES="$1/share/yasuna/yasuna-quotes"
    local ARGS=("$1/bin/yasuna" "--file" "$QUOTES")

    local N=16
    local Q=512

    echo "random_test(): N = $N, Q = $Q"
    for ((i = 0; i < $N; i++)); do
        echo -n "loop $i: "
        for ((j = 1; j <= $Q; j++)); do
            ${ARGS[@]}  | \
                grep null && \
                echo "$j" && \
                exit 1
        done
        echo "done."
    done

    return 0
}

function sequential_test() {
    local QUOTES="$1/share/yasuna/yasuna-quotes"
    local ARGS=("$1/bin/yasuna" "--file" "$QUOTES")

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

    return 0
}
