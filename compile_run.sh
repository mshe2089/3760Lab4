#! /usr/bin/bash
g++ -pedantic-errors -Wall -Wextra -Werror *.cpp -o program
./program
rm ./program