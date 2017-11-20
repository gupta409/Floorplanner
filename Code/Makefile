#compiler to use
CC= g++
#comiler flags
CFLAGS = -c -std=c++11
#make file commands
all: ioutilites node size polishutilites randomutilites floorplanner main
	$(CC) FloorplannerConstants.o Floorplanner.o PolishUtilities.o RandomizeUtilites.o IOUtilites.o Node.o Size.o main.o -o parser
main: main.cpp
	$(CC) $(CFLAGS) main.cpp
floorplanner: node floorplanner_constants Floorplanner.cpp Floorplanner_test.cpp ioutilites
	$(CC) $(CFLAGS) Floorplanner.cpp
	$(CC) $(CFLAGS) Floorplanner_test.cpp
floorplanner_constants: ioutilites FloorplannerConstants.cpp
	$(CC) $(CFLAGS) FloorplannerConstants.cpp
	$(CC) $(CFLAGS) FloorplannerConstants_test.cpp
polishutilites: PolishUtilities.cpp PolishUtilites_test.cpp
	$(CC) $(CFLAGS) PolishUtilities.cpp
	$(CC) $(CFLAGS) PolishUtilites_test.cpp
randomutilites: RandomizeUtilites.cpp RandomizeUtilites_test.cpp
	$(CC) $(CFLAGS) RandomizeUtilites.cpp
	$(CC) $(CFLAGS) RandomizeUtilites_test.cpp
ioutilites: node IOUtilites.cpp
	$(CC) $(CFLAGS) IOUtilites.cpp
	$(CC) $(CFLAGS) IOUtilites_test.cpp
node: Node.cpp size Node_test.cpp
	$(CC) $(CFLAGS) Node.cpp
	$(CC) $(CFLAGS) Node_test.cpp
size: Size.cpp
	$(CC) $(CFLAGS) Size.cpp

clean:
	rm -rf *o parser
	rm -rf *gch
