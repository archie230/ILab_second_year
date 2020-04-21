#!/usr/bin/env bash

DataRange=(001 002 003 004 005)
InputPath=input/
ExpPath=expect/



ERR_COUNTER=0

echo "=====TESTS=====" > test_log
for i in ${DataRange[@]}
do
    echo "running $i test"
    ANSW=$(./../bin/circalc ${InputPath}${i}.in)
    EXPECT=$(cat ${ExpPath}${i}.out)
    if [[ $ANSW != $EXPECT ]]; then
       STATUS="FAILED"
       ERR_COUNTER+=1
    else
       STATUS="OK"
    fi
    echo "[TEST ${i} $STATUS] " >> test_log
    echo "ANSW:" >> test_log
    echo "$ANSW" >> test_log
    echo "EXPECTED:" >> test_log
    echo "$EXPECT" >> test_log
    echo >> test_log
done