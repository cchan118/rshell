# rshell

Collaborators: Chih-Cheih Chang, Francisco Prado 

##Installation 
To download and file the file
``` 
$ git clone  https://github.com/cchan118/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```
##Description
rshell is a command shell that runs in C++, the shell performs in the following steps:
``` 
1. Print a command prompt (e.g. $)
2. Read in a command on one line
``` 
The commands will have the form:
``` 
cmd         = executable [ argumentList ] [ connector cmd ];
connector   = || or && or ;
``` 



##Testing 
To run the program and test shell scripts
``` 
Compile rshell.cpp
While running the ./a.out file execute the shell scripts inside the tests directory ex: ./single_command.sh

``` 
