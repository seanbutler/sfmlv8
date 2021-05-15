SRCDIR=src/
BIN=bin/

CC=g++

LIBV8= -L./deps/v8/out.gn/x64.release.sample/obj/
INCLUDEV8=-I./deps/v8/include/

SFML_LIBS= -L/usr/lib/x86_64-linux-gnu/
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE=


V8PP_INCLUDE= -I./deps/v8pp/


DEPS = ./deps/
INCLUDE=$(INCLUDEV8) $(V8PP_INCLUDE) $(SFML_INCLUDE)
LIBS=$(LIBV8) $(SFML_LIBS)

CFLAGS= -lrt -lm -lv8_monolith -pthread -std=c++14 -lstdc++ -DV8_COMPRESS_POINTERS -ldl $(SFML_FLAGS)

EXE=sfmlv8
OUT=bin/sfmlv8


ENGINE_SRCS= $(SRCDIR)/wrapper/graphics.cpp $(SRCDIR)/wrapper/time.cpp  $(SRCDIR)/scriptsystem/script.cpp $(SRCDIR)/scriptsystem/scriptsystem.cpp 

SRCS=$(SRCDIR)main.cpp $(ENGINE_SRCS)

default: sfmlv8

clean:
	figlet clean
	rm -r $(OUT)

sfmlv8: $(SRCS)
	figlet make sfmlv8
	$(CC) -g -Wall $(INCLUDE) $(SRCS) -o $(OUT) $(LIBS) $(CFLAGS)
	chmod +x $(OUT)
