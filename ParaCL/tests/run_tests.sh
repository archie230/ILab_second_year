#!/usr/bin/env bash

# running tests with correct input data
CorDataRange=(001 002 003 004 005 006 007 008 009 010 011 012 013 014)
CorDataPath=correct_data/
CorInputPath=input/
CorExpPath=expect/

BadDataRange=(001 002 003 004 005 006 007)
BadDataPath=bad_data/
BadOutPath=bad_outputs/

ERR_COUNTER=0

echo -e "\t[CORRECT DATA TESTS SET]" > test_log

for i in ${CorDataRange[@]}
do
    echo "running $i test"
    ANSW=$(valgrind --log-file=va_logs/va_logCorData${i}.txt ./../bin/interpreter ${CorDataPath}${i}.cl < ${CorInputPath}${i}.in)
    EXPECT=$(cat ${CorExpPath}${i}.txt)
    if [[ $ANSW != $EXPECT ]]; then
       STATUS="FAILED"
       ERR_COUNTER+=1
    else
      STATUS="OK"
    fi

    echo "[TEST ${i} $STATUS]: " >> test_log
    echo "answ:" >> test_log
    echo $ANSW >> test_log
    echo "expected:" >> test_log
    echo "$EXPECT" >> test_log
done

echo "[BAD DATA TESTS SET]" >> test_log

for i in ${BadDataRange[@]}
do
   echo "running $i test"
   valgrind --log-file=va_logs/va_logBadData${i}.txt ./../bin/interpreter ${BadDataPath}${i}.cl 2> ${BadOutPath}${i}.txt
   ANSW=$(cat ${BadOutPath}${i}.txt)
   if [[ -z $ANSW ]]; then
       STATUS="FAILED"
       ERR_COUNTER+=1
   else
       STATUS="OK"
   fi

   echo "[TEST ${i} $STATUS]: " >> test_log
done

if [[ $ERR_COUNTER == 0 ]]; then
  echo "ALL TESTS PASSED"
else
  echo "$ERR_COUNTER TESTS FAILED"
fi

read -n 1 -p "Show test_log ? [y/n]" Show

if [[ $Show == "y" ]]; then
  cat test_log
fi
