#include "Statistics.h"

Statistics::Statistics()
{
	unsigned char symbol = 0;
	for (int i = 0; i < 256; i++)
	{
		alphabet[i] = unsigned char(symbol);
		alpha.insert(std::make_pair(unsigned char(symbol), i));
		symbol++;
	}
}

Statistics::~Statistics()
{
}

void Statistics::calculateStatistics(const std::vector<unsigned char>& text, std::map<unsigned char, int>& statistics)
{
	int size = text.size();
	
	for (int i = 0; i < 256; i++)
	{
		statistics.insert(std::pair<unsigned char, int>(alphabet[i], 0));
	}
	for (size_t i = 0; i < text.size(); i++)
	{
		int tmp = statistics[text[i]];
		tmp++;
		statistics.insert_or_assign(text[i], tmp);
	}
}

double Statistics::calculateIndexOfCoincidence(const std::vector<unsigned char>& text)
{
	std::map<unsigned char, int> statistic;
	calculateStatistics(text, statistic);
	double index = 0;
	for (auto it = statistic.begin(); it != statistic.end(); ++it)
	{
		double p = (double)it->second / text.size();
		index += p * p;
	}
	return index;
}

unsigned char Statistics::getLetter(int number)
{
	return alphabet[number];
}

int Statistics::getLetterNumber(unsigned char letter)
{
	return alpha.find(letter)->second;
}

void Statistics::ShowStatistics(const std::map<unsigned char, int>& map)
{
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << " = " << it->second << std::endl;
	}
}
