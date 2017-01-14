/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW07_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* LLNode.h                                                                 */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#ifndef LLNODE_H
#define LLNODE_H

namespace MansBT
{
	template<class T>
	class LLNode
	{
	public:
		LLNode();
		LLNode(const T& the_data,LLNode<T>* the_next);
		const T& getData()const;
		T& getData();
		void setData(const T& the_data);
		LLNode<T>* getNext()const;
		void setNext( LLNode<T>* the_next);
	private:
		T data;
		LLNode<T>* next;
	};
}

#endif
