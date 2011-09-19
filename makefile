CXX = g++
CPPFLAGS = -Wall -pedantic-errors -ggdb -pg
LIBRARIES_grapher = $(addprefix -l,GL GLU glut)
LIBRARIES_rbf = 

object_rbf = $(addprefix obj/, main.o neurona.o neurona_rbf.o rbf.o util.o)
object_input = $(addprefix obj/, input.o util.o)
object_grapher = $(addprefix obj/, grapher.o)

objects = $(object_perceptron) $(object_grapher) $(object_input)

project: $(addprefix bin/,rbf input grapher)

all: $(objects)

bin/rbf: $(object_rbj)
	$(CXX) $(LIBRARIES_rbf) $(object_rbf) -o $@

bin/input: $(object_input)
	$(CXX) $(object_input) -o $@

bin/grapher: $(object_grapher)
	$(CXX) $(LIBRARIES_grapher) $(object_grapher) -o $@

obj/%.o : src/%.cpp
	$(CXX) $< -c $(CPPFLAGS) -Iheader -o $@

$(objects): | obj

$(bin): | bin

obj:
	mkdir $@

bin:
	mkdir $@

obj/main.o: $(addprefix header/, rbf.h neurona.h neurona_rbf.h)
obj/neurona.o: $(addprefix header/, util.h neurona.h)
obj/neurona_rbf.o: $(addprefix header/, util.h neurona_rbf.h)
obj/rbf.o: $(addprefix header/, rbf.h neurona.h neurona_rbf.h util.h)
obj/util.o: $(addprefix header/, util.h)
obj/input.o: $(addprefix header/, util.h)

.PHONY: clean test

clean:
	-rm $(objects) $(bin)
