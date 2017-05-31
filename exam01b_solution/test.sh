#!/bin/bash

COUNT=30

make

./peter.out $COUNT &
PETER_PID=$!

sleep 1s

for (( i=0; i<=$COUNT-1; i++ )); do ./student.out $i & done

wait $PETER_PID
make clean
