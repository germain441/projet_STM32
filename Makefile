# put your *.o targets here, make should handle the rest!

SRCS = appli/main.c system_stm32/stm32f4xx_it.c system_stm32/system_stm32f4xx.c system_stm32/startup_stm32f4xx.s 
SRCS += appli/led.c appli/bouton.c appli/driver.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=main

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tsystem_stm32/stm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

###################################################

CFLAGS += -Idriver_stm32 -Icore -Isystem_stm32
CFLAGS += -Iappli

OBJS = $(SRCS:.c=.o)

###################################################


all:	$(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
