/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyLinkedList.java                                                        */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

public class MyLinkedList<T> {

    private MyLLNode<T> head;
    private MyLLNode<T> end;
    int _size;

    public MyLinkedList()
    {
        head = null;
        end = null;
        _size = 0;
    }

    public MyLinkedList(T t)
    {
        head = new MyLLNode<T>(t,null,null);
        end = head;
        _size = 1;
    }

    public int size()
    {
        return _size;
    }

    //ads an element to the end //the same as in LinkedList 
    public void addLast(T t)
    {
        ++_size;

        if(end == null)
        {
            end = new MyLLNode<T>(t,null,null);
            head = end;
        }
        else if(end == head )
        {
            head.setNode(new MyLLNode<T>(t,null,head));
            end = head.getNode();
        }
        else
        {
            end.setNode(new MyLLNode<T>(t,null,end));
            end = end.getNode();
        }
    }

    //ads an element to the begining //the same as in LinkedList 
    public void addFirst(T t)
    {
        ++_size;

        if(head== null)
        {
            head = new MyLLNode<T>(t,null,null);
            end = head;
        }
        else if(head == end)
        {
            head = new MyLLNode<T>(t,end,null);
            end.setPrevious(head);
        }
        else
        {
            head = new MyLLNode<T>(t,head,null);
            head.getNode().setPrevious(head);
        }
    }

    //returns the first elemet //the same as in LinkedList 
    public T element()
    {
        return head.getData();
    }

    //returns the element indicated by it's index //the same as in LinkedList 
    public T get(int index)throws Exception
    {
        if(index >= size())
        {
            throw  new Exception("Out of range index in LinkedList method get()");
        }

        MyIterator<T> it = this.ListIterator();
        while(it.hasNext() && it.nextIndex()!= index)
        {
            it.next();
        }

        return it.next();
    }

    //the same as in LinkedList 
    public boolean contains(T t)
    {
        boolean found = false;
        MyIterator<T> it = this.ListIterator();
        while(it.hasNext() && !found)
        {
            if(it.next().equals(t))
                found = true;
        }

        return found;
    }

    //the same as in LinkedList 
    public int indexOf(T t)
    {
        if(!contains(t))
        {
            return -1;
        }

        int indx = 0;
        MyIterator<T> it = this.ListIterator();
        while(it.hasNext() && !it.next().equals(t))
        {
            ++indx;
        }

        return  indx;
    }

    //the same as in LinkedList 
    public T remove(int index)throws Exception
    {
        if(index >= size())
        {
            throw  new Exception("Out of range index in LinkedList method remove()");
        }

        MyLinkedListIterator<T> it = new MyLinkedListIterator<>(this);
        while(it.hasNext() && it.nextIndex() != index)
        {
            it.next();
        }

        T toReturn= it.peek();
        it.remove();

        return toReturn;
    }

    public void clear()
    {
        head = null;
        end = null;
        _size = 0;
    }

    //the same as in LinkedList 
    public MyIterator<T> ListIterator()
    {
        return new MyLinkedListIterator<>(this);
    }


    // the same as the ListIterator 
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private class MyLinkedListIterator<T> implements MyIterator<T>
    {
        private MyLinkedList<T> list;
        private MyLLNode <T> node;
        int index;

        public MyLinkedListIterator(MyLinkedList<T> _list)
        {
            list = _list;
            node = _list.head;
            index=0;
        }

        public boolean hasNext()
        {
            return node!=null;
        }

        public boolean hasPrevious()
        {
            return node.getPrevious()!=null;
        }

        public int nextIndex()
        {
            if(node == null)
            {
                return list._size;
            }

            return index;
        }

        public int previousIndex()
        {
            if(node == list.head)
            {
                return  -1;
            }

            return index-1;
        }

        public T next()
        {
            ++index;
            T toReturn = node.getData();
            node = node.getNode();

            return toReturn;
        }

        public T previous()
        {
            --index;
            node = node.getPrevious();
            return node.getData();
        }

        public T peek()
        {
            return node.getData();
        }

        public void set(T t)
        {
            if(list.head == null && node == null)
            {
                ++list._size;
                list.head = new MyLLNode<T>(t,null,null);
                list.end = list.head;
                node = list.head;
            }
            else
            {
                node.setData(t);
            }
        }

        public void add(T t)
        {
            ++list._size;

            if(list.head==null && node == null)
            {
                list.head = new MyLLNode<T>(t,null,null);
                list.end = list.head;
                node = list.head;
            }
            else if(node == null)
            {
                list.end.setNode(new MyLLNode<T>(t,null,list.end));
                list.end = list.end.getNode();
            }
            else
            {
                if(node == list.head)
                {
                    list.head = new MyLLNode<T>(t,node,null);
                    node.setPrevious(list.head);
                }
                else
                {
                    MyLLNode temp = new MyLLNode<T>(t,node,node.getPrevious());
                    node.getPrevious().setNode(temp);
                    node.setPrevious(temp);
                }
            }
        }

        public void remove()
        {
            if(list._size > 0)
            {
                --list._size;
            }

            if(node != null)
            {
                if(node == list.head)
                {
                    if(list.head == list.end)
                    {
                        list.head=null;
                        list.end=null;
                        next();
                    }
                    else
                    {
                        list.head = list.head.getNode();
                        list.head.setPrevious(null);
                        node = list.head;
                    }
                }
                else
                {
                    if(node == list.end)
                    {
                        list.end = list.end.getPrevious();
                        list.end.setNode(null);
                    }
                    node.getPrevious().setNode(node.getNode());
                    if(node.getNode()!=null)
                        node.getNode().setPrevious(node.getPrevious());

                    next();
                }
            }
        }

        public boolean equals(Object o)
        {
            if(this == o) return true;
            if(o instanceof MyLinkedListIterator)
            {
                MyLinkedListIterator<T> other = (MyLinkedListIterator<T>) o;
                return (node == other.node);
            }
            return  false;
        }
    }
}
