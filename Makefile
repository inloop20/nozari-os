# ===============================
# Project sources and headers
# ===============================
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS   = $(wildcard kernel/*.h drivers/*.h)
OBJ       = ${C_SOURCES:.c=.o}

# ===============================
# Docker image name
# ===============================
DOCKER_IMG = os-dev-env

# ===============================
# Default target: build OS inside Docker
# ===============================
all: os-image.bin

os-image.bin:
	docker run --rm -v $(PWD):/os -w /os $(DOCKER_IMG) make build-os

run:
	docker run --rm -v $(PWD):/os -w /os $(DOCKER_IMG) make run-os

debug:
	docker run --rm -v $(PWD):/os -w /os $(DOCKER_IMG) make debug-os

# ===============================
# Internal targets (run inside container)
# ===============================
build-os: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

run-os: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug-os: os-image.bin kernel.elf
	qemu-system-i386 -S -gdb tcp::1234 -fda os-image.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# ===============================
# Compile C and Assembly
# ===============================
%.o: %.c ${HEADERS}
	i386-elf-gcc -g -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.elf *.o os-image.bin
	rm -rf kernel/*.o boot/*.bin drivers/*.o