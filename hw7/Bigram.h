/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Bigram.h                                                                 */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#ifndef BIGRAM_H
#define BIGRAM_H

#include <iostream>
#include <string>
#include <utility>

#include "MyExeption.h"

using std::ostream;
using std::string;
using std::pair;

namespace MansBT
{
	template<class T>
	class Bigram
	{
	public:
		//reads input file and and stores all bigrams computed into the map (throws exception if err while opening a file or reading a file occures) 
		virtual void readFile(const string& filename)throw(MyExeption) = 0;
		//returns num of bugrams read so far
		virtual int numGrams()const = 0;
		//returns the occurence num of the give bugram
		virtual int numOfGrams(const T& first,const T& second)const = 0 ;
		//return bigram with the biggest accurence num
		virtual pair<T,T> maxGrams()const throw(MyExeption) = 0 ;

		//prints bigram to the screen in decreasing order(according to the number of occurences) 
		friend ostream& operator<< (ostream& out,const Bigram<T>& rv)
		{
			rv.print_to(out);
			return out;
		}
		
	private:
		//helper function  for << operator
		virtual void print_to(ostream & out )const =0;
	};
}

#endif