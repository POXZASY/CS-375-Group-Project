make: bottomup.cpp recursivememo.cpp
	g++ bottomup.cpp -o bottomup -Wall -O3 -std=c++17
	g++ recursivememo.cpp -o recursivememo -Wall -O3 -std=c++17
winclean:
	del bottomup.exe
	del recursivememo.exe
clean:
	rm bottomup
	rm recursivememo
