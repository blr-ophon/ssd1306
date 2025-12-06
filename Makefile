################################################################################

MCU = atmega328p
F_CPU = 16000000UL

CC = avr-gcc
OBJCOPY = avr-objcopy
OPT = -Os
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(OPT)


SRC_DIR := ./src
BUILD_DIR := ./build
BIN_DIR := ./bin
INC_DIR := ./include


CFILES := $(shell find $(SRC_DIR) -name '*.c')
INCLUDES= -I${INC_DIR}
OBJECTS := $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET := ${BIN_DIR}/main

all: ${TARGET}.hex

# Convert ELF to HEX
${TARGET}.hex: ${TARGET}.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Build ELF
${TARGET}.elf: ${OBJECTS}
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} ${INCLUDES} ${OBJECTS} -o $@ 

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} ${INCLUDES} -c $< -o $@ 

################################################################################

PROGRAMMER = arduino	# usbasp if using avr-dude
PORT = /dev/ttyACM0 
BAUD = 115200

# Upload HEX to chip via arduino
upload: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) \
		-U flash:w:$(TARGET).hex:i

doc:
	doxygen -g && \
	sed -i 's|^INPUT.*|INPUT = src include|' Doxyfile && \
	sed -i 's|GENERATE_LATEX.*|GENERATE_LATEX = NO|' Doxyfile

clean:
	rm -rf ${BUILD_DIR} 
	rm -rf ${BIN_DIR} 
	rm -rf *.plist
