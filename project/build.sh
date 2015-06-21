#!/bin/bash

source arm-gcc-locations

DEFAULT="all"

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
    echo "Example: buid.sh clean all debug"
    echo "params:"
    echo "help          Print this message"
    echo "all           Release build"
    echo "debug         Debug build"
    echo "flash         Compile and flash. Implies all"
    echo "debugFlash    Compile and flash. Implies debug"
    echo "launchGDB     Connects the GDB debugger the the board and loads the debug symbols"
    echo "debugRun      Same as debug debugflash launchGDB"
    echo "clean         Remove all .o files"
    echo "distclean     Remove all files that are not created by the user"
    echo "screen        Connect to the stellaris using GNU screen"
    echo "echo          Prints some parameters about the current build envirnment"
    echo ""
    echo "'all' is implied when no commands are given"
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
