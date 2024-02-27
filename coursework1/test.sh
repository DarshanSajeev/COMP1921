#!/bin/bash

# remove read permissions from this file
chmod -r data/bad_perms.csv

echo -e "\nArgument Testing:\n"

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
./skeleton 5x5.txt 15x7.txt > tmp
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
timeout 0.2s ./skeleton bad_perms.txt > tmp
if grep -q "Error: Bad filename" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing too many columns - "
timeout 0.2s ./skeleton invalidMazes/inc_columns.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing too many rows - "
timeout 0.2s ./skeleton invalidMazes/inc_rows.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "No 'E' in file - "
timeout 0.2s ./skeleton invalidMazes/NoE.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "No 'S' in file - "
timeout 0.2s ./skeleton invalidMazes/NoS.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Too many 'S' in file - "
timeout 0.2s ./skeleton invalidMazes/TooManyS.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Too many 'E' in file - "
timeout 0.2s ./skeleton invalidMazes/TooManyE.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "No 'S' or 'E' in file - "
timeout 0.2s ./skeleton invalidMazes/NoSorE.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Incorrect characters in maze - "
timeout 0.2s ./skeleton invalidMazes/wrongchar.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Too small maze - "
timeout 0.2s ./skeleton invalidMazes/TooSmall.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Too big maze - "
timeout 0.2s ./skeleton invalidMazes/TooHigh.txt > tmp
if grep -q "Error: Maze file does not have correct format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "\nTesting good files: \n"

echo -n "Testing good file 1 - "
timeout 0.2s ./skeleton validMazes/5x5.txt > tmp
if grep -q "Error: Maze loaded successfully" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing good file 2 - "
timeout 0.2s ./skeleton validMazes/15x7.txt > tmp
if grep -q "Error: Maze loaded successfully" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing good file 3 - "
timeout 0.2s ./skeleton validMazes/20x7.txt > tmp
if grep -q "Error: Maze loaded successfully" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing good file 4 - "
timeout 0.2s ./skeleton validMazes/100x14.txt > tmp
if grep -q "Error: Maze loaded successfully" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\nTesting Movement Inputs\n"

echo -n "Checking 'W' input - "
./skeleton validMazes/100x14.txt < testScripts/W.txt > tmp
if cmp -s tmp.txt testScripts/100x14_up.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'A' input - "
./skeleton validMazes/15x7.txt < testScripts/A.txt > tmp
if cmp -s tmp.txt testScripts/15x7_left.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'S' input - "
./skeleton validMazes/5x5.txt < testScripts/S.txt > tmp
if cmp -s tmp.txt testScripts/5x5_down.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'D' input - "
./skeleton validMazes/20x7.txt < testScripts/D.txt > tmp
if cmp -s tmp.txt testScripts/20x7_right.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'w' input - "
./skeleton validMazes/100x14.txt < testScripts/wLower.txt > tmp
if cmp -s tmp.txt testScripts/100x14_up.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'a' input - "
./skeleton validMazes/15x7.txt < testScripts/aLower.txt > tmp
if cmp -s tmp.txt testScripts/15x7_left.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 's' input - "
./skeleton validMazes/5x5.txt < testScripts/sLower.txt > tmp
if cmp -s tmp.txt testScripts/5x5_down.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'd' input - "
./skeleton validMazes/20x7.txt < testScripts/dLower.txt > tmp
if cmp -s tmp.txt testScripts/20x7_right.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'W' input - "
./skeleton validMazes/100x14.txt < testScripts/W.txt > tmp
if cmp -s tmp.txt testScripts/100x14_up.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'A' input - "
./skeleton validMazes/15x7.txt < testScripts/A.txt > tmp
if cmp -s tmp.txt testScripts/15x7_left.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking 'S' input - "
./skeleton validMazes/5x5.txt < testScripts/S.txt > tmp
if cmp -s tmp.txt testScripts/5x5_down.txt;
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Checking incorrect movement input - "
./skeleton validMazes/20x7.txt < testScripts/IncorrectMovement.txt > tmp
if grep -q "Error: Incorrect Input";
then
    echo "PASS"
else
    echo "FAIL"
fi 

echo -n "Testing 2 inputs - "
./skeleton 5x5.txt < D.txt W.txt > tmp
if grep -q "Error: IncorrectInput" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing a 2 character string input - "
./skeleton 5x5.txt < testScripts/IncorrectInput > tmp
if grep -q "Error: Incorrect Input" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi