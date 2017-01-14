#include <iostream>
#include <string>
#include <utility>	
#include <fstream>
#include <vector>

#include "MyExeption.h"
#include "BigramDyn.h"
#include "My_map.h"
#include "My_map.cpp"



using std::ostream;
using std::string;
using std::pair;
using std::ifstream;
using std::vector;
using std::endl;



namespace MansBT
{	
	template<class T>
	void BigramDyn<T>::fillMap(const vector<T>& vect)
	{
		if(my_map.size()>0)
		{
			my_map.clear();
		}
		
		for (int i = 0; i < vect.size()-1; ++i)
		{
			pair<T,T> temp_pair(vect[i],vect[i+1]);
			if(my_map.find(temp_pair)==my_map.end())
			{
				for (int j = i; j < vect.size()-1; ++j)
				{
					if(temp_pair == pair<T,T>(vect[j],vect[j+1]))
					{
						if(my_map.find(temp_pair)==my_map.end())
						{
							my_map[temp_pair]=1;
						}		
						else
						{
							my_map[temp_pair]+=1;
						}
					}	
				}
			}
		}		
	}

	template<class T>
	BigramDyn<T>::BigramDyn()
		:my_map()
	{
		//empty body
	}

	template<class T> 
	BigramDyn<T>::BigramDyn(int value)
		:my_map()
	{
		//empty body
	}

	template<class T> 
	void BigramDyn<T>::readFile(const string& filename)throw(MyExeption)
	{
		ifstream file(filename.c_str());
		if(!file.is_open())
		{
			throw MyExeption("Error while opening file");
		}

		vector<T> my_vector;  
		T data;
		while(!file.eof() && !file.fail())
		{
			file >> data;
			my_vector.push_back(data);	
		}
		if(file.fail() && !file.eof())
		{
			throw MyExeption("Error while reading data from file");
		}	

		fillMap(my_vector);
	}

	template<class T>
	int BigramDyn<T>::numGrams()const
	{
		int count = 0;

		typename My_map<pair<T, T>, int>::const_iterator  it = my_map.begin();
		
		for (/*nothing*/; it != my_map.end(); ++it)
		{
			count+=it->second;
		}
		
		return count;
	}

	template<class T>
	int BigramDyn<T>::numOfGrams(const T& first,const T& second)const
	{
		if(my_map.find(pair<T,T>(first,second)) != my_map.end())
		{
			 return my_map.find(pair<T,T>(first,second))->second; // map has no overload of operator[] for const
		}
		else
		{
			return 0;
		}
		
	}


	template<class T>
	void BigramDyn<T>::print_to(ostream & out )const
	{
		BigramDyn<T> temp_bigram_map = *this;
		while(temp_bigram_map.my_map.size()!=0)
		{
			out <<"{" << temp_bigram_map.maxGrams().first << "," << temp_bigram_map.maxGrams().second << "} ";
			temp_bigram_map.my_map.erase(temp_bigram_map.maxGrams());
		}
	}
	
	template<class T>
	pair<T,T> BigramDyn<T>::maxGrams()const throw(MyExeption)
	{
		if(my_map.size()==0)
		{
			throw MyExeption("There are no bigrams\nmaxGram function can not return anything...");
		}

		typename My_map<pair<T, T>, int>::const_iterator  it = my_map.begin();
		typename My_map<pair<T, T>, int>::const_iterator  it_max = it;
		for (/*nothing*/; it != my_map.end(); ++it)
		{
			if (it->second > it_max->second)
			{
				it_max=it;
			}
		}

		return it_max->first;
	}		
}

