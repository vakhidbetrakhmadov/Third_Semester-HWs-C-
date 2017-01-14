/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Computer.cpp                                                             */
/* ---------                                                                */
/* Created on 13/11/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <cstdlib>

#include "Memory.h"
#include "CPU.h"
#include "CPUProgram.h"
#include "Computer.h"

using namespace std;

Computer::Computer(int option_value)
		:option(option_value)
{
	/*empty body*/
}

Computer::Computer( const CPU & cpu_obj,const CPUProgram & cpu_program_obj,Memory const & memory_obj,int option_value)
		: my_cpu(cpu_obj),my_cpu_program(cpu_program_obj),my_memory(memory_obj),option(option_value)
{
	/*empty body*/
}

void Computer::setCPU(const CPU & cpu_obj)
{
	my_cpu=cpu_obj;
}

void Computer::setCPUProgram(const CPUProgram & cpu_program_obj)
{
	my_cpu_program=cpu_program_obj;
}

void Computer::setMemory(const Memory & memory_obj)
{
	my_memory=memory_obj;
}

const CPU & Computer::getCPU()const
{
	return my_cpu;
}

const CPUProgram & Computer::getCPUProgram()const
{
	return my_cpu_program;
}

const Memory & Computer::getMemory()const
{
	return my_memory;
}

int Computer::getOption()const
{
	return option;
}

void Computer::setOption(int value)
{
	if(!(value >=0 && value <=2))
	{
		cerr << "Option flag is set incorrect.\n";
	}
	else
	{
		option = value;
	}	
}

// executes program and prints results on the screen, prints err and exits the execution if error is detected
void Computer::execute()
{
	string instruction;

	if(!(getOption() >=0 && getOption()<=2))
	{
		cerr << "Option flag is set incorrect.\n"
		<< "Please try running the program again!\n";
	    exit(1);
	}

	my_cpu.setPc(1);

	while(!my_cpu.halted())
    {
        instruction = my_cpu_program.getLine(my_cpu.getPc()-1);
        my_cpu.validate(instruction,my_cpu_program.size());
        if(my_cpu.error())
        {
            cout << "Syntax error is detected...\n"
                    << "Exiting the program\n";       
        }
        if(!my_cpu.error())
        {      	
            my_cpu.execute(instruction,my_memory);
            if(getOption()==1)
            {
            	cout << instruction.substr(0,instruction.size()-1)<<endl;
            	if(!my_cpu.halted())
            	{
            		my_cpu.print();
            		cout << "PC="<< my_cpu.getPc() << endl << endl;
            	}
            }
            else if(getOption()==2)
            {
            	cout << instruction.substr(0,instruction.size()-1)<<endl;
            	if(!my_cpu.halted())
            	{
            		my_cpu.print();
            		cout << "PC="<< my_cpu.getPc() << endl;
            		my_memory.printAll();
            		cout << endl;
            	}
            }
        }
    }
}