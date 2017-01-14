/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyVector.java                                                            */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
public class MyVector<T> {
    Object[] arr;
    int _size;
    int capacity;

    public MyVector()
    {
        arr = null;
        _size = 0;
        capacity = 0;

    }

    public MyVector(int initSize)
    {
        arr = new Object[initSize];
        _size = 0;
        capacity = initSize;
    }

    //adds element to the end
    public boolean add(T t)
    {
        if(capacity == 0)
        {
            capacity = 100;
            arr = new Object[capacity];
        }
        else if(_size >= capacity)
        {
            int new_capacity = capacity*2;
            Object[] temp_arr = new Object[new_capacity];
            for(int i=0;i<capacity;i++)
            {
                temp_arr[i] = arr[i];
            }
            capacity = new_capacity;
            arr = temp_arr;
        }

        arr[_size] = t;
        ++_size;

        return true;
    }

    //gets elements indicated by the given index,throws exception if out of range
    public T get(int index)throws Exception
    {
        if(index < 0 || index >= _size)
        {
            throw new Exception("Vector index out of range!");
        }

        return ((T)arr[index]);
    }

    public int size()
    {
        return _size;
    }


}
