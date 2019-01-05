#include "Vigener.h"

Vigener::Vigener()
{
}

Vigener::~Vigener()
{
}

void Vigener::readFromFile(const char* filename, std::vector<unsigned char>& text)
{
	std::string line;
	std::ifstream file(filename);
	if (file.is_open()) 
	{
		while (std::getline(file, line)) 
		{
			size_t i = 0;
			while (i < line.length())
			{
				text.push_back(line[i]);
				i++;
			}
		}
	}
	else
	{
		std::cout << "Unable to open file.";
	}
	file.close();
}

void Vigener::writeToFile(const char* filename, std::vector<unsigned char>& v) 
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		for (size_t i = 0; i < v.size(); i++)
		{
			file << v[i];
		}
	}
	else
	{
		std::cout << "Unable to open file";
	}
	file.close();
}

unsigned char Vigener::shiftForward(unsigned char letter, unsigned char shift)
{
	//	c[i] = m[i] + k[i] mod(N)
	int shifting = statistics.getLetterNumber(shift);
	unsigned char result = statistics.getLetter(getModulus((statistics.getLetterNumber(letter) + shifting), statistics.alpha.size()));
	return result;
}

unsigned char Vigener::shiftBack(unsigned char letter, unsigned char shift)
{
	//	m[i] = c[i] - k[i] mod(N)
	int shifting =  statistics.getLetterNumber(shift);
	unsigned char result = statistics.getLetter(getModulus((statistics.getLetterNumber(letter) - shifting), statistics.alpha.size()));
	return result ;
}

void Vigener::encrypt(std::vector<unsigned char>& text, std::vector<unsigned char>& key, std::vector<unsigned char>& entext)
{
	int text_length = text.size();
	int key_length = key.size();
	for (int i = 0; i < text_length; i++)
	{
		entext.push_back(shiftForward(text[i], key[i % key_length]));
	}
}

void Vigener::decrypt(std::vector<unsigned char>& entext, std::vector<unsigned char>& key, std::vector<unsigned char>& detext)
{
	int text_length = entext.size();
	int key_length = key.size();
	for (int i = 0; i < text_length; i++)
	{
		detext.push_back(shiftBack(entext[i], key[i % key_length]));
	}
}

void Vigener::selectText(std::vector<unsigned char>& text, std::vector<unsigned char>& selected_text, int step, int start)
{
	for (size_t i = start; i < text.size(); i += step)
	{
		selected_text.push_back(text[i]);
	}
}

unsigned char Vigener::getModulus(unsigned char a, int modulus) 
{
	if (modulus == 0)
	{
		return a;
	}
	if (a >= 0)
	{
		a = a % modulus;
	}
	if(a < 0)
	{
		while (a < 0)
		{
			a = a + modulus;
		}
	}
	return a;
}

int Vigener::findKeyLength(std::vector<unsigned char>& entext)
{
	for (size_t i = 0; i < entext.size(); i++)
	{
		std::vector<unsigned char> current_selected_text;
		selectText(entext, current_selected_text, i + 1, 0);
		double index = statistics.calculateIndexOfCoincidence(current_selected_text);
		//std::cout << index << std::endl;
		if (index > 0.06)	//en - 0.06 //ru - 0.05
		{
			return i + 1;
		}
	}
	return 0;
}

void Vigener::getKey(const char* filestat, std::vector<unsigned char>& entext, int keysize, std::vector<unsigned char>& founded_key)
{
	unsigned char max = findShiftUsingStatisticsFile(filestat);
	for (int i = 0; i < keysize; ++i)
	{
		std::vector<unsigned char> current_selected_text;
		selectText(entext, current_selected_text, keysize, i);
		std::map<unsigned char, int> stat;
		statistics.calculateStatistics(current_selected_text, stat);
		//find maximum frequency in encrypted-selected text
		auto tmp = stat.begin();
		for (auto it = stat.begin(); it != stat.end(); ++it)
		{
			if (it->second > tmp->second)
			{
				tmp = it;
			}
		}
		int shift = (getModulus(statistics.getLetterNumber(tmp->first) - statistics.getLetterNumber(max), 256));
		founded_key.push_back(statistics.getLetter(shift));
	}
}

char Vigener::findShiftUsingStatisticsFile(const char* filename)
{
	std::vector<unsigned char> statistic_text;
	readFromFile(filename, statistic_text);
	std::map<unsigned char, int> stat;
	statistics.calculateStatistics(statistic_text, stat);
	auto max = stat.begin();
	for (auto it = stat.begin(); it != stat.end(); ++it)
	{
		if (it->second >= max->second)
		{
			max = it;
		}
	}
	return max->first;
}

void showVector(std::vector<unsigned char>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i];
	}
	std::cout << std::endl;
}

void showDifferences(std::vector<unsigned char>& original, std::vector<unsigned char>& restored)
{
	if (original.size() != restored.size())
	{
		return;
	}
	for (size_t i = 0; i < original.size(); i++)
	{
		if (original[i] == restored[i])
		{
			std::cout << original[i];
		}
		else
		{
			std::cout << ".";
		}
	}
}

