#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>
#include <exception>

#include "Bigram.h"
#include "BigramMap.h"
#include "BigramDyn.h"
#include "MyExeption.h"
#include "BigramMap.cpp"
#include "BigramDyn.cpp"


using std::cout;
using std::string;
using std::exit;
using std::endl;
using std::pair;
using std::exception ;
using MansBT::Bigram;
using MansBT::MyExeption;
using MansBT::BigramMap;
using MansBT::BigramDyn;


enum Option_t {INT=1,STRING,DOUBLE,BIFRAM_MAP,BIGRAM_DYN};

#if 1
template<class T>
void myTest(Bigram<T>& my_bigram,const char* filename)
{
	try
	{
		my_bigram.readFile(filename);
		cout << "numGrams() : " << my_bigram.numGrams() << endl;
		pair<T,T> temp_pair = my_bigram.maxGrams();
		cout << "numOfGrams(" << temp_pair.first << "," << temp_pair.second << ") : " << my_bigram.numOfGrams(temp_pair.first,temp_pair.second) << endl;
		cout << my_bigram << endl;
		cout << " maxGrams() : {" << my_bigram.maxGrams().first << "," << my_bigram.maxGrams().second << "}" <<endl;
	}
	catch(const exception & e)
	{
		cout << e.what() << endl;
	}
}
#endif


int main(int argc, char const *argv[])
{
	const char* filename = argv[1];
	const int opt1=atoi(argv[2]);
	const int opt2= atoi(argv[3])+3;
	
	if (opt1 < INT || opt1 > DOUBLE || opt2 < BIFRAM_MAP || opt2 > BIGRAM_DYN)
	{
		cout << "Inappropriate options\n Exiting program...\n";
		exit(1);
	}

	BigramMap<int> my_bigram_map_int;
	BigramMap<string> my_bigram_map_string;
	BigramMap<double> my_bigram_map_double;

	BigramDyn<int> my_bigram_dyn_int;
	BigramDyn<string> my_bigram_dyn_string;
	BigramDyn<double> my_bigram_dyn_double;

#if 1
	switch (opt1)
	{
		case INT:
		{
			switch(opt2)
			{
				case BIFRAM_MAP:cout << 1 <<" " << 1 << endl; myTest(my_bigram_map_int,filename);break;
				case BIGRAM_DYN:cout << 1 <<" " << 2 << endl; myTest(my_bigram_dyn_int,filename);break;
				default:break;
			}
		}break;

		case STRING:
		{
			switch(opt2)
			{
				case BIFRAM_MAP:cout << 2 <<" " << 1 << endl; myTest(my_bigram_map_string,filename);break;
				case BIGRAM_DYN:cout << 2 <<" " << 2 << endl; myTest(my_bigram_dyn_string,filename);break;
				default:break;
			}
		}break;

		case DOUBLE:
		{
			switch(opt2)
			{
				case BIFRAM_MAP:cout << 3 <<" "<< 1 << endl; myTest(my_bigram_map_double,filename);break;
				case BIGRAM_DYN:cout << 3 <<" "<< 2 << endl; myTest(my_bigram_dyn_double,filename);break;
				default:break;
			}
		}break;

		default:break;
	}
#endif

	return 0;
}