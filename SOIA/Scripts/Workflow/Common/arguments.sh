#!/bin/bash

function bhelp_1args
{
	if [ "$#" -ne 1 ] || [ "$1" == "-h" ];then
		bhelp=true
	fi
}