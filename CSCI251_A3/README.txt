If program fails to run, there may be a need to recompile the files.

Copy and paste the following commands into command prompt:

	g++ -c Point2D.cpp
	g++ -c Point3D.cpp
	g++ -c Line2D.cpp
	g++ -c Line3D.cpp

To compile and run the program in the command prompt:

	g++ -std=c++11 Point2D.o Point3D.o Line2D.o Line3D.o mainmenu.cpp -o csci251_a3.exe
	
	./csci251_a3.exe

A sample txt file is included for Read In Data option while running the program:

	messy.txt