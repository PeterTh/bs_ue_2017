# Exercise Sheet 2

In this exercise you will be asked to work with a shell. The idea is to get familiar with some Unix commands and bash programming.

## Task 1

Consider the following scripts. Explain what means each line within these scripts. Explain what happens when you execute these scripts with and without input arguments. 

```bash
#!/bin/bash
# Script 1
#
for FN in "$@"
do
chmod 0750 "$FN"
done
```

```bash
#!/bin/bash 
## Script 2
##
if (( $# < 3 ))
then
printf "%b" "Error. Not enough arguments.\n" >&2
printf "%b" "usage: myscript file1 op file2\n" >&2
exit 1
elif (( $# > 3 ))
then 
printf "%b" "Error. Too many arguments.\n" >&2
printf "%b" "usage: myscript file1 op file2\n" >&2
exit 2
else
printf "%b" "Argument count correct. Proceeding...\n" 
fi
```

```bash
#!/bin/bash
INFILE=$1
OUTFILE=$2
if [ -e "$INFILE" ]
then
if [ -w "$OUTFILE" ]
then
cat "$INFILE" >> "$OUTFILE"
else
echo "can not write to $OUTFILE"
fi
else
echo "can not read from $INFILE"
fi

```

## Task 2
Write a script *my_back_up.sh* to perform a back up of the current directory into a given folder. The script receives a single parameter which is the path of the folder where the back up is to be stored. If the back up folder already exists then a file needs to be copy if and only if it does not exist within the back up folder or if it is newer than the existing one in the back up folder. The script will be used as follows

```bash
./my_back_up.sh backUpFolder #creates a back up of . into backUpFolder
```
