IDIR=../include
CC=gcc
CFLAGS=-g -I$(IDIR)
FLAGS=-c
ODIR=../obj
LDIR=../lib
LIBS=-lm
EXEC=testa_grafo

_DEPS = graph.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph.o testa_grafo.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -o $@ $< $(CFLAGS)

testa_grafo: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run: testa_grafo
	@./testa_grafo

.PHONY: clear

clear:
	rm -rf $(ODIR)/*.o *~ core $(INCDIR)/*~
