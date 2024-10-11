# Programs name
PROG = turbolink

# Define the target file
TARGET = main

# Define the source file
SRC = $(TARGET).asm

# Define the output binary file
OUTPUT = $(PROG).bin

# Define the assembler command
ASSEMBLER = z88dk-z80asm

# Define the assembler flags
ASFLAGS = -mez80 -b -Iinclude

# Default target
all: clean $(OUTPUT)

# Rule to assemble the source file
$(OUTPUT): $(SRC)
	$(ASSEMBLER) $(ASFLAGS) -o$(OUTPUT)  $(SRC)

# Clean up target
clean:
	rm -f $(TARGET).o $(PROG).bin
