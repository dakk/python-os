.PHONY: all build make-iso run-qemu clean

all: build make-iso run-qemu
	@echo "Default run complete"


build:
	rm -r micropython/ports/x86_64
	cp -r x86_64 micropython/ports/
	make -C micropython/mpy-cross
	make -C micropython/ports/x86_64 submodules all FROZEN_MANIFEST=../../../kernel/manifest.py USER_C_MODULES=../../../modules/

make-iso:
	mkdir -p isofiles/boot/grub
	cp ./micropython/ports/x86_64/build/firmware.elf isofiles/boot/kernel.elf
	cp grub.cfg isofiles/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o python-os.iso isofiles

run-qemu:
	rm -f /tmp/qemu-mon.sock	
	qemu-system-x86_64 -cdrom python-os.iso	-monitor unix:/tmp/qemu-mon.sock,server,nowait &
	sleep 1
	echo "screendump screenshot.ppm" | socat - UNIX-CONNECT:/tmp/qemu-mon.sock
	convert screenshot.ppm screenshot.png
	rm screenshot.ppm  /tmp/qemu-mon.sock

clean:
	cd micropython/ports/x86_64 && make clean


make-mpy-cross:
	cd ./micropython/mpy-cross && make

