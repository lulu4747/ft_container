#!/bin/bash
CMD_DATE=date

	SEED=$($CMD_DATE +%s);

#	while getopts u:a:f: flag
#	do
#		case "${flag}" in
#			t) time_check=1;;
#			sd) SEED=${OPTARG};;
#		esac
#	done

	echo "Seed is : $SEED"

	if [[ $# -ne 0 ]]
	then
		if [[ $1 == "vector" ]]
		then
			./ft_vector_test > ft
			./std_vector_test > std
			diff ft std > result
		fi
		if [[ $1 == "stack" ]]
		then
			./ft_stack_test > ft
			./std_stack_test > std
			diff ft std > result
		fi
		if [[ $1 == "map" ]]
		then
			./ft_map_test > ft
			./std_map_test > std
			diff ft std > result
		fi
	else
			./ft_vector_test > ft
			./std_vector_test > std
			./ft_stack_test >> ft
			./std_stack_test >> std
			./ft_map_test >> ft
			./std_map_test >> std
			diff ft std > result
	fi

	if [[ $? -eq 0 ]]
	then 
		echo "diff : OK"
	else
		echo "diff : KO"
		cat result
		echo "Seed is : $SEED"
	fi