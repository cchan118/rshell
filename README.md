# rshell

Collaborators: Chih-Chieh Chang, Francisco Prado 

##Installation 
To download and file the file
``` 
$ git clone  https://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw3
$ make
$ bin/rshell
```
##Description
Adds the test command to your rshell, as well as its symbolic equivalent [ ]. The square brackets [ ] are actually set up as the test command in bash. This command returns 0 (TRUE) if the test succeeds and 1 (FALSE) if the test fails. This command is very useful for writing conditions that can be combined with && and || to write more complex bash command structures.
Additionally,  parentheses ( ) act as precedence operators in rshell. The parentheses ( ) operators are used to change the precedence of the returns of commands, connectors, and chains of connectors.
``` 
The commands will have the form:
``` 
$ test -e /test/file/path && echo “path exists”
$ [ -e test/file/path ]
$ test -e /test/file/path && echo “path exists”
					- or -
$ [ -e /test/file/path ] && echo “path exists”
$ echo A && echo B || echo C && echo D
$ (echo A && echo B) || (echo C && echo D)
``` 



##Testing 
To run the program and test shell scripts
``` 
Compile: g++ rshell.cpp
While running the ./a.out file execute the shell scripts inside the tests directory ex: ./single_command.sh

``` 

##Known Bugs
List of known bugs in the program:
``` 
-Brackets [] implemented to only be used with spaces such that [_-e path_]
-Parenthesis have issues with logic in determining two commands to be one false/true statement
``` 
