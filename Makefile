CFLAGS  = -Wall 

#------------------------------------------------------------------------------
all : escalona 
	$(RM) *.o

escalona : escalona.o grafo.o operacao.o 

#------------------------------------------------------------------------------

clean :
	$(RM) escalona *.o