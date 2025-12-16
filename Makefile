
# git clone https://github.com/micropython/micropython

build-micropython:
	cp -r x86_64 micropython/ports/
	cd micropython/ports/x86_64 && make

	mkdir -p isofiles/boot/grub
	cp ./micropython/ports/x86_64/build/firmware.elf isofiles/boot/kernel.elf
	cp grub.cfg isofiles/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o python-os.iso isofiles
	qemu-system-x86_64 -cdrom python-os.iso	
	

clean:
	cd micropython/ports/x86_64 && make clean
