#!/usr/bin/env bash

# running tests with correct input data
CorDataRange=(001 002 003 004 005)
CorDataPath=correct_data/
CorInputPath=input/
CorExpPath=expect/

BadDataRange=(006 007 008 009 010)
BadDataPath=bad_data/
BadOutPath=bad_outputs/

echo "=====CORRECT DATA TESTS=====" > test_log
for i in ${CorDataRange[@]}
do
    ANSW=$(./../bin/interpreter ${CorDataPath}${i}.cl < ${CorInputPath}${i}.in)
    EXPECT=$(cat ${CorExpPath}${i}.txt)
    if [[ $ANSW != $EXPECT ]]; then
       STATUS="FAILED"
    else
       STATUS="OK"
    fi
    echo "TEST ${i} $STATUS : answ = $ANSW  expected = $EXPECT" >> test_log
done

echo "=====BAD DATA TESTS=====" >> test_log

for i in ${BadDataRange[@]}
do
    ./../bin/interpreter ${BadDataPath}${i}.cl 2> ${BadOutPath}${i}.txt
    if [[ ! -s ${BadOutPath}${i}.txt ]]; then
        STATUS="FAILED"
    else
        STATUS="OK"
    fi

    echo "TEST ${i} $STATUS" >> test_log
done