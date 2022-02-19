#!/bin/bash
CMD_DATE=date

SEED=$($CMD_DATE +%s);

echo "Seed is : $SEED"


if [[ $# -ne 0 ]]
then
	if [[ $1 == "vector" ]]
	then
		echo -e "\n\nft::vector"
		time ./ft_vector_test.exe > ft.out
		echo -e "\nstd::vector"
		time ./std_vector_test.exe > std.out
	fi
	if [[ $1 == "stack" ]]
	then
		echo -e "\n\nft::stack"
		time ./ft_stack_test.exe > ft.out
		echo -e "\nstd::stack"
		time ./std_stack_test.exe > std.out
	fi
	if [[ $1 == "map" ]]
	then
		echo -e "\n\nft::map"
		time ./ft_map_test.exe > ft.out
		echo -e "\nstd::map"
		time ./std_map_test.exe > std.out
	fi
else
	echo -e "\n\nft::vector"
	time ./ft_vector_test.exe > ft.out
	echo -e "\nstd::vector"
	time ./std_vector_test.exe > std.out

	echo -e "\n\nft::stack"
	time ./ft_stack_test.exe >> ft.out
	echo -e "\nstd::stack"
	time ./std_stack_test.exe >> std.out

	echo -e "\n\nft::map"
	time ./ft_map_test.exe >> ft.out
	echo -e "\nstd::map"
	time ./std_map_test.exe >> std.out
fi

diff ft.out std.out > result.out

if [[ $? -eq 0 ]]
then 
	echo -e "\ndiff : OK"
else
	echo -e "\ndiff : KO"
	cat result.out
	echo "Seed was : $SEED"
fi
