CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++11 -g
INCLUDES = -Iinc
LFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR := src
OBJDIR := obj
INCDIR := inc
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OBJDIR)/,$(SRC:$(SRCDIR)/%.cpp=%.o))  #Place objects
LIBS =  -lsfml-graphics -lsfml-window -lsfml-system
NAME = engine


all:
	$(MAKE) --no-print-directory clean
	$(MAKE) --no-print-directory -j build
	$(MAKE) --no-print-directory run

.PHONY : clean
clean:
	rm -f $(OBJDIR)/*.o *~ $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

build: $(OBJS)
	$(CXX) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBS)

run:
	./$(NAME)
