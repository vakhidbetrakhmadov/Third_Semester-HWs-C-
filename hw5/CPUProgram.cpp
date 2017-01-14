/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPUProgram.cpp                                                           */
/* ---------                                                                */
/* Created on 13/11/2016 by Vakhid_Betrakhmadov                             */
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

 //returns program line as a string, exits the execution if indx is out of range
string & CPUProgram::operator [] (int indx)
{
	if(indx >=file_size)
	{
		cout << "Out of range\n";
		exit(1);
	}
	else
	{
		return line[indx];
	}
}

//overloaded version of [] operator works as for r_value objects (constant objects),
    //exits the execution if indx is out of range
const string & CPUProgram::operator [] (int indx)const
{
	if(indx >=file_size)
	{
		cout << "Out of range\n";
		exit(1);
	}
	else
	{
		return line[indx];
	}
}

// returns a new program consisting of calling program + new string 
const CPUProgram CPUProgram::operator +(string const & str)const
{
	CPUProgram temp;
	temp = (*this);
	temp.line.push_back(str);
	(temp.file_size)++;

	return temp; 
}

// appends a string to the end of the calling program
CPUProgram & CPUProgram::operator += (const string str)
{
	line.push_back(str);
	file_size++;

	return *this;
}

//returns a new program consisting of added to each other programs 
const CPUProgram CPUProgram::operator + (const CPUProgram & r_s)const
{
	CPUProgram temp;
	temp=(*this);
	for (int i = 0; i < r_s.file_size; ++i)
	{
		temp.line.push_back(r_s.line[i]);
	}
	temp.file_size+=r_s.file_size;

	return temp;
}

//compares the number of lines of two programs 
bool CPUProgram::operator == (const CPUProgram & r_s)const
{
	return (file_size==r_s.file_size);
}

//compares the number of lines of two programs 
bool CPUProgram::operator != (const CPUProgram & r_s)const
{
	return (file_size != r_s.file_size);
}

//compares the number of lines of two programs 
bool CPUProgram::operator > (const CPUProgram & r_s)const
{
	return (file_size > r_s.file_size);
}

//compares the number of lines of two programs 
bool CPUProgram::operator < (const CPUProgram & r_s)const
{
	return (file_size < r_s.file_size);
}

//compares the number of lines of two programs 
bool CPUProgram::operator >= (const CPUProgram & r_s)const
{
	return (file_size >= r_s.file_size);
}

//compares the number of lines of two programs 
bool CPUProgram::operator <= (const CPUProgram & r_s)const
{
	return (file_size <= r_s.file_size);
}

// prints on the screen the program
ostream & operator << (ostream & output, const CPUProgram & r_s)
{
	for (int i = 0; i < r_s.file_size; ++i)
	{
		output << r_s.line[i] << endl;
	}
	return output;
}

//pre decrement , deletes the last line from the program,prints err message if program is empty and returns the program
const CPUProgram CPUProgram::operator -- ()
{
	if(file_size==0)
	{
		cout << "Program is empty\n";
		return *this;
	}

	line.pop_back();
	file_size--;
	return (*this);
}

//post decrement , deletes the last line from the file, and returns the state before decrementing,
    //prints err message if program is empty and returns the program
const CPUProgram CPUProgram::operator -- (int stub)
{
	if(file_size==0)
	{
		cout << "Program is empty\n";
		return *this;
	}
	CPUProgram temp(*this);
	line.pop_back();
	file_size--;
	return(temp);
}

 //returns a new program consisting of the lines in between limit1 and limit2 (including),prints err
    //message if out of range and returns empty program
const CPUProgram CPUProgram::operator () (int limit1,int limit2)
{
	CPUProgram temp;
	if(limit2 >=file_size || limit1 >= file_size || limit1 < 0 || limit2 < 0 || limit2<=limit1)
	{
		cout << "Error!\n";
		return temp;
	}
	
	for (int i = limit1; i <= limit2; ++i)
	{
		temp.line.push_back(line[i]);
	}	
	temp.file_size = limit2-limit1+1;

	return temp;
}