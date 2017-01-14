/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* BigramDyn.h                                                              */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#ifndef BIGRAM_DYN_H
#define BIGRAM_DYN_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Bigram.h"
#include "MyExeption.h"
#include "My_map.h"


using std::ostream;
using std::string;
using std::pair;
using std::vector;

namespace MansBT
{
	template<class T>
	class BigramDyn:public Bigram<T>
	{
	public:
		BigramDyn();
		BigramDyn(int value);
		//reads input file and and stores all bigrams computed into the map (throws exception if err while opening a file or reading a file occures) 
		virtual void readFile(const string& filename) throw(MyExeption);
		//returns num of bugrams read so far
		virtual int numGrams()const;
		//returns the occurence num of the give bugram
		virtual int numOfGrams(const T& first,const T& second)const;
		//return bigram with the biggest accurence num(throws exception if there is no bigram to return,not an empty object like {0,0} for ex. cuz might be confusing)
		virtual pair<T,T> maxGrams()const throw(MyExeption);
	private:
		My_map<pair<T,T>,int> my_map;

		//helper function for readFile
		void fillMap(const vector<T>& vect);
		//helper function  for << operator
		virtual void print_to(ostream & out )const;
	};
}

#endif