CXX= g++
CPPFLAGS= -g -Wall -std=c++11 -O0 -g -c -o
LDFLAGS= -lboost_regex `pkg-config --libs --cflags QtGui`
OBJECTS= main.o \
		 action.o commit.o user.o log.o logfilehandler.o \
		 mainwindow.o

MOCS= mainwindow.moc.cpp

#Vpath defining foldes with source files
VPATH+= src

#Main build rule
all: vcls

vcls: $(OBJECTS) $(MOCS)
	$(CXX) $(OBJECTS) $(MOCS) $(LDFLAGS) -g -Wall -o $@

#Rules for individual parts of the program
%.o: logdata/%.cpp logdata/%.hpp
	$(CXX) $< $(LDFLAGS) $(CPPFLAGS) $@

%.o: qtgui/%.cpp qtgui/%.hpp
	$(CXX) $< $(LDFLAGS) $(CPPFLAGS) $@

%.o: %.cpp %.hpp
	$(CXX) $< $(CPPFLAGS) $@

#Rule to handle the files that does not have a header
%.o: %.cpp
	$(CXX) $? $(LDFLAGS) $(CPPFLAGS) $@

#Rule for Qt's preprosser, which must run on QTOBJECT derived files
%.moc.cpp: qtgui/%.hpp
	moc $< -o $@

#Rules for cleaning
make clean:
	rm *.o
	rm *.moc.cpp
	rm vcls 
