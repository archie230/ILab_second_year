#! /bin/bash

cd data
echo > ../test_log

for file in *;
do
  ANSW=$(./../../interarea < $file)
  EXPECT=$(cat ../results/${file%.dat}.res)
  if [[ $ANSW != $EXPECT ]]; then
    STATUS="FAILED"
  else
    STATUS="OK"
  fi
  echo "TEST ${file%.dat} $STATUS : answ = $ANSW  expected = $EXPECT" >> ../test_log
done