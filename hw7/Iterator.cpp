#include <cstdlib>
#include "Iterator.h"

namespace MansBT
{
	template<class T>
	Iterator<T>::Iterator()
		:node(NULL)
	{
		//empty body
	}	


	template<class T>
	Iterator<T>::Iterator(LLNode<T>* the_node)
		:node(the_node)
	{
		//empty body
	}

	template<class T>
	T& Iterator<T>::operator *()const
	{
		return node->getData();
	}

	template<class T>
	T* Iterator<T>::operator ->()const
	{
		return &(node->getData());
	}

	template<class T>
	Iterator<T> Iterator<T>::operator ++()
	{
		node = node->getNext();
		return *this;
	}

	template<class T>
	Iterator<T> Iterator<T>::operator ++(int stab)
	{
		Iterator<T> temp_it(node);
		node=node->getNext();
		return temp_it;
	}

	template<class T>
	bool Iterator<T>::operator == (const Iterator<T>& rv)const
	{
		return (node == rv.node);
	}

	template<class T>
	bool Iterator<T>::operator !=(const Iterator<T>& rv)const
	{
		return (node != rv.node);
	}

	template<class T>
	Iterator<T>::operator Const_iterator<T>()const
	{
		return Const_iterator<T>(node);
	}
}
