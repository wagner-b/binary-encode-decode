CC = gcc
CXX = g++
RM = rm -f

all: ascii-to-binary binary-to-ascii

ascii-to-binary:
	$(CXX) ascii-to-binary.cpp -o ascii-to-binary

binary-to-ascii:
	$(CXX) binary-to-ascii.cpp -o binary-to-ascii


clean:
	$(RM) ascii-to-binary binary-to-ascii
