CXX= g++
CPPFLAGS= -Wall -std=c++11 -O0 -g -c -o
INCPATH = `pkg-config --cflags QtGui`
LIBS= -lboost_regex -lQtGui -lQtCore 
OBJECTS= main.o \
		 action.o commit.o worktimehandler.o user.o log.o logfilehandler.o \
		 mainwindow.o filedialog.o textview.o listview.o

MOCS= mainwindow.moc.cpp filedialog.moc.cpp textview.moc.cpp listview.moc.cpp

#Vpath defining foldes with source files
VPATH+= src

#Main build rule
all: vcls

vcls: $(OBJECTS) $(MOCS)
	$(CXX) $(OBJECTS) $(MOCS) $(INCPATH) $(LIBS) -std=c++11 -Wall -o $@

#Rules for individual parts of the program
%.o: logdata/%.cpp logdata/%.hpp
	$(CXX) $< $(CPPFLAGS) $@

%.o: qtgui/%.cpp qtgui/%.hpp
	$(CXX) $< $(INCPATH) $(CPPFLAGS) $@

%.o: %.cpp %.hpp
	$(CXX) $< $(CPPFLAGS) $@

#Rule to handle the files that does not have a header
%.o: %.cpp
	$(CXX) $? $(INCPATH) $(CPPFLAGS) $@

#Rule for Qt's preprosser, which must run on QTOBJECT derived files
%.moc.cpp: qtgui/%.hpp
	moc $< -o $@

#Rules for cleaning
make clean:
	rm *.o
	rm *.moc.cpp
	rm vcls 
