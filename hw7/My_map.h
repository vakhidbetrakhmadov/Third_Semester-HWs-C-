/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* My_map.h                                                                 */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#ifndef MY_MAP_H
#define MY_MAP_H

#include <utility>

#include "Iterator.h"
#include "Iterator.cpp"
#include "Const_iterator.h"
#include "Const_iterator.cpp"
#include "LLNode.h"
#include "LLNode.cpp"

using std::pair;

namespace MansBT
{
	template <class T,class U>
	class My_map
	{
	public:
		typedef T key_type;
		typedef U mapped_type;
		typedef Iterator<pair<T,U> > iterator;
		typedef Const_iterator<pair<T,U> > const_iterator;

		My_map();
		My_map(const T& key, const U& mapped);
		My_map(const My_map<T,U>& sample);//standard
		My_map<T,U>& operator =(const My_map<T,U>& rv); //standard
		Iterator<pair<T,U> > find(const T& key)const; // work the same as std::map's find method
		U& operator[](const T& key);// work the same as std::map's find method
		int size()const;// work the same as std::map's find method
		void erase(const T& key);// work the same as std::map's find method
		void clear();// work the same as std::map's find method
		Iterator<pair<T,U> > begin()const;// work the same as std::map's find method
		Iterator<pair<T,U> > end()const;// work the same as std::map's find method
		
		virtual ~My_map(); //destructor

	private:
		LLNode<pair<T,U> > * head;
		int _size;

		//helper function for [] operator
		Iterator<pair<T,U> > insertInOrder(const pair<T,U>& the_pair);
	};
}

#endif