/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW06_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* CPUProgramDyn.cpp                                                        */
/* ---------                                                                */
/* Created on 26/11/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "CPUProgramDyn.h"

using namespace std;

//nameless namespace
namespace
{
	//helper function to count number of lines in the file (before exiting sets filepointer to the begining)
	int countLines(ifstream& file)
	{
		int count=0;
		string temp;
		while(getline(file,temp))
	    {
	        ++count;
	    }
	    file.clear();
	    file.seekg(0,file.beg);

	    return count;
	}
}

namespace CPUPD
{
	CPUProgramDyn::CPUProgramDyn(int option_value)
		: file_size(0),option(option_value),capacity(0),line(NULL)
	{
		/*empty body*/
	}

	//prints error message and exits the programm if  problem in opening file occures ,calls ReadFile
	CPUProgramDyn::CPUProgramDyn(char const * c_str)
	        : file_size(0),option(-1),capacity(0),line(NULL)
	{
	    ReadFile(c_str);
	}

	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& sample)
		:file_size(sample.file_size),option(sample.option),capacity(sample.capacity)
	{
		line = new string[capacity];

		for (int i = 0; i < file_size; ++i)
		{
			line[i]=sample.line[i];
		}
	}

	CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& r_s)
	{
		if(this==&r_s)
			return *this;

		file_size=r_s.file_size;
		option=r_s.option;
		capacity=r_s.capacity;

		delete [] line;
		line = new string[capacity];

		for (int i = 0; i < file_size; ++i)
		{
			line[i]=r_s.line[i];
		}

		return *this;
	}

	//opens file and reads it into the string vector,prints error message and exits the programm if problem in opening file occures
	void CPUProgramDyn::ReadFile(char const* name)
	{
	    ifstream file;

	    file.open(name);
	    if(file.fail())
	    {
	        cerr << "File could not be opened.\nExiting the program ... \n";
	        exit(1);
	    }
	    
	    if(capacity!=0)
	    {
	    	delete [] line;
	    }

	   	capacity=countLines(file);
	   	file_size=capacity;
	   	line = new string[capacity];

	    for (int i = 0; i < file_size; ++i)
	    {
	    	getline(file,line[i]);
	    }
	    
	    file.close();
	}

	string CPUProgramDyn::getLine(int line_num)const
	{
		if(line_num >=file_size)
		{
			cout << "Error! Out of range\n";
			string str="";
			return str;
		}

	    return (line[line_num]);
	}

	int CPUProgramDyn::size()const
	{
	    return file_size;
	}

	 //returns program line as a string, exits the execution if indx is out of range
	string & CPUProgramDyn::operator [] (int indx)
	{
		if(indx >=file_size)
		{
			cout << "Error! Out of range, returning the last line ... ";
			return line[file_size-1];
		}
		else
		{
			return line[indx];
		}
	}

	//overloaded version of [] operator works as for r_value objects (constant objects),
	    //exits the execution if indx is out of range
	const string & CPUProgramDyn::operator [] (int indx)const
	{
		if(indx >=file_size)
		{
			cout << "Error! Out of range, returning the last line ... ";
			return line[file_size-1];
		}
		else
		{
			return line[indx];
		}
	}

	//adds a string ellement to the end of the dynamic arr of strings "line" and increments size,
        //if arr is full, doubles capacity and adds a string ellement incrementing size 
	void CPUProgramDyn::addLine(const string& str)
	{
		if(capacity==file_size)
		{
			CPUProgramDyn temp = *this;
			delete [] line;
			if(capacity==0)
			{
				capacity=10;
			}
			capacity*=2;
			line = new string[capacity];
			for (int i = 0; i < file_size; ++i)
			{
				line[i]=temp[i];
			}
		}
		
		line[file_size]=str;
		file_size++;
	}

	// returns a new program consisting of calling program + new string 
	const CPUProgramDyn CPUProgramDyn::operator +(string const & str)const
	{
		CPUProgramDyn temp;
		temp = (*this);
		temp.addLine(str);

		return temp; 
	}

	// appends a string to the end of the calling program
	CPUProgramDyn & CPUProgramDyn::operator += (const string str)
	{
		this->addLine(str);

		return *this;
	}

	//returns a new program consisting of added to each other programs 
	const CPUProgramDyn CPUProgramDyn::operator + (const CPUProgramDyn & r_s)const
	{
		CPUProgramDyn temp;
		temp=(*this);
		for (int i = 0; i < r_s.file_size; ++i)
		{
			temp.addLine(r_s.line[i]);
		}

		return temp;
	}

	//compares the number of lines of two programs 
	bool CPUProgramDyn::operator == (const CPUProgramDyn & r_s)const
	{
		return (file_size==r_s.file_size);
	}

	//compares the number of lines of two programs 
	bool CPUProgramDyn::operator != (const CPUProgramDyn & r_s)const
	{
		return (file_size != r_s.file_size);
	}

	//compares the number of lines of two programs 
	bool CPUProgramDyn::operator > (const CPUProgramDyn & r_s)const
	{
		return (file_size > r_s.file_size);
	}

	//compares the number of lines of two programs 
	bool CPUProgramDyn::operator < (const CPUProgramDyn & r_s)const
	{
		return (file_size < r_s.file_size);
	}

	//compares the number of lines of two programs 
	bool CPUProgramDyn::operator >= (const CPUProgramDyn & r_s)const
	{
		return (file_size >= r_s.file_size);
	}

	//compares the number of lines of two programs 
	bool CPUProgramDyn::operator <= (const CPUProgramDyn & r_s)const
	{
		return (file_size <= r_s.file_size);
	}

	// prints on the screen the program
	ostream & operator << (ostream & output, const CPUProgramDyn & r_s)
	{
		for (int i = 0; i < r_s.file_size; ++i)
		{
			output << r_s.line[i] << endl;
		}
		return output;
	}

	//pre decrement , deletes the last line from the program,prints err message if program is empty and returns the program
	const CPUProgramDyn CPUProgramDyn::operator -- ()
	{
		if(file_size==0)
		{
			cout << "Program is empty\n";
			return *this;
		}

		line[file_size-1]="";
		file_size--;
		return (*this);
	}

	//post decrement , deletes the last line from the file, and returns the state before decrementing,
	    //prints err message if program is empty and returns the program
	const CPUProgramDyn CPUProgramDyn::operator -- (int stub)
	{
		if(file_size==0)
		{
			cout << "Program is empty\n";
			return *this;
		}
		CPUProgramDyn temp(*this);
		line[file_size-1]="";
		file_size--;
		return(temp);
	}

	 //returns a new program consisting of the lines in between limit1 and limit2 (including),prints err
	    //message if out of range and returns empty program
	const CPUProgramDyn CPUProgramDyn::operator () (int limit1,int limit2) const
	{
		CPUProgramDyn temp;
		if(limit2 >=file_size || limit1 >= file_size || limit1 < 0 || limit2 < 0 || limit2<=limit1)
		{
			cout << "Error!\n";
			return temp;
		}
		
		for (int i = limit1; i <= limit2; ++i)
		{
			temp.addLine(line[i]);
		}	
		temp.file_size = limit2-limit1+1;

		return temp;
	}

	CPUProgramDyn::~CPUProgramDyn()
	{
		delete [] line;
	}
}