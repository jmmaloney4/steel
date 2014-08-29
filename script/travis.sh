#!/bin/sh

if [[ $platform == 'linux' ]]; then
    sudo apt-get update
    sudo apt-get install nasm
else
    brew update
    brew install nasm
fi

make
