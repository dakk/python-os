
# git clone https://github.com/micropython/micropython
#make submodules && make -C ../../mpy-cross &&

build-micropython:
#  	cd kernel && make
	rm -r micropython/ports/x86_64
	cp -r x86_64 micropython/ports/
	make -C micropython/mpy-cross
	make -C micropython/ports/x86_64 submodules all FROZEN_MANIFEST=../../../kernel/manifest.py USER_C_MODULES=../../../modules/

	mkdir -p isofiles/boot/grub
	cp ./micropython/ports/x86_64/build/firmware.elf isofiles/boot/kernel.elf
	cp grub.cfg isofiles/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o python-os.iso isofiles
	qemu-system-x86_64 -cdrom python-os.iso	
	

clean:
	cd micropython/ports/x86_64 && make clean
	#cd kernel && make clean


make-mpy-cross:
	cd ./micropython/mpy-cross && make