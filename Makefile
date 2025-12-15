
# git clone https://github.com/micropython/micropython

build-micropython:
	cp -r x86_64 micropython/ports/
	cd micropython/ports/x86_64 && make
	./micropython/ports/x86_64/build/firmware.elf