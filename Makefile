SRC=src/
BIN=bin/

CC=g++
LIBV8= -L./deps/v8/out.gn/x64.release.sample/obj/
CFLAG= -lrt -lm -lv8_monolith -pthread -std=c++14 -lstdc++ -DV8_COMPRESS_POINTERS -ldl 
DEPS = ./deps/
INCLUDE=-I./deps/v8/include/

EXE=sfmlv8
OUT=bin/sfmlv8

default: sfmlv8

clean:
	rm -r $(OUT)

sfmlv8: $(SRC)main.cpp
	$(CC) -Wall $(INCLUDE) $(SRC)main.cpp -o $(OUT) $(LIBV8) $(CFLAG)
	chmod +x $(OUT)
