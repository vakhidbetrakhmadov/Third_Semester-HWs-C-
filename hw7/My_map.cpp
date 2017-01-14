#include <utility>
#include <cstdlib>

#include "My_map.h"

using std::pair;

namespace MansBT 
{
	template <class T,class U>
	My_map<T,U>::My_map()
		:head(NULL),_size(0)
	{
		//empty body
	}	

	template<class T,class U>
	My_map<T,U>::My_map(const T& key, const U& mapped)
		:head(new LLNode<pair<T,U> >(pair<T,U>(key,mapped),NULL)),_size(1)
	{
		//empty body
	}

	template<class T,class U>
	My_map<T,U>::My_map(const My_map<T,U>& sample)
	{
		if(sample.size()==0)
		{
			head = NULL;
			_size=0;
		}
		else
		{	
			_size=sample._size;
			typename My_map<T,U>::iterator it = sample.begin();
			head = new LLNode<pair<T,U> >(*it,NULL);
			++it;

			LLNode<pair<T,U> > * next = head;
			while(it!=sample.end())
			{
				next->setNext(new LLNode<pair<T,U> >(*it,NULL));
				next=next->getNext();
				++it;
			}
		}
	}

	template<class T,class U>
	void My_map<T,U>::clear()
	{
		LLNode<pair<T,U> > * discard;
		LLNode<pair<T,U> > * next = head;
		while(next!=NULL)
		{
			discard=next;
			next=next->getNext();
			delete discard;
		}
		head=NULL;	
		_size=0;
	}

	template<class T,class U>
	My_map<T,U>& My_map<T,U>::operator =(const My_map<T,U>& rv)
	{
		if(this == &rv)
		{
			return *this;
		}

		if(rv.size()==0)
		{
			clear();
			head = NULL;
			_size=0;
			return *this;
		}
		else
		{	
			if(size() > 0)
			{
				clear();
			}

			_size=rv._size;
			typename My_map<T,U>::iterator it = rv.begin();
			head = new LLNode<pair<T,U> >(*it,NULL);
			++it;

			LLNode<pair<T,U> > * next = head;
			while(it!=rv.end())
			{
				next->setNext(new LLNode<pair<T,U> >(*it,NULL));
				next=next->getNext();
				++it;
			}
		}
	}

	template<class T,class U>
	Iterator<pair<T,U> > My_map<T,U>::find(const T& key)const
	{
		typename My_map<T,U>::iterator it = begin();
		while(it!=end())
		{
			if(it->first == key)
			{
				return it;
			}
			++it;
		}

		return end();
	}

	template<class T,class U>
	Iterator<pair<T,U> > My_map<T,U>::insertInOrder(const pair<T,U>& the_pair)
	{
		LLNode<pair<T,U> >* to_return;

		if(size()==0)
		{
			to_return=new LLNode<pair<T,U> >(the_pair,NULL);
			head=to_return;
		}
		else
		{
			if(the_pair.first < head->getData().first)
			{
				to_return=new LLNode<pair<T,U> >(the_pair,head);
				head = to_return;
			}
			else
			{	
				LLNode<pair<T,U> >* current = head;
				LLNode<pair<T,U> >* next = head->getNext();
				while(next!=NULL && (the_pair.first > next->getData().first))
				{
					current = next;
					next = next->getNext();
				}
				to_return=new LLNode<pair<T,U> >(the_pair,next);
				current->setNext(to_return);
			}
		}
		
		return Iterator<pair<T,U> >(to_return);
	}

	template<class T,class U>
	U& My_map<T,U>::operator[](const T& key)
	{
		Iterator<pair<T,U> > it = find(key);
		if(it!=end())
		{
			return it->second;
		}

		pair<T,U> to_isert(key,U());
		it=insertInOrder(to_isert);
		_size++;
		return it->second;
	}

	template<class T,class U>
	int My_map<T,U>::size()const
	{
		return _size;
	}

	template<class T,class U>
	void My_map<T,U>::erase(const T& key)
	{
		if(size()>0)
		{
			if(key == head->getData().first)
			{	
				LLNode<pair<T,U> >* discard = head;
				head = head->getNext();
				_size--;
				delete discard;
			}
			else
			{
				LLNode<pair<T,U> >* current = head;
				LLNode<pair<T,U> >* next = head->getNext();
				while(next!=NULL && !(key == next->getData().first))
				{
					current = next;
					next = next->getNext();
				}
				
				if(next!=NULL)
				{
					LLNode<pair<T,U> >* discard =next;
					current->setNext(next->getNext());
					_size--;
					delete discard;
				}
			}
		}	
	}

	template<class T,class U>
	Iterator<pair<T,U> > My_map<T,U>::begin()const
	{
		return Iterator<pair<T,U> >(head);
	}

	template<class T,class U>
	Iterator<pair<T,U> > My_map<T,U>::end()const
	{
		return Iterator<pair<T,U> >();
	}

	template<class T,class U>
	My_map<T,U>::~My_map()
	{
		clear();
	}
}