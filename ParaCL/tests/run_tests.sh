#!/usr/bin/env bash

# running tests with correct input data
CorDataRange=(001 002 003 004 005 006 007 008 009 010 011 012 013 014)
CorDataPath=correct_data/
CorInputPath=input/
CorExpPath=expect/

BadDataRange=(001 002 003 004 005 006)
BadDataPath=bad_data/
BadOutPath=bad_outputs/

echo "=====CORRECT DATA TESTS=====" > test_log
for i in ${CorDataRange[@]}
do
    ANSW=$(valgrind --log-file=va_logs/va_logCorData${i}.txt ./../bin/interpreter ${CorDataPath}${i}.cl < ${CorInputPath}${i}.in)
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
   valgrind --log-file=va_logs/va_logBadData${i}.txt ./../bin/interpreter ${BadDataPath}${i}.cl 2> ${BadOutPath}${i}.txt
   ANSW=$(echo ${BadOutPath}${i}.txt)
   if [[ -z ANSW ]]; then
       STATUS="FAILED"
   else
       STATUS="OK"
   fi

   echo "TEST ${i} $STATUS" >> test_log
done
