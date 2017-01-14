all :exe

exe: CPUProgram.o Memory.o CPU.o Computer.o _mainTester.o
	g++ -o exe CPU.o CPUProgram.o _mainTester.o Computer.o Memory.o

Computer.o: Computer.cpp Computer.h Memory.h CPUProgram.h CPU.h
	g++ -c Computer.cpp

Memory.o: Memory.cpp Memory.h
	g++ -c Memory.cpp

CPU.o: CPU.cpp CPU.h Memory.h
	g++ -c CPU.cpp

CPUProgram.o:CPUProgram.cpp CPUProgram.h
	g++ -c CPUProgram.cpp

_mainTester.o: _mainTester.cpp requiredIncs.h
	g++ -c _mainTester.cpp 

clean:
	rm exe* *.o

exe2: CPUProgram.o Memory.o CPU.o Computer.o main2.o
	g++ -o exe2 CPU.o CPUProgram.o main2.o Computer.o Memory.o

main2.o: main2.cpp requiredIncs.h
	g++ -c main2.cpp

