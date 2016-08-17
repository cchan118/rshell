all: rshell.cpp Cmd.h CmdCheck.h Connector.h
	[ -d "bin" ] || mkdir bin
	g++ rshell.cpp -o bin/rshell
clean:
	rm -rf bin
