
CXX=g++
CXXFLAGS=-Wall -g
TARGET=xutest

.PHONY: all

all: $(TARGET)

$(TARGET): src/main.o src/test/util/io.o src/test/util/strutil.o src/test/sourcecode/SourceCodeManager.o src/test/xutest.o
	$(CXX) -o $(TARGET) obj/Debug/src/main.o obj/Debug/src/test/util/io.o obj/Debug/src/test/util/strutil.o obj/Debug/src/test/sourcecode/SourceCodeManager.o obj/Debug/src/test/xutest.o

src/main.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/main.o -c src/main.cpp

src/test/util/io.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/test/util/io.o -c src/test/util/io.cpp

src/test/util/strutil.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/test/util/strutil.o -c src/test/util/strutil.cpp

src/test/sourcecode/SourceCodeManager.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/test/sourcecode/SourceCodeManager.o -c src/test/sourcecode/SourceCodeManager.cpp

src/test/xutest.o:
	$(CXX) $(CXXFLAGS) -o obj/Debug/src/test/xutest.o -c src/test/xutest.cpp

