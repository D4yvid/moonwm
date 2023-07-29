SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

CC = tcc
CFLAGS = -Wall -Werror -Wpedantic -Wno-unused-variable -Wno-unused-argument
LFLAGS = -lX11

TARGET = moonwm

all: dirs build run

dirs:
	mkdir -p obj/

build: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LFLAGS)

run:
	./runwm-xwayland.sh

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
