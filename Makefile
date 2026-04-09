SourceFiles = main.cpp
Libs = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c++23
CC = g++
all:
	$(CC) $(SourceFiles) $(Libs) -o sshub
