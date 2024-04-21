all:
	gcc main.c ecs.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g -o main
