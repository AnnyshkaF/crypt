#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include"Statistics.h"

class Vigener
{
private:
	Statistics						statistics;

	void							selectText(std::vector<unsigned char>& text, std::vector<unsigned char>& selected_text, int step, int start);
	unsigned char					shiftForward(unsigned char letter, unsigned char shift);
	unsigned char					shiftBack(unsigned char letter, unsigned char shift);
	unsigned char					getModulus(unsigned char a, int modulus);
	char							findShiftUsingStatisticsFile(const char* filename);

public:	
									Vigener();
									~Vigener();

	void							readFromFile(const char* filename, std::vector<unsigned char>& text);
	void							writeToFile(const char* filename, std::vector<unsigned char>& v);
	void							encrypt(std::vector<unsigned char>& text, std::vector<unsigned char>& key, std::vector<unsigned char>& entext);
	void							decrypt(std::vector<unsigned char>& entext, std::vector<unsigned char>& key, std::vector<unsigned char>& detext);
	
	int								findKeyLength(std::vector<unsigned char>& entext);
	void							getKey(const char* filestat, std::vector<unsigned char>& entext, int keysize, std::vector<unsigned char>& founded_key);
	
	
};

