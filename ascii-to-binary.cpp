/*
BSD 3-Clause License

Copyright (c) 2023, Wagner Bertholdo Burghausen

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// This is a simple program to encode a text file containing ASCII chars 
// into the binary representation of each char as a group of 8 zeros / ones.
// The program reads the file, and either stores the resulting string on 
// a file on disk, or simply prints it to STDOUT. You need to pass the file 
// name as a command line argument when calling this program.
// Example: ./ascii-to-binary file-to-encode.txt


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void printOrWriteToDisk(const std::string& binString)
{
	char userInput;
	do
	{
		std::cout << "\nOptions:\n1 - Write output to a file\n";
		std::cout << "2 - Simply print output to STDOUT\n";
		std::cout << "Choose an option [1 or 2]: ";
		std::cin >> userInput;
		std::cin.ignore(); // clear '\n' in buffer

		if(userInput == '1')
		{
			std::string fileName;
			std::cout << "Type the name for the output file: ";
			std::getline(std::cin, fileName);
			std::ofstream outputFile(fileName);
			if(!outputFile)
			{
				std::cout << "Error trying to open file!\n";
				exit(1);
			}
			outputFile << binString;
			outputFile.close();
			std::cout << "Done!" << std::endl;
		}
		else if(userInput == '2')
			std::cout << binString;
		else
			std::cout << "Error! Please, type only 1 or 2.\n";
	}
	while(userInput != '1' && userInput != '2');
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Error! Usage: <file_name>\n";
		return 1;
	}
	std::ifstream asciiFile(argv[1]);
	if(!asciiFile)
	{
		std::cout << "Error trying to open file!\n";
		return 1;
	}

	std::string binStr;
	std::ostringstream oss;
	oss << asciiFile.rdbuf();
	std::string asciiStr= oss.str();

	// Find the 8 bit repr. of each char and append it to binStr
	for(auto itr = asciiStr.begin(); itr != asciiStr.end(); itr++)
	{
		char binSymbol[9];
		for(short i = 7, j = 0; i >= 0; i--, j++)
		{
			if((*itr >> i) & 1) binSymbol[j] = '1';
			else binSymbol[j] = '0';
		}
		binSymbol[8] = '\0';

		binStr += binSymbol; 
		binStr += ' ';
	}

	asciiFile.close();
	printOrWriteToDisk(binStr);
	return 0;
}
