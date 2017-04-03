SOURCES := $(wildcard src/*.c)

all: build
	gcc -o build/demon main.c $(SOURCES) -I headers #all in one

build:
	mkdir build

clean:
	rm -rf build
