CXX = g++
CPPFLAGS = -Wall -pedantic-errors -O2 #-ggdb 
LIBRARIES_grapher = $(addprefix -l,GL GLU glut)
LIBRARIES_rbf = 

object_rbf = $(addprefix obj/,main.o neurona.o neurona_rbf.o rbf.o util.o)
object_input = $(addprefix obj/,input.o util.o)
object_grapher = $(addprefix obj/,grapher.o)

objects = $(object_rbf) $(object_input) $(object_grapher)

binaries = $(addprefix bin/,rbf input grapher) 

project: $(binaries)

all: $(objects)

bin/rbf: $(object_rbf)
	$(CXX) $(LIBRARIES_rbf) $(object_rbf) -o $@

bin/input: $(object_input)
	$(CXX) $(object_input) -o $@

bin/grapher: $(object_grapher)
	$(CXX) $(LIBRARIES_grapher) $(object_grapher) -o $@

obj/main.o: $(addprefix header/,rbf.h neurona.h neurona_rbf.h)
obj/neurona.o: $(addprefix header/,util.h neurona.h)
obj/neurona_rbf.o: $(addprefix header/,util.h neurona_rbf.h)
obj/rbf.o: $(addprefix header/,rbf.h neurona.h neurona_rbf.h util.h)
obj/util.o: $(addprefix header/,util.h)
obj/input.o: $(addprefix header/,util.h)

obj/%.o : src/%.cpp
	$(CXX) $< -c $(CPPFLAGS) -Iheader -o $@

obj/main.o: src/main.cpp
	$(CXX) $< -c $(CPPFLAGS) -Iheader -o $@

$(objects): | obj

$(binaries): | bin

obj:
	mkdir $@

bin:
	mkdir $@


.PHONY: clean test

clean:
	-rm $(objects) $(binaries)
	-rmdir bin obj
