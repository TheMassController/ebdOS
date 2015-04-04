#!/bin/bash

source arm-gcc-locations

DEFAULT="flash"

MAKEFLAGS="-j10"
MAKE=$(which make)
FLASH=$(which lm4flash)
OPENOCD=$(which openocd)
OPENOCDSCRIPT=/usr/local/share/openocd/scripts/board/ek-lm4f120xl.cfg
LOGDIR=log/
PROJDIR=proj/
RELEASEEXEC=$PROJDIR/release/jackoOS_stripped
DEBUGEXEC=$PROJDIR/debug/jackoOS
GDBDIR=gdb/

function runMake {
    $MAKE -C $PROJDIR $1 $MAKEFLAGS
    if [ $? -ne 0 ]; then
        echo "Make failed! Exitting.."
        exit
    fi
}

function runFlash {
    pkill openocd || true
    case "$1" in
        flash)
            runMake all
            $FLASH $RELEASEEXEC
            ;;
        debugflash)
            runMake debug
            $FLASH $DEBUGEXEC
            ;;
    esac

    if [ $? -ne 0 ]; then
        echo "Flashing failed! Exiting.."
        exit
    fi
}

function debugRun {
    runFlash debugflash
    launchGDB
}

function launchGDB {
    pkill openocd || true
    $OPENOCD --file $OPENOCDSCRIPT >> $LOGDIR/openocdLog.txt 2>&1 &
    arm-none-eabi-gdb $DEBUGEXEC -x $GDBDIR/gdb.script
    pkill $OPENOCD
    
}

function printUsage {
    echo "Usage: <script> params"
    echo "params:"
    echo "help, all, clean, distclean, debug, flash, debugflash, echo, launchGDB, screen" 
    echo "debugflash implies debug and launchGDB"
    echo "flash implies all"
}

function launchScreen {
    sudo screen /dev/ttyACM0 115200
}

function commandDistribution {
    case "$1" in
        all|clean|debug|distclean|echo)
            runMake $1
            ;;
        flash|debugflash)
            runFlash $1
            ;;
        debugRun)
            debugRun
            ;;
        launchGDB)
            launchGDB
            ;;
        screen)
            launchScreen
            ;;
        help)
            printUsage
            ;;
        *)
            echo "Unknown command $1"   
            ;;
    esac
}

PATH=$PATH:$ARMGCCBIN
export PATH
export ARMGCCEXLIB
export ARMGCCLIB

#default: all
if [ $# -eq 0 ]; then
    commandDistribution $DEFAULT
    exit 0
fi

for var in $@; do
    commandDistribution $var;
done
