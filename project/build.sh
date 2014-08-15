#!/bin/bash

MAKEFLAGS="-j4" 
MAKE=$(which make)
FLASH=$(which lm4flash)
PROJDIR=proj/
RELEASEEXEC=$PROJDIR/release/jackoOS_stripped
DEBUGEXEC=$PROJDIR/debug/jackoOS

function runMake {
   $MAKE -C $PROJDIR $1 $MAKEFLAGS
}

function runFlash {
    case "$1" in
        flash)
            runMake all
            ;;
        debugflash)
            runmake debug
            ;;
    esac
    $FLASH $1
}

function printUsageAndExit {
    echo "Usage: <script> params"
    echo "params:"
    echo "all, clean, distclean, debug, flash, debugflash" 
    echo "debugflash implies debug"
    echo "flash implies all"
    exit
}

function commandDistribution {
    case "$1" in
        all|clean|debug|distclean)
            runMake $1
            ;;
        flash|debugflash)
            runFlash $1
            ;;
        
        *)
            echo "Unknown command $1"   
            ;;
    esac
}

if [ $# -eq 0 ]; then
    printUsageAndExit
fi

PARAMS=$(($#))
for var in $@; do
    commandDistribution $var;
done
