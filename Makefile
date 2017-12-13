
build: build/pam_module.so

build/pam_module.so: build/pam_module.o
	gcc -shared -o build/pam_module.so build/pam_module.o -lpam

build/pam_module.o: src/pam_module.c
	gcc -fPIC -c src/pam_module.c -o build/pam_module.o

.PHONY: clean

clean:
	-rm build/*