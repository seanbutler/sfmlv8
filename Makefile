SRC=src/
CC=g++
LIBV8= -L./deps/v8/out.gn/x64.release.sample/obj/
CFLAG= -lrt -lm -lv8_monolith -pthread -std=c++14 -lstdc++ -DV8_COMPRESS_POINTERS -ldl 
DEPS = ./deps/
INCLUDE=-I./deps/v8/include/

default: main

native: tools.o $(SRC)native.cpp
	$(CC) tools.o -Wall $(INCLUDE) -I$(DEPS) $(SRC)native.cpp -o bin/native $(LIBV8) $(CFLAG)
	chmod +x bin/native

tools.o: $(DEPS)tools.c $(DEPS)tools.h
	$(CC) -c $(DEPS)tools.c -o tools.o

clean:
	rm -r bin/*

main: $(SRC)main.cpp
	$(CC) -Wall $(INCLUDE) $(SRC)main.cpp -o bin/main $(LIBV8) $(CFLAG)
	chmod +x bin/main

