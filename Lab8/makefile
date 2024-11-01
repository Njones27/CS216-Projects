HEADERS = imdb.h powerString.h
#(listing all header files here, separated by space)
SOURCES = $(HEADERS:.h=.cpp)
OBJECTS = $(HEADERS:.h=.o)
MAINSOURCE = Lab8.cpp
SUBTEST = testPowerString.cpp
MAINOBJ = $(MAINSOURCE:.cpp=.o)
SUBTESTOBJ = $(SUBTEST:.cpp=.o)
EXEC = Lab8
TESTEXEC = testPowerString
#the first target should be the final executable
#the second target can be the executable to test sub-problem
$(EXEC): $(OBJECTS) $(MAINOBJ)
	g++ $^ -o $@
$(TESTEXEC): $(OBJECTS) $(SUBTESTOBJ)
	g++ $^ -o $@
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm -i *.o
	rm -i `find ./ -type f -executable`