make: bottomup.cpp
	g++ bottomup.cpp -o bottomup -Wall -O3
run: make bottomup.exe
	./bottomup
