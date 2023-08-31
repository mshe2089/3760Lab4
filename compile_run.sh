#! /usr/bin/bash
g++ -pedantic-errors -Wall -Wextra -Werror *.cpp -o program
./program < example.circuit
rm ./program