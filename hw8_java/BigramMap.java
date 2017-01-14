/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* BigramMap.java                                                           */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
import java.io.*;
import java.util.*;

public class BigramMap<T> implements Bigram<T>{

    private HashMap<MyPair<T,T>,Integer> my_map;
    final int type;


    public BigramMap(int _type)throws Exception
    {
        type = _type;
        my_map = new HashMap<>(100);

        if(type < 1 || type >3)
            throw new Exception("Invalid type id !");
    }

     //reads file into a map,HashMap or MyMap throws an Exception on fileread error
    public void readFile(String filename)throws Exception
    {
        FileInputStream fin = new FileInputStream(filename);
        Scanner scaner = new Scanner(fin);
        Vector<T> vector = new Vector<>(100);

        while(scaner.hasNext())
        {
            if(type == 1)
            {
                vector.add((T)(Integer)(scaner.nextInt()));
            }
            else if(type == 2)
            {
                vector.add((T)(scaner.next()));
            }
            else
            {
                vector.add((T)(Double)(scaner.nextDouble()));
            }
        }

        fillMap(vector);
    }

    // returns number of Bigrams read so far
    public int numGrams()
    {
        int count = 0;

        Iterator it = my_map.entrySet().iterator();

        while (it.hasNext())
        {
            Map.Entry entry = (Map.Entry) it.next();
            count+=(Integer)entry.getValue();
        }

        return count;
    }

    //returns number of occurences of the given bigram
    public int numOfGrams(T first,T second)
    {
        if(my_map.containsKey(new MyPair<T, T>(first,second)))
        {
            return my_map.get(new MyPair<T, T>(first,second));
        }
		else
        {
            return 0;
        }
    }

    //standard
    public String toString()
    {
        String to_return = "";
        Set set = my_map.entrySet();
        while(set.size()>0)
        {
            Map.Entry<MyPair<T,T>,Integer> entry = getMaxAndDiscard(set);
            to_return=to_return +"{"+ entry.getKey().getFirst() + ","
                    + entry.getKey().getSecond()+"} ";
        }

        return to_return;
    }

     //removes the max entry faund in the map and returns removed value
    private Map.Entry<MyPair<T,T>,Integer> getMaxAndDiscard (Set<Map.Entry<MyPair<T,T>,Integer>> set)
    {
        Iterator it = set.iterator();
        Map.Entry<MyPair<T,T>,Integer> maxEntry = (Map.Entry<MyPair<T,T>,Integer> ) it.next();

        while (it.hasNext()) {
            Map.Entry<MyPair<T,T>,Integer> curEntry = (Map.Entry<MyPair<T,T>,Integer> ) it.next();
            if(curEntry.getValue() > maxEntry.getValue()) {
                maxEntry = curEntry;
            }
        }

        it = set.iterator();
        while(it.hasNext()){
            if (it.next().equals(maxEntry)) {
                it.remove();
            }
        }

        return maxEntry;
    }

    //helper function to fill up the map 
    private void fillMap(Vector<T> vector)
    {
        if(my_map.size() >0)
        {
            my_map.clear();
        }

        for (int i =0;i<vector.size()-1;++i)
        {
            MyPair<T,T> temp_pair = new MyPair<T, T>(vector.get(i),vector.get(i+1));
            if(!my_map.containsKey(temp_pair))
            {
                for(int j = i;j < vector.size()-1;++j)
                {
                    if(temp_pair.equals(new MyPair<T, T>(vector.get(j),vector.get(j+1))))
                    {
                        if(!my_map.containsKey(temp_pair))
                        {
                            my_map.put(temp_pair,1);
                        }
                        else
                        {
                            my_map.put(temp_pair,my_map.get(temp_pair)+1);
                        }
                    }
                }
            }
        }
    }
}
