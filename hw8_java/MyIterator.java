/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW08_141044086_Vakhid_Betrakhmadov                                       */
/*                                                                          */
/* MyIterator.java                                                          */
/* ---------                                                                */
/* Created on 26/12/2016 by Vakhid_Betrakhmadov                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

public interface MyIterator<T> {
    boolean hasNext();
    boolean hasPrevious();
    int nextIndex();
    int previousIndex();
    T next();
    T previous();
    T peek();
    void set(T t);
    void add(T t);
    boolean equals(Object o);
}
