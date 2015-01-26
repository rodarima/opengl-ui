CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lGL -lGLU -lglut -lm

# Nombres de los binarios a compilar:
BIN = line test_slider

all: $(BIN)

line: slider.o

test_slider: slider.o

clean:
	rm -f *.o $(BIN)
