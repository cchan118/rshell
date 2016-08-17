CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic

all:
	mkdir -p ./bin 
	$(CC) $(CFLAGS) ./src/rshell.cpp -o ./bin/rshell
	
shell: 
	$(CC) $(CFLAGS) ./src/rshell.cpp
	
Cmd: 
	$(CC) $(CFLAGS) ./src/Cmd.h
	
Connector: 
	$(CC) $(CFLAGS) ./src/Connector.h
	
CmdCheck: 
	$(CC) $(CFLAGS) ./src/CmdCheck.h

clean: 
	rm -rf ./bin
