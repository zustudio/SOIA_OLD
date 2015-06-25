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
	echo "= Help:"
	for line in "$@"
	do
	    echo "=   $line"
	done
}

function echo_success
{
	echo "="
	echo "=="
	echo "====== Success ======"
}