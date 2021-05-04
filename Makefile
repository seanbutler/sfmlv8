SRC=src/
BIN=bin/

CC=g++

LIBV8= -L./deps/v8/out.gn/x64.release.sample/obj/
INCLUDEV8=-I./deps/v8/include/



SFML_LIBS= -L/usr/lib/x86_64-linux-gnu/
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE=

DEPS = ./deps/
INCLUDE=$(INCLUDEV8) $(SFML_INCLUDE)
LIBS=$(LIBV8) $(SFML_LIBS)

CFLAGS= -lrt -lm -lv8_monolith -pthread -std=c++14 -lstdc++ -DV8_COMPRESS_POINTERS -ldl $(SFML_FLAGS)

EXE=sfmlv8
OUT=bin/sfmlv8

default: sfmlv8

clean:
	rm -r $(OUT)

sfmlv8: $(SRC)main.cpp
	$(CC) -Wall $(INCLUDE) $(SRC)main.cpp -o $(OUT) $(LIBS) $(CFLAGS) $(SFML_FLAGS)
	chmod +x $(OUT)
