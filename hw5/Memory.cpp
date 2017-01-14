/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Memory.cpp                                                               */
/* ---------                                                                */
/* Created on 13/11/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>

#include "Memory.h"

using namespace std;

Memory::Memory(int option_value) 
	: MEM_SIZE(50),option(option_value)
{

	for (int i = 0; i < MEM_SIZE; ++i)
	{
		cell[i]=0;
	}
}

void Memory::setMem(int indx,int value)
{
	if(indx >= 50)
	{
		cerr << "The adress is out of memory range" <<endl;
	}
	else
	{
		cell[indx]=value;
	}
}

int Memory::getMem(int indx)const
{
if(indx >= 50)
	{
		cerr << "The adress is out of memory range" <<endl;
	}
	else
	{
		return cell[indx];
	}
}

void Memory::printAll()const
{
	for (int i = 0; i < MEM_SIZE; ++i)
	{
		cout <<"["<<i<<"]"<<" -> "<<cell[i]<<endl;  
	}
}