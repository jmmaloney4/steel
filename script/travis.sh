#!/bin/sh

if which -s apt-get; then
    sudo apt-get update
    sudo apt-get install nasm
else
    brew update
    brew install nasm
fi

function run {
"$@"
local status=$?
if [ $status -ne 0 ]; then
	echo "$@" Failed With Status $status
		exit $status
	else
		echo $1 Succeeded
	fi
	return $status
}

run make
