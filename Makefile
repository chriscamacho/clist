
APPNAME:=$(shell basename `pwd`)

INSTR:= -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract
INSTR+= -fno-omit-frame-pointer

LDFLAGS:=  

CFLAGS:= -Wfatal-errors -Wall -Wextra -Werror
CFLAGS+= -std=c99 -I ./include 

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=.build/%.o)
INC:=$(wildcard include/*.h)

CC=gcc

all: debug

$(APPNAME): $(OBJ)
	$(CC) $(OBJ) -o $(APPNAME) $(LDFLAGS)

$(OBJ): .build/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: debug release inst

debug: CFLAGS+= -g
debug: 
	@echo "*** made DEBUG target ***"

release: CFLAGS+= -O3
release: 
	@echo "*** made RELEASE target ***"

inst: CFLAGS+= -g $(INSTR) -g
inst: LDFLAGS+= $(INSTR)
inst: 
	@echo "*** made INSTRUMENTATION target ***"

release: CFLAGS+= -Ofast

debug release inst: $(APPNAME)

.PHONY:	clean
clean:
	rm .build/* -f
	rm $(APPNAME) -f

style: $(SRC) $(INC)
	astyle -A10 -s4 -S -p -xg -j -z2 -n src/* include/*
