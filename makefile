CFLAGS = -std=c++17 -O2

project: main.cpp
	g++ $(CFLAGS) -o project main.cpp

.PHONY: test clean

test: project
	./project

clean:
	rm -f project
