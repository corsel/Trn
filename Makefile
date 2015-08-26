.DEFAULT=build

INCLUDE=-I include
SOURCE=src/*
LIB=-l glut -l GL -l pthread
OUT=-o bin/trn
DEBUGOUT=bin/trnd


build: 
	g++ $(INCLUDE) $(OUT) $(SOURCE) $(LIB)

build-debug:
	g++ -g $(INCLUDE) $(OUT) $(SOURCE) $(LIB)
