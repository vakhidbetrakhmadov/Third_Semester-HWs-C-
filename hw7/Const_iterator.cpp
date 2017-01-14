#include <cstdlib>
#include "Const_iterator.h"

namespace MansBT
{
	template<class T>
	Const_iterator<T>::Const_iterator()
		:Iterator<T>()
	{
		//empty body
	}	


	template<class T>
	Const_iterator<T>::Const_iterator(LLNode<T>* the_node)
		:Iterator<T>(the_node)
	{
		//empty body
	}

	template<class T>
	const T& Const_iterator<T>::operator *()const
	{
		return Iterator<T>::node->getData();
	}

	template<class T>
	const T* Const_iterator<T>::operator ->()const
	{
		return &(Iterator<T>::node->getData());
	}
}
