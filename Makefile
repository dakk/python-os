kernel:
	shedskin translate kernel/main --nogc -m Makefile2 --nomakefile --int64 --float64 -o gen_cxx/
	cd kernel && make

cplib:
	cp -r $(HOME)/venv/lib/python3.13/site-packages/shedskin/lib ./cp_lib

.PHONY: kernel 