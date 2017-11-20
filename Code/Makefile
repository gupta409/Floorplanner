#compiler to use
CC= g++
#comiler flags
CFLAGS = -c -std=c++11
EXEFLAGS = -DCURL_STATICLIB -static -lstdc++ -lgcc -lpthread -lcurl
#make file commands
all: ioutilites node size polishutilites randomutilites floorplanner main
	$(CC) FloorplannerConstants.o Floorplanner.o PolishUtilities.o RandomizeUtilites.o IOUtilites.o Node.o Size.o main.o -o test
main: main.cpp
	$(CC) $(CFLAGS) main.cpp
floorplanner: node FloorplannerConstants.cpp FloorplannerConstants_test.cpp Floorplanner.cpp Floorplanner_test.cpp
	$(CC) $(CFLAGS) FloorplannerConstants.cpp
	$(CC) $(CFLAGS) FloorplannerConstants_test.cpp
	$(CC) $(CFLAGS) Floorplanner.cpp
	$(CC) $(CFLAGS) Floorplanner_test.cpp
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
	rm -rf *o
	rm -rf *gch
