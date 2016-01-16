# sane defaults for C in the year 2016, source: https://matt.sh/howto-c
FLAGS ?= -std=c99 -O2 -Wall -Wextra -pedantic -Wno-missing-field-initializers -flto -march=native

# TODO: extra flags for testing, how to include in build?
EXTRAFLAGS = -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing

all:	build

build:	xdgatool

xdgatool:	xdgatool.c
	$(CC) $(FLAGS) -o xdgatool xdgatool.c -lX11 -lXxf86dga

clean:
	rm -f *~
	rm -f xdgatool
