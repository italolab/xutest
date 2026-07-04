g++ -I../src -o ../obj/Debug/test/main.o -c main.cpp

g++ -o ../bin/Debug/__test ../obj/Debug/test/main.o -L../lib/linux -lxutest -ldl -rdynamic

../bin/Debug/__test