CC = g++
LD = g++

LDFLAGS = -std=c++14 -Wall -Wextra -Werror -pedantic
CCFLAGS = $(LDFLAGS) -c

SRCDIR = src
OBJDIR = obj

EXE = perceptron


all: $(OBJDIR) $(EXE)


$(EXE):	$(OBJDIR)/Perceptron.o $(OBJDIR)/main.o
	$(LD) $(LDFLAGS) $(OBJDIR)/Perceptron.o $(OBJDIR)/main.o -o $(EXE)


$(OBJDIR)/Perceptron.o:	$(SRCDIR)/Perceptron.hpp $(SRCDIR)/Perceptron.cpp
	$(CC) $(CCFLAGS) $(SRCDIR)/Perceptron.cpp -o $(OBJDIR)/Perceptron.o

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR):
	mkdir $@

clean:
	rm -rf $(OBJDIR)
