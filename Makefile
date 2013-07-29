CXX= g++
CPPFLAGS= -Wall -fPIE -std=c++11 -O2 -c -o 
INCPATH = `pkg-config --cflags Qt5Widgets`
LIBS= -lboost_regex -lQt5Core -lQt5Widgets
OBJECTS= action.o commit.o worktimehandler.o commitedfileshandler.o user.o log.o logfilehandler.o
GUIOBJECTS= mainwindow.o textview.o listview.o errorpopup.o
CLIOBJECTS= maininterface.o

MOCS= mainwindow.moc.cpp textview.moc.cpp listview.moc.cpp errorpopup.moc.cpp

#Vpath defining foldes with source files
VPATH+= src

#Main build rule
all: gui 

#Rules for gui and cli	
gui: $(OBJECTS) $(GUIOBJECTS) $(MOCS)
	$(CXX) $(INCPATH) $(OBJECTS) $(GUIOBJECTS) $(MOCS) $(LIBS) src/main.cpp -DGUI -fPIE -std=c++11 -Wall -o vcls

cli: $(CLIOBJECTS) $(OBJECTS)
	$(CXX) $(OBJECTS) $(CLIOBJECTS) src/main.cpp -std=c++11 -lboost_regex -Wall -o vcls

#Rules for individual parts of the program
%.o: logdata/%.cpp logdata/%.hpp
	$(CXX) $< $(CPPFLAGS) $@

%.o: gui/%.cpp gui/%.hpp
	$(CXX) $< $(INCPATH) $(CPPFLAGS) $@

%.o: cli/%.cpp cli/%.hpp
	$(CXX) $< $(CPPFLAGS) $@

%.o: %.cpp %.hpp
	$(CXX) $< $(CPPFLAGS) $@

#Rule for Qt's preprosser, which must run on QTOBJECT derived files
%.moc.cpp: gui/%.hpp
	moc-qt5 $< -o $@

#Rules for cleaning
make clean:
	rm -rf *.o
	rm -rf *.moc.cpp
	rm -rf vcls 
