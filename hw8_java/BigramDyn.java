/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* BigramDyn.java                                                           */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
import java.io.FileInputStream;
import java.util.Scanner;

public class BigramDyn<T> implements Bigram<T>{

    private MyMap<MyPair<T,T>,Integer> my_map;
    final int type;

    public BigramDyn(int _type)throws Exception
    {
        my_map = new MyMap<>();
        type = _type;

        if(type<1 || type > 3)
        {
            throw new Exception("Invalid type id !");
        }
    }

    //reads file into a map,HashMap or MyMap throws an Exception on fileread error
    public void readFile(String filename)throws Exception
    {
        FileInputStream fin = new FileInputStream(filename);
        Scanner scaner = new Scanner(fin);
        MyVector<T> vector = new MyVector<T>(100);

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

        MyIterator<MyPair<MyPair<T,T>,Integer>> it = my_map.iterator();

        while (it.hasNext())
        {
            MyPair<MyPair<T,T>,Integer> entry =it.next();
            count+=entry.getSecond();
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
        MyMap clone = my_map.clone();
        while(clone.size()>0)
        {
            MyPair<MyPair<T,T>,Integer> entry = getMaxAndDiscard(clone);
            to_return=to_return +"{"+ entry.getFirst().getFirst() + ","
                    + entry.getFirst().getSecond()+"} ";
        }

        return to_return;
    }

    //removes the max entry faund in the map and returns removed value
    private MyPair<MyPair<T,T>,Integer> getMaxAndDiscard (MyMap<MyPair<T,T>,Integer> map)
    {
        MyIterator<MyPair<MyPair<T,T>,Integer>> it = map.iterator();
        MyPair<MyPair<T,T>,Integer> maxEntry =  it.next();

        while (it.hasNext()) {
            MyPair<MyPair<T,T>,Integer> curEntry = it.next();
            if(curEntry.getSecond() > maxEntry.getSecond()) {
                maxEntry = curEntry;
            }
        }

        map.removeEntry(maxEntry.getFirst(),maxEntry.getSecond());

        return maxEntry;
    }

    //helper function to fill up the map 
    private void fillMap(MyVector<T> vector)throws  Exception
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
