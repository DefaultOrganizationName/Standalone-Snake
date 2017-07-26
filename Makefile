CFLAGS  = -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -std=c++11
TARGET = os
OBJFILES = \
	lib/boot.o \
	lib/screen.o  \
	lib/standalone_snake_game.o \
	lib/keyboard_communicator.o \
	lib/queue.o \
	lib/easy_printf.o \
	lib/gdt.o \
	lib/io.o \
	lib/start_handler.o \
	lib/idt.o \
	lib/handler.o \
	lib/pic.o \
	lib/pit.o \
	lib/time.o \
	kernel.o

all: $(TARGET).bin
	@echo "\ncompiled successful!\n"

.s.o:
	i686-elf-as  $< -o $@

.cpp.o:
	i686-elf-g++ -c $< -o $@ $(CFLAGS)

$(TARGET).bin: $(OBJFILES)
	i686-elf-g++ -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

image:
	@mkdir -p isodir/boot/grub
	@cp $(TARGET).bin isodir/boot/$(TARGET).bin
	@cp grub.cfg isodir/boot/grub/grub.cfg
	@grub-mkrescue -o $(TARGET).iso isodir
	@echo "\niso image done successful!\n"

clean:
	rm -f -r $(OBJFILES) $(TARGET).iso $(TARGET).bin isodir/