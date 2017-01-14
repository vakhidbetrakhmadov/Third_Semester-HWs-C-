/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Memory.h                                                            	    */
/* ---------                                                                */
/* Created on 25/10/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
public:
	Memory(int option_value=-1);
	void setMem(int indx,int value);
	int getMem(int indx)const;
	void printAll()const;
private:
	int cell[50];
	int MEM_SIZE;
	int option;
};


#endif