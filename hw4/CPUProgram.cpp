/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPUProgram.cpp                                                           */
/* ---------                                                                */
/* Created on 25/10/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#include "CPUProgram.h"

using namespace std;

CPUProgram::CPUProgram(int option_value)
	: file_size(0),option(option_value)
{
	/*empty body*/
}

//prints error message and exits the programm if  problem in opening file occures ,calls ReadFile
CPUProgram::CPUProgram(char const * c_str)
        : file_size(0)
{
    ReadFile(c_str);
}

//opens file and reads it into the string vector,prints error message and exits the programm if problem in opening file occures
void CPUProgram::ReadFile(char const* name)
{
    ifstream file;

    file.open(name);
    if(file.fail())
    {
        cerr << "File could not be opened.\nExiting the program ... \n";
        exit(1);
    }
    
    string temp_str;
    while(getline(file,temp_str))
    {
        ++file_size;
        line.push_back(temp_str);
    }
    
    file.close();
}

string CPUProgram::getLine(int line_num)const
{
    return (line[line_num]);
}

int CPUProgram::size()const
{
    return file_size;
}