#Makefile
all: sum-test

sum-test: add-nbo.o
	g++ -o sum-test add-nbo.o

add-nbo.o: add-nbo.h add-nbo.cpp

#main.o: sum.h main.cpp

#sum.o: sum.h sum.cpp

clean:
	rm -f sum-test
	rm -f *.o

