#include "Vigener.h"
#include "Statistics.h"
#include <fstream>
#include <string>
#include <algorithm>

void showVector (std::vector<unsigned char>& v);
void showDifferences(std::vector<unsigned char>& original, std::vector<unsigned char>& restored);

int main()
{
	const char* filename = "C:/Users/Anna/Desktop/ciphers/text/text3.txt";
	const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/stat100000_1.txt";
	//const char* filename = "C:/Users/Anna/Desktop/ciphers/text/rutext4.txt";
	//const char* filestat = "C:/Users/Anna/Desktop/ciphers/statistic/rustat100000_1.txt";
	
	setlocale(LC_ALL, "Russian");
	Vigener vigener;
	
	std::string k = "hello world";
	//std::string k = "Проверка";
	std::vector<unsigned char> original_key;
	for (char i : k) 
	{
		original_key.push_back(i);
	}
	std::cout << "Key ";
	std::cout <<"size = "<< k.length() <<"\n";
	showVector(original_key);

	std::vector<unsigned char> original;
	std::vector<unsigned char> entext;
	std::vector<unsigned char> detext;
	std::vector<unsigned char> restored;
	std::vector<unsigned char> founded_key;

	vigener.readFromFile(filename, original);
	vigener.encrypt(original, original_key, entext);
	vigener.decrypt(entext, original_key, detext);
	
	int keysize = vigener.findKeyLength(entext);
	vigener.getKey(filestat, entext, keysize, founded_key);
	vigener.decrypt(entext, founded_key, restored);

	
	std::cout << "Original" << std::endl;
	//showVector(original);
	vigener.writeToFile("C:/Users/Anna/Desktop/original.txt", original);
	std::cout << "Encrypted" << std::endl;
	//showVector(entext);
	vigener.writeToFile("C:/Users/Anna/Desktop/entext.txt", entext);
	std::cout << "Decrypted" << std::endl;
	//showVector(detext);
	vigener.writeToFile("C:/Users/Anna/Desktop/detext.txt", detext);
	
	std::cout << std::endl << "Finding key size" << std::endl;
	std::cout << std::endl << "Key size = ";
	std::cout << keysize;
	std::cout << std::endl  << "Frequency analysis" << std::endl;
	std::cout << "Key = ";
	showVector(founded_key);
	
	std::cout << std::endl << "Restored text" << std::endl;
	//showVector(restored);
	
	
	return 0;
}




