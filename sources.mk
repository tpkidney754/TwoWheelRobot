INCLUDES = \
	-I ./Main/   \
	-I ./Data/   \
	-I ./Memory/ \
	-I ./Testing/ \
	-I ./CircularBuffer/ \
	-I ./FRDM_INCLUDES/ \
	-I ./Modules \
	-I ./FRDM_Startup_Code/ \
	-I ./Logging/ \
	-I ./Messaging/ \
	-I ./Display/ \
	-I ./TemperatureController/ \

BBBSRCS = \
	./Main/main.c   \
	./Memory/memory.c \
	./Data/data.c \
	./CircularBuffer/circularbuffer.c \
	./Modules/uart.c \
	./Modules/diags.c \
	./Modules/spi.c \
	./Modules/nRF24L01.c \
	./Modules/timers.c \
	./Logging/uartlogging.c \
	./Testing/testing.c \
	./Testing/datatesting.c \
	./Testing/memorytesting.c \
	./Testing/circularbuffertesting.c \
	./Testing/performancetesting.c \
	./Messaging/messaging.c \

FRDMSRCS = \
	./Main/main.c   \
	./Memory/memory.c \
	./Data/data.c \
	./CircularBuffer/circularbuffer.c \
	./Modules/uart.c \
	./Modules/led.c \
	./Modules/timers.c \
	./Modules/diags.c \
	./Modules/dma.c \
	./Modules/spi.c \
	./Modules/nRF24L01.c \
	./Modules/i2c.c \
	./Modules/lsm9ds1.c \
	./Modules/adc.c \
	./Modules/pushbutton.c \
	./Logging/uartlogging.c \
	./Testing/testing.c \
	./Testing/datatesting.c \
	./Testing/memorytesting.c \
	./Testing/circularbuffertesting.c \
	./Testing/performancetesting.c \


STARTUP = \
	./FRDM_Startup_Code/startup_MKL25Z4.S \
	./FRDM_Startup_Code/system_MKL25Z4.c \

LIBS = \
	./Memory/memory.c \
	./Data/data.c \
	./CircularBuffer/circularbuffer.c \
	./Modules/uart.c \
	./Modules/led.c \
	./Modules/timers.c \
	./Modules/diags.c 	\
