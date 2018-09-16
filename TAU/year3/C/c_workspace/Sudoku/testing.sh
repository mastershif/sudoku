#!/usr/bin/env bash
#set -x

for i in tdd/test5;
do
    echo $i
    echo '========='
    cat $i
    echo ''
    echo '< is what you print'
    echo '> is what is expected'
    echo ''
    res=$(echo $i | sed -e 's/test/res/g');
    cat $i | ./cmake-build-debug/Sudoku | diff - $res
    echo '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
    echo '=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='
    echo '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
done