CC=g++

default: sendfile recvfile

all: sendfile recvfile

sendfile.o: src/sendfile.cpp src/utils.h src/sliding_window.h
	$(CC) -c src/sendfile.cpp

utils.o: src/utils.cpp src/utils.h
	$(CC) -c src/utils.cpp

recvfile.o: src/recvfile.cpp src/utils.h
	$(CC) -c src/recvfile.cpp

sendfile: sendfile.o utils.o
	$(CC) -o sendfile sendfile.o utils.o

recvfile: recvfile.o utils.o
	$(CC) -o recvfile recvfile.o utils.o

clean: 
rm -f *.o