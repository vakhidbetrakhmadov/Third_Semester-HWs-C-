JFLAGS = -g

JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	_mainTester.java \
	Bigram.java \
	BigramDyn.java \
	BigramMap.java \
	makefile \
	MyIterator.java \
	MyLinkedList.java \
	MyLLNode.java \
	MyMap.java \
	MyPair.java \
	MyVector.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class

