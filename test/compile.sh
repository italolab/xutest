g++ -o ../obj/Debug/test/main.o -c main.cpp -I../src
g++ -o ../bin/Debug/test/xutest ../obj/Debug/test/main.o -ldl -rdynamic -L../lib -lxutest