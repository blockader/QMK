#!/bin/bash -xe
os=`uname`
if [ $os == "Darwin" ]; then
    pip install hidapi
    pip install pync
    pip install pyqt5
else
    echo $os is not a supported OS.
fi
