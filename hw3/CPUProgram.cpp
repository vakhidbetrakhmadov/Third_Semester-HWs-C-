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

//prints error message and exits the programm if either problem in opening file occures or cmd parameter is wrong,calls readFile
CPUProgram::CPUProgram(char const * c_str,char const* num)
        : file_name(c_str),mode(num),file_size(0)
{
    if(!(mode=="0" || mode =="1"))
    {
        cerr << "Option flag is set incorrect.\n"
		<< "Please try running the program again!\n";
        exit(1);
    }
    readFile(file_name);
}

//opens file and reads it into the string vector,prints error message and exits the programm if problem in opening file occures
void CPUProgram::readFile(char const* name)
{
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
    return (line[line_num-1]);
}

int CPUProgram::size()const
{
    return file_size;
}

string CPUProgram::getMode()const
{
    return (mode);
}