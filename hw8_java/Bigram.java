/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* Bigram.java                                                              */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

public interface Bigram<T> {
    void readFile(String filename)throws Exception; //reads file into a map,HashMap or MyMap throws an Exception on fileread error
    int numGrams(); // returns number of Bigrams read so far
    int numOfGrams(T first,T second); //returns number of occurences of the given bigram
    String toString(); // standard
}
