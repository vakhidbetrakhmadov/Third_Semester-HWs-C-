all :exe

exe: _mainTester.o
	g++ -o exe _mainTester.o

_mainTester.o: _mainTester.cpp requiredIncs.h BigramDyn.cpp BigramDyn.h \
	Iterator.cpp Bigram.h  Iterator.h  BigramMap.cpp  LLNode.cpp  MyExeption.h \
	BigramMap.h  LLNode.h  My_map.cpp Const_iterator.cpp My_map.h Const_iterator.h  

	g++ -c _mainTester.cpp 

clean:
	rm exe* *.o


