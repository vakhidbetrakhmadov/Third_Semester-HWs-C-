/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyPair.java                                                              */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
public class MyPair<T,K> implements Comparable<MyPair<T,K>> {

    private T first;
    private K second;


    public MyPair()
    {
        first =null;
        second = null;
    }

    public MyPair(T _first,K _second)
    {
        first = _first;
        second = _second;
    }


    //getters,setters
    public T getFirst()
    {
        return first;
    }

    public K getSecond()
    {
        return second;
    }

    public void setFirst(T _first)
    {
        first = _first;
    }

    public void setSecond(K _second)
    {
        second = _second;
    }

 	//accordig to the standard (-,0,+)
    public int compareTo(MyPair<T,K> other)
    {
        if(this.first == null && this.second == null && other.first==null && other.second == null)
            return 0;

        if(((Comparable) this.first).compareTo((Comparable)other.first) != 0)
        {
            return ((Comparable) this.first).compareTo((Comparable)other.first);
        }

        return ((Comparable) this.second).compareTo((Comparable)other.second);
    }

    public int hashCode() {
        // name's hashCode is multiplied by an arbitrary prime number (13)
        // in order to make sure there is a difference in the hashCode between
        // these two parameters:
        //  name: a  value: aa
        //  name: aa value: a
        return first.hashCode() * 13 + (second == null ? 0 : second.hashCode());
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o instanceof MyPair) {
            MyPair pair = (MyPair) o;
            if (first != null ? !first.equals(pair.first) : pair.first != null) return false;
            if (second != null ? !second.equals(pair.second) : pair.second != null) return false;
            return true;
        }
        return false;
    }
}
