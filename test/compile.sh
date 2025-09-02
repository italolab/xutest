g++ -o ../obj/Debug/test/main.o -c main.cpp -I../src
g++ -o ../bin/Debug/test/cbtest ../obj/Debug/test/main.o -ldl -rdynamic -L../lib -lcbtest