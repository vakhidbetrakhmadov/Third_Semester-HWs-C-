#include <cstdlib> 
#include "LLNode.h"

namespace MansBT
{
	//comment here
	template<class T>
	LLNode<T>::LLNode()
		:data(T()),next(NULL)
	{
		//empty body
	}

	template<class T>
	LLNode<T>::LLNode(const T& the_data,LLNode<T>* the_next)
		:data(the_data),next(the_next)
	{
		//empty body
	}

	template<class T>
	const T& LLNode<T>::getData()const
	{
		return data;
	}

	template<class T>
	T& LLNode<T>::getData()
	{
		return data;
	}

	template<class T>
	void LLNode<T>::setData(const T& the_data)
	{
		data=the_data;
	}

	template<class T>
	LLNode<T>* LLNode<T>::getNext()const
	{
		return next;
	}

	template<class T>
	void LLNode<T>::setNext(LLNode<T>* the_next)
	{
		next = the_next;
	}	
}
