How to compile:

c++ -c time.cpp --> compiles but does not link Time class

This creates a time.o object file. This is like a .class file in Java.

Then you want to run:

c++ testTime.cpp time.o --> this links the object and client file.

testTime.cpp should #include "time.h" to call the function prototypes referred to in the header file.

c++ -c time.cpp
c++ tesTime.cpp time.o
