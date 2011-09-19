CXX = g++
CPPFLAGS = -Wall -pedantic-errors -ggdb -pg
#LIBRARIES_grapher = $(addprefix -l,GL GLU glut)
LIBRARIES_rbf = 
objdir = obj
headerdir = header
bindir = bin
bin = $(addprefix $(bindir)/,rbf)

object_perceptron = $(addprefix $(objdir)/, main.o neurona.o neurona_rbf.o rbf.o util.o)
#object_grapher = $(addprefix $(objdir)/, grapher.o)

objects = $(object_perceptron)#$(object_grapher) $(object_input)

project: $(bin)

all: $(objects)

bin/rbf: $(object_perceptron)
	$(CXX) $(LIBRARIES_perceptron) $(object_perceptron) -o $@

#bin/grapher: $(object_grapher)
#	$(CXX) $(LIBRARIES_grapher) $(object_grapher) -o $@

$(objdir)/%.o : src/%.cpp
	$(CXX) $< -c $(CPPFLAGS) -I$(headerdir) -o $@

$(objects): | $(objdir)

$(bin): | $(bindir)

$(objdir):
	mkdir $@

$(bindir):
	mkdir $@

$(objdir)/main.o: $(addprefix $(headerdir)/, rbf.h neurona.h neurona_rbf.h)
$(objdir)/neurona.o: $(addprefix $(headerdir)/, util.h neurona.h)
$(objdir)/neurona_rbf.o: $(addprefix $(headerdir)/, util.h neurona_rbf.h)
$(objdir)/rbf.o: $(addprefix $(headerdir)/, rbf.h neurona.h neurona_rbf.h util.h)
$(objdir)/util.o: $(addprefix $(headerdir)/, util.h)

.PHONY: clean test

clean:
	-rm $(objects) $(bin)
