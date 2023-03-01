CC = gcc
SRC = main.c tools/tools.c render/render.c render/rayTracing.c object/object.c object/sphere.c
TAG = -lm -o rt

build: $(SRC)
	$(CC) $(SRC) $(TAG)

debug: $(SRC)
	$(CC) $(SRC) $(TAG) -g

clean:
	rm rt

.PHONY: clean