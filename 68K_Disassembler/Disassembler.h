#pragma once
#include <string>

class Disassembler
{
public:
	
	static char hexArray[];
	static std::string condArray[];

	static std::string parseInstruction(char* code, int& offset);
	static int parseSize(char* code, int& offset, int opcode, std::string& line);
	static int parseSourceOperand(char* code, int& offset, int opcode, int size, std::string& line);
	static int parseDestOperand(char* code, int& offset, int opcode, int size, std::string& line);

	static std::string parseByte(char byte);
};

