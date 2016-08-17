#!/bin/sh
#tests commands with ;, &&, or
ls -a; echo hello && mkdir test || echo world; git status

echo "hello" && echo "world"

echo hi || echo bye

mkdir class && echo "works"

ls -j || echo no

exit
