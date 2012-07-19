CXX= clang++
CPPFLAGS= -g -Wall -O0 -g -c -o 
OBJECTS= main.o \
		 action.o

#Vpath defining foldes with source files
VPATH+= src 

#Main build rule
all: vcls

vcls: $(OBJECTS)
	$(CXX) $(OBJECTS) -g -Wall -o $@ 

#Rules for individual parts of the program
%.o: logdata/%.cpp logdata/%.hpp
	$(CXX) $< $(CPPFLAGS) $@

%.o: %.cpp %.hpp
	$(CXX) $< $(CPPFLAGS) $@

#Rule to handle the files that does not have a header
%.o: %.cpp 
	$(CXX) $? $(CPPFLAGS) $@

#Rules for cleaning 
make clean:
	rm *.o
	rm vcls 
