/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyLLNode.java                                                            */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
public class MyLLNode<T> {

    private T data;
    private MyLLNode<T> node;
    private MyLLNode<T> previous;


    public MyLLNode()
    {
        data = null;
        node = null;
        previous =null;
    }

    public MyLLNode(T _data, MyLLNode<T> _node, MyLLNode<T> _previous)
    {
        data = _data;
        node = _node;
        previous = _previous;
    }

    //setters,getters
    public T getData()
    {
        return data;
    }

    public void setData(T _data)
    {
        data= _data;
    }

    public MyLLNode<T> getNode()
    {
        return node;
    }

    public void setNode(MyLLNode<T> _node)
    {
        node = _node;
    }

    public MyLLNode<T> getPrevious()
    {
        return previous;
    }

    public void setPrevious(MyLLNode<T> _previous)
    {
        previous = _previous;
    }
}
