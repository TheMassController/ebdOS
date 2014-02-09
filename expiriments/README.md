#Info
This projocts is the result of RTOS, one of the things we need to do for the minor Embedded Systems. But thats okay, its fun!
The current repo contains everything you need to build a file which can be read and run by a Stellar Launchpad

##Dependencies and instructions
You need the GCC-ARM-none-eaubi toolchain:

[gcc-arm-embedded](https://launchpad.net/gcc-arm-embedded/4.7/4.7-2012-q4-major)

And LM4Flash

[LM4Tools on Github](https://github.com/utzig/lm4tools)

Compile LM4Flash and place it on your PATH to make the autoflash function of the Makefile work properly
You need to install one depedency:

`sudo apt-get install libusb-1.0-0-dev`

Next up: git clone

`git clone git@github.com:utzig/lm4tools.git`

And compile and move to PATH location

`cd lm4tools/lm4flash; make; sudo cp lm4flash /usr/bin`

To make sure every user has the right to write and read to the Stellaris Launchpad, do the following:

1.	Create the file /etc/udev/rules.d/61.stellpad.rules

2.	Put the following text into it:  
	`SUBSYSTEM=="usb", ATTRS{idVendor}=="1cbe", ATTRS{idProduct}=="00fd", MODE="0666"`

3. Reload USB rules:  
	`udevadm control --reload-rules`

#Debugging

##Dependencies
Install the following dependencies:  
`sudo apt-get install git-core libtool autoconf texinfo libusb-dev libusb-1.0 screen vim`

##OpenOCD
Get the correct OpenOCD version:  
```shell
git clone http://git.code.sf.net/p/openocd/code  
cd code    
git fetch http://openocd.zylin.com/openocd refs/changes/22/922/14 && git checkout FETCH_HEAD
```

If all the dependencies have been installed, the following command should execute without errors:  
```shell
./bootstrap
./configure --enable-maintainer-mode --enable-ti-icdi
make
sudo make install
```

##How to debug

First launch OpenOCD with the correct configuration for this Stellaris Launchpad:  
```shell
sudo openocd --file /usr/local/share/openocd/scripts/board/ek-lm4f120xl.cfg
```

Next start the GNU ARM version of GDB using the ELF file:  
```shell
arm-none-eabi-gdb final.elf
(gdb) target extended-remote :3333
(gdb) monitor reset halt
(gdb) load
(gdb) monitor reset init
```
At this point normal debugging should be possible.  
To receive printed output, the application __screen__ can be used. Use the following command to connect to the Stellaris Launchpad:
```shell
sudo screen /dev/ttyACM0 115200
```

#Sources  
+http://hackaday.com/2012/10/11/getting-started-with-the-stellaris-launchpad/
+http://recursive-labs.com/blog/2012/10/28/stellaris-launchpad-gnu-linux-getting-started/
+https://github.com/utzig/lm4tools
+https://launchpad.net/gcc-arm-embedded/4.7/4.7-2012-q4-major
+http://ubuntuforums.org/showthread.php?t=2101826
+http://processors.wiki.ti.com/index.php/Stellaris_Launchpad_with_OpenOCD_and_Linux
+http://eehusky.wordpress.com/2012/12/17/using-gcc-with-the-ti-stellaris-launchpad-newlib/
+https://github.com/eehusky/Stellaris-GCC/tree/master/proj0
