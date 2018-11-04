CPP = g++

LINK = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d

ARGS = -Wall -std=c++11

OUT_FILE = shapeFinder


all: main.o helperFunctions.o
	$(CPP) $(ARGS) main.o helperFunctions.o $(LINK) -o$(OUT_FILE)
	
main.o: main.cpp
	$(CPP) -c main.cpp $(ARGS)
	
helperFunctions.o: helperFunctions.cpp
	$(CPP) -c helperFunctions.cpp $(ARGS)