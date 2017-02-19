Makefile commands:

make host: Compiles for the host
make bbb: Comiles for the Beagle Bone Black
make frdm: Compiles for the MKL25Z FRDM board
make preprocess: This will run the preprocess portion of compliling and then stop
make asm-file: This will compile but not assemble and link all files.
make compile-all: This will compile and assemble but not link all files.
make build: This will compile, assemble, and link for the three main targets.
make upload: This will compile, assemble, link, and upload the executable
			 to the Beagle Bone Black.
make build-lib: This will build an archive library for the data.c and memory.c files.
make /Directory/file.o: This will individually compile and assemble a file when passed
						 the directory and file the user wishes to build and output to
						 the same directory file.o
make /Directory/file.i: This will individually preprocess a file when passed
						 the directory and file the user wishes to preprocess and output to
						 the same directory file.i
make /Directory/file.S: This will individually compile but not assemble a file when passed
						 the directory and file the user wishes to compile and output to
						 the same directory file.S
make clean: This will remove any *.o, *.d, *.i, *.S, *.map or *.a file located in the
				directory.

The size of the executable will be outputed after the specified build target is finished
building.

The make file will output an executable as follows:
host: proj
bbb: pro1bbb
frdm: projfrdm.elf

To run testing run the make file as follows:
	make target DEFINES=-DTEST
this will add in a #define TESTING to the preprocessor that will compile the
testing code written into the main.c file.


Diag commands when using FRDM KL25Z board:
set color x: This will change the color of the LED using the red green blue leds.
               Available colors are: red, green, blue, yellow, purple, cyan, white, and off.
set power x: Adjusts the intensity of the LED. The third parameter is an integer between 0 and 100.
               100 is full power, 0 is zero power and will turn off the LEDs.
set cycle:		Starts fading in and fading out the LEDs through each standard color.
send nop:      Sends a NOP command to the nRF24L01
read reg x:  Sends a read register command to the nRF24L01. XXX is the register to be read.
write reg x y: Sends a write register command to the nRF24L01. x is the register to be written and
					 y is the value to be writen to x register.
