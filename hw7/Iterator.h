/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Iiterator.h                                                              */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#ifndef ITERATOR_H
#define ITERATOR_H

#include "LLNode.h"
//#include "Const_iterator.h"

namespace MansBT
{
	template<class T>
	class Const_iterator;

	template<class T>
	class Iterator
	{
	public:
		Iterator();
		Iterator(LLNode<T>* the_node);
		//dereffrence operator overload, works as standard
		T& operator *()const;
		//arrow operator overload,works as standard
		T* operator ->()const;
		// ++ operator overload,works as standard
		Iterator<T> operator ++();
		//post ++ operator ovearload,works as standard
		Iterator<T> operator ++(int stab);
		//== operator ovearload,works as standard
		bool operator == (const Iterator<T>& rv)const;
		//!=operator overload,works as standard
		bool operator !=(const Iterator<T>& rv)const;
		//type convertion operator
		operator Const_iterator<T>()const;
	protected:
		LLNode<T>* node;
	};
}

#endif


