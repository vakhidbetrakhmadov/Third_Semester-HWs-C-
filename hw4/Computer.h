#ifndef COMPUTER_H
#define COMPUTER_H
	
#include "Memory.h"
#include "CPU.h"
#include "CPUProgram.h"

class Computer
{
public:
	Computer(){}
	Computer(int option_value);
	Computer( const CPU & cpu_obj,const CPUProgram & cpu_program_obj,Memory const & memory_obj,int option_value);

	void setCPU(const CPU & cpu_obj);
	void setCPUProgram(const CPUProgram & cpu_program_obj);
	void setMemory(const Memory & memory_obj);
	const CPU & getCPU()const;
	const CPUProgram & getCPUProgram()const;
	const Memory & getMemory()const;
	int getOption()const;
	void setOption(int value);
	void execute();
private:
	CPU my_cpu;
	CPUProgram my_cpu_program;
	Memory my_memory;
	int option;
};

#endif