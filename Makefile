# Makefile for CS130A PA01

perfectHash.o: perfectHash.cpp
	g++ -c -g perfectHash.cpp

perfectHashTest.o: perfectHashTest.cpp
	g++ -c -g perfectHashTest.cpp

myCache.o: myCache.cpp
	g++ -c -g myCache.cpp

myCacheTest.o: myCacheTest.cpp
	g++ -c -g myCacheTest.cpp

clean: 
	rm -f perfectHashTest perfectHashTest.o perfectHash.o
	rm -f myCacheTest myCacheTest.o myCache.o

q1test:  perfectHashTest.o perfectHash.o
	g++ -o perfectHashTest -g perfectHashTest.o perfectHash.o
	
q2test: myCache.o myCacheTest.o
	g++ -o myCacheTest -g myCacheTest.o myCache.o
