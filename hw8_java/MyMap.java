/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyMap.java                                                          	    */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
public class MyMap<K,V> {

    private MyLinkedList<MyPair<K,V> > list;


    public MyMap()
    {
        list = new MyLinkedList<>();
    }

    public MyMap(K key,V value)
    {
        list = new MyLinkedList<>(new MyPair<>(key,value));
    }

    //retunrns iterator to the map
    public MyIterator<MyPair<K,V>> iterator()
    {
        return list.ListIterator();
    }

    public int size()
    {
        return list.size();
    }

    //works the same as in HashMap
    public V put(K key,V value)
    {
        MyPair<K,V> toInsert = new MyPair<K,V>(key,value);
        if(containsKey(key))
        {
            MyIterator<MyPair<K,V>> it = iterator();
            while(it.hasNext())
            {
                if(it.peek().getFirst().equals(toInsert.getFirst()))
                {
                    it.set(toInsert);
                }
                it.next();
            }
        }
        else
        {
            insertInOrder(toInsert);
        }

        return value;
    }

    //works the same as in HashMap
    public V get(K key)
    {
        if(!containsKey(key))
        {
            return null;
        }

        MyIterator<MyPair<K,V>> it = iterator();
        MyPair<K,V> tempPair = it.next();
        while(it.hasNext() && !tempPair.getFirst().equals(key))
        {
            tempPair = it.next();
        }

        return tempPair.getSecond();
    }

    //removes the given entry from the map
    public void removeEntry(K k,V v)
    {
        try {
            if(list.contains(new MyPair<K, V>(k,v)))
            {
                list.remove(list.indexOf(new MyPair<K, V>(k,v)));
            }
        }
        catch (Exception e)
        {
            System.out.println(e);
        }

    }

    //works the same as in HashMap
    public boolean containsKey(K key)
    {
        boolean found = false;
        MyPair<K,V> myPair;

        MyIterator<MyPair<K,V>> it = iterator();
        while(it.hasNext() && !found)
        {
            myPair = it.next();
            if(myPair.getFirst().equals(key)) {
                found = true;
            }
        }

        return found;
    }


    public MyMap<K,V> clone()
    {
        MyIterator<MyPair<K,V>> it = iterator();

        if(!it.hasNext())
            return new MyMap<>();

        MyPair<K,V>temp=null;
        MyMap<K,V> toReturn = new MyMap<>();
        while(it.hasNext())
        {
            temp = it.next();
            toReturn.put(temp.getFirst(),temp.getSecond());
        }

        return toReturn;
    }

    public void clear()
    {
       list.clear();
    }

    //inserts the given entry in a appropriate place in the map  
    private void insertInOrder(MyPair<K,V> toInsert)
    {
        MyIterator<MyPair<K,V>> it = iterator();
        boolean inserted = false;
        while(it.hasNext() && !inserted)
        {
            if(it.peek().compareTo(toInsert) > 0)
            {
                it.add(toInsert);
                inserted = true;
            }
            it.next();
        }
        if(!inserted)
        {
            list.addLast(toInsert);
        }
    }

}
