#!/bin/bash

# remove read permissions from this file
chmod -r data/bad_perms.csv

echo -e "\n\n Argument Testing:"

#Testing no file inputted
echo -n "Testing no arguments - "

./skeleton > tmp

# code based from week 2 lab
if grep -q "Usage: skeleton.c <filename>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# Testing 2 files inputted
# code based from week 2 lab
echo -n "Testing 2 arguments - "
./skeleton x x > tmp
if grep -q "Usage: studentData <filename>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "\nFile testing"

echo -n "Bad file name testing - "

./skeleton badfile.txt > tmp
if grep -q "Error: Bad filename" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

# code based from week 2 lab
echo -n "Testing bad permissions - "
timeout 0.2s ./skselton bad_perms.txt > tmp
if grep -q "Error: Bad filename" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing too many columns - "
./
if grep "Error: Maze file does not have correct format";
then
    echo "PASS"
else
    echo "FAIL"
fi



