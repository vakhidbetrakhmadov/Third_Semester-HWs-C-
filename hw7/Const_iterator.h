/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Const_iterator.h                                                         */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include "LLNode.h"
#include "Iterator.h"

namespace MansBT
{
	template<class T>
	class Const_iterator:public Iterator<T>
	{
	public:
		Const_iterator();
		Const_iterator(LLNode<T>* the_node);
		//dereffrence operator overload, works as standard
		const T& operator *()const;
		//arrow operator overload,works as standard
		const T* operator ->()const;
	protected:

	};
}

#endif