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

// This is a simple program to decode a text file with 0 (zeros) and 1 (ones),
// in which every 8 bits (a group of 8 zeros / ones) should represent 1 ASCII
// char. The program reads the file, removes any white spaces, and either
// stores the decoded ASCII string on a file on disk, or simply prints it to
// STDOUT. You need to pass the file name as a command line argument when
// calling this program. Example: ./binary-to-ascii file-to-decode.txt


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <bitset>

void printOrWriteToDisk(const std::string& asciiString)
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
			outputFile << asciiString;
			outputFile.close();
			std::cout << "Done!" << std::endl;
		}
		else if(userInput == '2')
			std::cout << asciiString;
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
	std::ifstream binFile(argv[1]);
	if(!binFile)
	{
		std::cout << "Error trying to open file!\n";
		return 1;
	}

	std::string asciiStr;
	std::ostringstream oss;
	oss << binFile.rdbuf();
	std::string binStr = oss.str();

	// remove white spaces
	binStr.erase(std::remove(binStr.begin(), binStr.end(), ' '),
			binStr.end());

	// remove new lines
	binStr.erase(std::remove(binStr.begin(), binStr.end(), '\n'),
			binStr.end());

	// loop at every 8 bits (1 byte) and convert it to 1 ascii char
	for(auto itr = binStr.begin(); itr != binStr.end(); itr += 8)
	{
		char binSymbol[9];
		for(short i = 0; i < 8; i++)
			binSymbol[i] = itr[i];
		binSymbol[8] = '\0';

		auto numSymbol = std::bitset<8>(binSymbol).to_ulong();
		char asciiSymbol = numSymbol;
		asciiStr += asciiSymbol; // append char to string
	}

	binFile.close();
	printOrWriteToDisk(asciiStr);
	return 0;
}
