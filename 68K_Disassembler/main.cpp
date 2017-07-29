#include <iostream>
#include <fstream>

#include "Disassembler.h"

int main(int argc, char* argv[])
{
	std::cout << "\tEdward Opich's 68K Disassembler\n\n" << std::endl;

	if (argc == 1)
	{
		std::cout << "Standard Format: 68K_Disassembler.exe [Flags] \"S.bin\" \"D.asm\" [Start] [End]\n\n";

		std::cout << "\"S.bin\" is the binary program you are disassembling.\n";
		std::cout << "\"D.asm\" is the file you would like the disassembly saved to.\n";
		std::cout << "[Start] and [End] are decimal numbers for where to start and stop parsing.\n\n";

		std::cout << "Do not include any brackets or quotes for the files or offsets.\n";
		std::cout << "No flags are currently available, but will be in a future build!\n\n";						// Remove this line for personal version

		/*std::cin.get();

		std::cout << "Enhanced Disassembly: 68K_Disassembler.exe -E [Flags] \"S.bin\" \"D.asm\" \"P.edf\"\n\n";
		std::cout << "\"P.edf\" is an Enhanced Disassembly File to make the disassembly cleaner.\n";
		std::cout << "It allows for parsing code from data, spacing, comments, and more.\n\n";

		std::cin.get();

		std::cout << "Flags:\n";
		std::cout << "\t-E | Enhanced Disassembly mode. The program will expect an .edf file.\n";
		std::cout << "\t-O | The program will not print offsets as comments.\n\n";*/
		
		std::cout << "Press Enter to exit. ";
		std::cin.get();

		return 0;
	}

	else
	{
		std::ifstream binaryFile = std::ifstream(argv[1], std::ifstream::binary);

		if (!binaryFile.is_open())
		{
			std::cout << "Input file failed to open! Press Enter to exit. ";
			std::cin.get();
			return 1;
		}

		std::ofstream outputFile = std::ofstream(argv[2]);

		if (!outputFile.is_open())
		{
			std::cout << "Failed to open output file! Press Enter to exit. ";
			std::cin.get();
			return 1;
		}

		binaryFile.seekg(0, binaryFile.end);
		int length = binaryFile.tellg();
		binaryFile.seekg(0, binaryFile.beg);

		char* file = new char[length + 1];

		binaryFile.read(file, length);
		file[length] = 0;

		binaryFile.close();

		// Time to get parsing instructions!
		int offset = 0;
		int end = -1;

		if (argc >= 4)
		{
			offset = atoi(argv[3]);
			std::cout << "Starting at offset ";
			std::cout << offset;
			std::cout << "\n";

			if (argc >= 5)
			{
				end = atoi(argv[4]);
				std::cout << "Ending at offset ";
				std::cout << end;
				std::cout << "\n";
			}
		}

		while (offset < length)
		{
			std::string instruction = Disassembler::parseInstruction(file, offset);
			std::string finalInstruction = "\t";
			finalInstruction += instruction;
			outputFile.write(finalInstruction.c_str(), finalInstruction.length());
			if (offset >= end && end > 0)
			{
				break;
			}
		}

		delete[] file;

		outputFile.close();
	}

	std::cout << "The file has been parsed. Press Enter to exit. ";
	std::cin.get();
	return 0;
}