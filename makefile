PipeServerProject: interface.c
	gcc -std=c99 -w -o server server.c
	gcc -std=c99 -w -o interface interface.c -I.
