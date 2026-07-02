g++ -I/home/italo/workspace-cpp/xutest/src -o /home/italo/workspace-cpp/xutest/obj/Debug/test/main.o -c main.cpp

g++ -o ../bin/Debug/__test ../obj/Debug/test/main.o -L../lib/linux -lxutest -ldl -rdynamic

../bin/Debug/__test