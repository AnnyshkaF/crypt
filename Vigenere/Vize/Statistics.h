#pragma once
#include <map>
#include <vector>
#include <iostream>

class Statistics
{
public:
	std::map<unsigned char, int> alpha;
	unsigned char alphabet[256];

									Statistics();
									~Statistics();
	void							calculateStatistics(const std::vector<unsigned char>& text, std::map<unsigned char, int>& statistics);
	double							calculateIndexOfCoincidence(const std::vector<unsigned char>& text);
	unsigned char					getLetter(int number);
	int								getLetterNumber(unsigned char letter);
	void							ShowStatistics(const std::map<unsigned char, int>& map);
};

