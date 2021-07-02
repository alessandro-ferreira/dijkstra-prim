
INCDIR = include/
SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

CC = g++

CFLAGS = -std=c++17 -O2 -W -Wall -Wno-unused-parameter -Wno-unused-variable
LIBS = 
INCS = -I$(INCDIR)

OBJS = $(addprefix $(OBJDIR), main.o graph.o min_heap.o unordered_array.o)

EXEC = $(BINDIR)main

RM = rm -fv

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIBS)
	
rebuild:
	make clean
	make

$(OBJDIR)main.o: $(SRCDIR)main.cc
	$(CC) -c $(SRCDIR)main.cc -o $(OBJDIR)main.o $(INCS) $(CFLAGS)
	
$(OBJDIR)graph.o: $(SRCDIR)graph.cc
	$(CC) -c $(SRCDIR)graph.cc -o $(OBJDIR)graph.o $(INCS) $(CFLAGS)
	
$(OBJDIR)min_heap.o: $(SRCDIR)min_heap.cc
	$(CC) -c $(SRCDIR)min_heap.cc -o $(OBJDIR)min_heap.o $(INCS) $(CFLAGS) 
	
$(OBJDIR)unordered_array.o: $(SRCDIR)unordered_array.cc
	$(CC) -c $(SRCDIR)unordered_array.cc -o $(OBJDIR)unordered_array.o $(INCS) $(CFLAGS) 

clean:
	$(RM) $(OBJS) $(EXEC)
