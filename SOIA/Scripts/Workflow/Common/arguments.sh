#!/bin/bash

function bhelp_args
{
	expected_count=$(expr $1 + 1)
	if [ "$#" -ne "$expected_count" ] || [ "$1" == "-h" ];then
		bhelp=true
	fi
}