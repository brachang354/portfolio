#!/bin/bash

#Group members: Bradley Chang, Gustavo Cotem Lopez, Harrison Moore, Huan Nguyen, Nick Phua

ENDVAL=25
BEGVAL=1
VERBOSE=0
#num = -1

function show_help()
{
	echo "./run_test.bash [-h] [-b <begin>] [-e <end>] [-v]"
	echo "Today's date is $(date)"
	exit 0
}

function exit_value()
{
		#./bar $num >> /dev/null 2>&1
		
		exit_status=$1
		if  [ ${exit_status} -eq 0  ] 
		then
			echo "$num  was successful"
		#elif  [${exit_status} -ne 0] #&& [${verbose} -eq 1]
		elif ${verbose}
		then
			echo -n "$num failed with exit value "
			echo -n $exit_status
		fi
}

while getopts "he:b:v" OPT
do
	case "${OPT}" in
		h)
			show_help
			;;
		e)
			ENDVAL=${OPTARG}
			;;
		b)
			BEGVAL=${OPTARG}
			;;
		v)
			VERBOSE=1
			;;
	esac
done


for ((num = BEGVAL; num <= ENDVAL; num++ ))
	do
		timeout -s SIGKILL 1s ./bar $num > /dev/null
		EV=$?
		exit_value $EV
	done
