#!/bin/bash

function backup_dir
{
	if [ -d "$1" ];then
		if [ "$2" -ne "0" ];then
			backup_dir "$1_old" "$(expr $2 - 1)"
			mv "$1" "$1_old"
		else
			rm -r "$1"
		fi
	fi
}