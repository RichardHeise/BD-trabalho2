# @file  Makefile
# @brief Arquivo Make
# @date 27/02/2021
# @author Richard Fernando Heise Ferreira (GRR20191053)
# @author Monica Ludmila Hintz de Oliveira (GRR20159417)


CFLAGS  = -Wall 
CC = g++

#------------------------------------------------------------------------------
all : escalona 

escalona : escalona.o grafo.o operacao.o main.o

#------------------------------------------------------------------------------

clean :
	$(RM) *.o

#------------------------------------------------------------------------------

purge:
	$(RM) escalona *.o
