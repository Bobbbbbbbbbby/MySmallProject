SRC = main.c input/input.c init.c draw/draw.c mouse/mouse.c keyboard/keyboard.c
TAG = -lGL -lglut -lGLU -o lab2 -g
CC = gcc

polygon: $(SRC)
	@$(CC) $(SRC) $(TAG)  -lm

lineloop: $(SRC)
	@$(CC) $(SRC) $(TAG) -D LINE_LOOP

renormal: $(SRC)
	@$(CC) $(SRC) $(TAG) -D RENORMAL -lm

clean:
	@rm lab2

run:
	@./lab2

.PHONY:clean run