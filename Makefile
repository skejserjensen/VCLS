CXX= g++
# Local typedef warnings are disabled as warning from included Qt4 headers clutters the output, and VCLS does not contain any typedefs
CPPFLAGS= -Wall -Wno-unused-local-typedefs -std=c++11 -O0 -g -c -o 
INCPATH = `pkg-config --cflags QtGui`
LIBS= -lboost_regex -lQtGui -lQtCore 
OBJECTS= main.o \
		 action.o commit.o worktimehandler.o commitedfileshandler.o user.o log.o logfilehandler.o \
		 mainwindow.o textview.o listview.o errorpopup.o

MOCS= mainwindow.moc.cpp textview.moc.cpp listview.moc.cpp errorpopup.moc.cpp

#Vpath defining foldes with source files
VPATH+= src

#Main build rule
all: vcls

vcls: $(OBJECTS) $(MOCS)
	$(CXX) $(OBJECTS) $(MOCS) $(INCPATH) $(LIBS) -std=c++11 -Wno-unused-local-typedefs -Wall -o $@

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
	moc-qt4 $< -o $@

#Rules for cleaning
make clean:
	rm *.o
	rm *.moc.cpp
	rm vcls 
