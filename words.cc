#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int debug = 0;
std::vector <std::string> words;

void populateWords()
{
	std::ifstream wordsFile;
	wordsFile.open("./Data/words.txt");

	std::string line;

	if(wordsFile.is_open())
	{
		while(getline (wordsFile, line))
		{
			words.push_back(line);
		}
		wordsFile.close();
	}
	else
	{
		std::cout << "Unable to open file\n";
	}
}

int stringWordMatch(std::string s, std::string word)
{
	std::size_t where = -1;

	if(s[0] != word[0])
		return 0;
	else
	{
		word = word.substr(1);
		where = word.find(s[1]);

		if(where == -1)
			return 0;
		else
		{
			word = word.substr(where);
			where = -1;
			where = word.find(s[2]);
		}
	}

	if(where == -1)
		return 0;
	else
		return 1;
}

std::vector <std::string> getWords(std::string s)
{
	std::vector <std::string> results;

	for(int i = 0; i < words.size(); i++)
	{
		if(stringWordMatch(s, words[i]))
			results.push_back(words[i]);
	}
	return results;
}

void playGame()
{
	std::string stringy;
	int keepGoing = 1;

	while(keepGoing)
	{
		std::cout << "Please enter the 3 letters to find all words associated: ";
		std::cin >> stringy;

		std::vector <std::string> results = getWords(stringy);

		for(int i = 0; i < results.size(); i++)
			std::cout << results[i] << "\n";
		
		std::cout << "\n\nDo you want to play again?\nIf so enter 1\nIf not enter 0\n";
		std::cin >> keepGoing;
	}
}

int main()
{
	populateWords();

	std::cout << "Welcome to a fun program!\n"
						<< "This will find words associated with the 3 letters from a license plate!\n";

	playGame();

	std::cout << "\n\nThank you for playing!\n";

	if(debug)
	{
		for(int i = 0; i < words.size(); i++)
			std::cout << words[i] << "\n";
	}

	return 0;
}
