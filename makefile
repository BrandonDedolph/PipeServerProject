PipeServerProject: interface.c
	cc -o server server.c
	cc -o interface interface.c -I.
