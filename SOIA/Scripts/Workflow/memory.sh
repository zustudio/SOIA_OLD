#!/bin/bash

base_dir="$(dirname "$0")"
source "$base_dir/Common/common.sh"

#####################################
# main

echo_header "Check memory leakage"

bhelp_args 1 "$@"
echo_help \
	"Usecase: Runs tests with drmemory." \
	"Arg0:    Name of cmake generator to use for build." \
	"         This defines the build folder name."

set_project_vars "$1"

find_exec="/usr/bin/find"
drmemory_exec=$($find_exec "$build_dir/Install/ThirdParty/bin/drmemory/bin" -executable -name "drmemory.exe" -type f)

mkdir -p "$build_dir/Logs"

templog_dir="$build_dir/Logs/Temp"
templog="$templog_dir/DrMemory.txt"
mkdir -p "$templog_dir"

log_dir="$build_dir/Logs/Memory"
backup_dir "$log_dir" "3"
mkdir -p "$log_dir"

cd "$build_dir/Binaries"
testfiles=$($find_exec . -executable -name "Test*")

for testfile in "$testfiles"
do
	soia_echo "Checking test $testfile..."
	echo ""
	{ result=$($drmemory_exec -callstack_style 0x1820 -visual_studio -prefix_style 2 -logdir "$log_dir" -- "$testfile" 2>&1 1>&$out); } {out}>&1
	echo ""
done

echo_important "Result"
leaknum="$(echo "$result" | grep -c LEAK)"
soia_echo "Leaks: $leaknum"
echo "$(echo "$result" | grep -B 8 Details)"
echo ""
soia_echo "Leak details:"
echo "$(echo "$result" | grep -A 18 LEAK)"

if [ "$leaknum" -ne "0" ];then
	exit 1
else
	echo_success
fi