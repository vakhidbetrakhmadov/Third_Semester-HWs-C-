/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* main.cpp                                                                 */
/* ---------                                                                */
/* Created on 25/10/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "CPUProgram.h"
#include "CPU.h"

using namespace std;

int main(int argc, char** argv)
{
    CPUProgram my_cpu_program(argv[1],argv[2]);
    CPU my_cpu;
    string instruction;
    
    while(!my_cpu.halted())
    {
        instruction = my_cpu_program.getLine(my_cpu.getPc());
        my_cpu.validate(instruction,my_cpu_program.size());
        if(my_cpu.error())
        {
            cout << "Syntax error is detected...\n"
                    << "Exiting the program\n";
            
        }
        if(!my_cpu.error())
        {
            my_cpu.execute(instruction);
            my_cpu.print(my_cpu_program.getMode(),instruction);
        }
    }

    if(!my_cpu.error())
    {
        my_cpu.print();
    }
    
    return 0;
}