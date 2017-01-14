/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Computer.h                                                               */
/* ---------                                                                */
/* Created on 13/11/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

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

	void setCPU(const CPU & cpu_obj); //setter for CPU 
	void setCPUProgram(const CPUProgram & cpu_program_obj); //setter for CPUProgram
	void setMemory(const Memory & memory_obj); //setter for Memory
	const CPU & getCPU()const; //getter for CPU
	const CPUProgram & getCPUProgram()const; // getter for CPUProgram
	const Memory & getMemory()const; //getter for Memory
	int getOption()const; // getter for option
	void setOption(int value); //setter for option
	void execute(); // executes program and prints results on the screen, prints err and exits the execution if error is detected
private:
	CPU my_cpu;
	CPUProgram my_cpu_program;
	Memory my_memory;
	int option;
};

#endif