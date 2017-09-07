#!/bin/bash
#
# 簡易カバレッジ測定
#

YASUNA="./yasuna"

function test0() {
    ${YASUNA} --version                                 && \
    ${YASUNA} --help                                    && \
    ${YASUNA} -n STR                                    || \
    ${YASUNA} -f                                        || \
    ${YASUNA} -f ENOENT                                 || \
    ${YASUNA} -f ../testsuite/empty                     || \
    ${YASUNA} -f /var/log/syslog                        || \
    ${YASUNA} -f ../src                                 || \
    ${YASUNA}

    return $?
}

function test1() {
    local QUOTES="../quotes/yasuna-quotes"

    ${YASUNA} -f ${QUOTES}                              && \
    ${YASUNA} -f ${QUOTES} -n 32                        && \
    ${YASUNA} -f ${QUOTES} -n 1000000                   && \
    ${YASUNA} -f ${QUOTES} --speaker "やすな"           && \
    ${YASUNA} -f ${QUOTES} --speaker "やすな" -n 32     && \
    ${YASUNA} -f ${QUOTES} --speaker "やすな" --list    && \
    ${YASUNA} -f ${QUOTES} --speaker "ソーニャ"         || \
    ${YASUNA} -f ${QUOTES} --speaker "あぎり" -n 32     || \
    ${YASUNA} -f ${QUOTES} --speaker "没キャラ" --list  || \
    ${YASUNA} -f ${QUOTES} --list

    return $?
}

function test2() {
    local QUOTES="../quotes/trio_the_techno.ltsv"

    ${YASUNA} -f ${QUOTES}                              && \
    ${YASUNA} -f ${QUOTES} -n 32                        && \
    ${YASUNA} -f ${QUOTES} --speaker "細野晴臣"         && \
    ${YASUNA} -f ${QUOTES} --speaker "坂本龍一" -n 8    && \
    ${YASUNA} -f ${QUOTES} --speaker "高橋幸宏" --list  && \
    ${YASUNA} -f ${QUOTES} --list

    return $?
}

function test3() {
    local QUOTES="../quotes/old-yasuna-quotes"

    ${YASUNA} -f ${QUOTES}                              && \
    ${YASUNA} -f ${QUOTES} -n 32                        && \
    ${YASUNA} -f ${QUOTES} --speaker "細野晴臣"         || \
    ${YASUNA} -f ${QUOTES} --speaker "坂本龍一" -n 8    || \
    ${YASUNA} -f ${QUOTES} --speaker "高橋幸宏" --list  || \
    ${YASUNA} -f ${QUOTES} --list

    return $?
}

#(test0 && test1 && test2 && test3) > /dev/null 2>&1
test0 && test1 && test2 && test3
