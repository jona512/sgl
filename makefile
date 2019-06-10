main: t01.c sgl.h sgl.c
	gcc -Wall t01.c sgl.c -o t01 -lGL -lGLU -lglut -lm
