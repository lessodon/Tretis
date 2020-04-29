#############  TRETIS MAKEFILE v1.0  #############
#   by Tales Upper (github.com/lessodon) © 2020  #

GL=gamelib
SPRS=gamelib/sprites

all: gamelib-comp blah-only linkall
	# RUN ./tetris.run AND HAVE FUN!

linkall:
	cc blah.o $(GL)/tretis.o $(SPRS)/sprite.o $(SPRS)/brick*.o -lncursesw -o tretis.run

gamelib-comp:
	cd $(GL) && make

blah-only:
	cc -c blah.c

help:
	# Just run "make"

clean:
	rm blah.o
	cd $(GL) && make clean
