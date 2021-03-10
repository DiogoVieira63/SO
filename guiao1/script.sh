#!/bin/bash

for ((i = 0; i < $1; i++))
do
    IDADE=$(((RANDOM %100) +1 ))
    ./pessoas -i Pessoa${i} $IDADE
done