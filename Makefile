ROOT_DIR= 
SRCDIR=$(ROOT_DIR)src/
BIN=$(ROOT_DIR)bin/

CC=g++

V8DIR = /home/sean/Projects/v8/
LIBV8= -L$(V8DIR)v8/out.gn/x64.release.sample/obj/
INCLUDEV8=-I$(V8DIR)v8/include/
V8PP_INCLUDE= -I$(V8DIR)v8pp/
LIBPLAT_INCLUDE=-I$(V8DIR)v8/include/libplatform

SFML_LIBS= -L/usr/lib/x86_64-linux-gnu/
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE=

INCLUDE=$(INCLUDEV8) $(V8PP_INCLUDE) $(LIBPLAT_INCLUDE) $(SFML_INCLUDE)
LIBS=$(LIBV8) $(SFML_LIBS)

CFLAGS= -lrt -lm -lv8_monolith -pthread -std=c++20 -lstdc++ -DV8_ENABLE_SANDBOX -DV8_COMPRESS_POINTERS -ldl $(SFML_FLAGS)

EXE=sfmlv8
OUT=bin/sfmlv8

# ENGINE_SRCS= $(SRCDIR)/wrapper/graphics.cpp $(SRCDIR)/wrapper/time.cpp  $(SRCDIR)/scriptsystem/script.cpp $(SRCDIR)/scriptsystem/scriptsystem.cpp 
ENGINE_SRCS=  $(SRCDIR)bridge.cpp
SRCS=$(SRCDIR)main.cpp $(ENGINE_SRCS)

default: sfmlv8

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: sfmlv8

clean:
	figlet clean
	rm -r $(OUT)

sfmlv8: $(SRCS)
	figlet make sfmlv8
	$(CC) -g -Wall $(INCLUDE) $(SRCS) -o $(OUT) $(LIBS) $(CFLAGS)
	chmod +x $(OUT)
