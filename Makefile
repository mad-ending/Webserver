FLAGS = -std=c++17 -Wall -Wextra
CPP = g++

main: main.o request.o response.o validation.o server.o
	$(CPP) $(FLAGS) validation.o request.o response.o server.o main.o -o server

main.o: main.cpp
	$(CPP) -c $(FLAGS) main.cpp -o main.o

request.o: request.cpp
	$(CPP) -c $(FLAGS) request.cpp -o request.o

response.o: response.cpp
	$(CPP) -c $(FLAGS) response.cpp -o response.o

server.o: server.cpp
	$(CPP) -c $(FLAGS) server.cpp -o server.o

validation.o: validation.cpp
	$(CPP) -c $(FLAGS) validation.cpp -o validation.o

clean:
	sudo rm -rf *.o

distclean:
	sudo rm -rf *.o server

all : main
