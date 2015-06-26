#!/bin/bash

function soia_echo
{
	echo "= $1"
}

function echo_header
{
	echo ""
	echo "====== $1 ======"
	echo "=="
}

function echo_help
{
	if [ "$bhelp" == "true" ];then
		echo "= Help:"
		for line in "$@"
		do
		    echo "=   $line"
		done
		exit
	fi
}

function echo_success
{
	echo "="
	echo "=="
	echo "====== Success ======"
}
