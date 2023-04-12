# Encode or decode a text file to binary representation
These are simple C++ programs to encode / decode the contents of a text file in binary representation (string of zeros / ones).<br>
Each `.cpp` file in this repository is a separate program.

### ascii-to-binary.cpp
This is a simple program to encode a text file containing ASCII chars 
into the binary representation of each char as a group of 8 zeros / ones.
The program reads the file, and either stores the resulting string on 
a file on disk, or simply prints it to STDOUT. You need to pass the file 
name as a command line argument when calling this program.<br>
Example: `./ascii-to-binary file-to-encode.txt`

### binary-to-ascii.cpp
This is a simple program to decode a text file with 0s (zeros) and 1s (ones),
in which every 8 bits (a group of 8 zeros / ones) should represent 1 ASCII
char. The program reads the file, removes any white spaces, and either
stores the decoded ASCII string on a file on disk, or simply prints it to
STDOUT. You need to pass the file name as a command line argument when
calling this program.<br>
Example: `./binary-to-ascii file-to-decode.txt` 

### Compilation
There is a makefile in this repository, so in case you have `g++` and `make` installed,
you can simply clone this repository, enter it, and type: `make`. Otherwise, compile
each `.cpp` file into a separate program.
