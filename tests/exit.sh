#!/bin/sh
#tests exit and commands with exit

exit

ls -a && exit

-j || exit

exit && echo hello
