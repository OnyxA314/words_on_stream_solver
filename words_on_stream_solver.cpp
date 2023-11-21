#include <iostream>
#include <fstream>
#include <string>

#include <vector>
using namespace std;


void limit_to_range(ifstream &MyFile, vector <string> &words, int min_letters, int max_letters);
 
void limit_to_characters (vector <string> &words, char valid_letters[], int unique_letters, bool wanted_letter_used[]);




int main (void)
{

	ifstream MyFile("wos_dictionary.txt");	//gets file from disk

	int min_letters, max_letters, total_letters;
	
	char wanted_letters[26];
	bool wanted_letter_used[26] = {false}; //array to tell if a letter has been used


	vector <string> words;	//vector to hold all words. Vector as we don't know length @ compile time



	cout << "Minimum allowed letters: ";
	cin >> min_letters;

	cout << "Maximum allowed letters: ";
	cin >> max_letters;

	cout << "How many total letters: ";
	cin >> total_letters;


	for (int i = 0; i < total_letters; i++)	//gets valid letters from user
	{
		cout << "Enter a character: ";
		cin >> wanted_letters[i];
	}

	
	limit_to_range(MyFile, words, min_letters, max_letters);


	limit_to_characters(words, wanted_letters, total_letters, wanted_letter_used);

	
	for (string num : words)	//prints out all valid values
	{
		cout << num << endl;
	}


	return 0;
}




void limit_to_range(ifstream &MyFile, vector <string> &words, int min_letters, int max_letters)
{
	string current_word;

	while (getline (MyFile, current_word))	//goes thorugh file on disk line by line
	{
		//if the word is above or equal the min lenght, but below or equal max lenght
		if (current_word.length() >= min_letters && current_word.length() <= max_letters)
		{
			//cout << current_word << endl;
			words.push_back(current_word);	//adds words to vector
		}
	}


	return;
}




void limit_to_characters (vector <string> &words, char valid_letters[], int unique_letters, bool wanted_letter_used[])
{
	vector <string> valid_words; //new vector to temporary store items
	
	bool valid_flag;	//valid word flag
	
	bool valid_char;	//valid char flag


	for (string word_check : words) //like "for word_check in words"
	{
		valid_flag = true;	//assumes word is valid by default
		
		//cout << "\nCurrent Word: " << word_check; //debug
		//cout << " Current Word Letters: ";	//debug
		
		for (char ch : word_check)	//goes thorugh every character in the word
		{
			//cout << ch << " ";	//debug
			
			valid_char = false;	//assumes char is invalid by default
			
			for (int i = 0; i < unique_letters; i++)	//while characters to check against valid_letters
			{
				if (ch == valid_letters[i])	//if a valid_letter has been found
				{
					if (!wanted_letter_used[i])	//if it's position has not been marked as being already used. 
					{
						valid_char = true;		
						wanted_letter_used[i] = true;
					}
				}

				if (valid_char) //if we found a valid_char then we don't need to check the list. Also needed otherwise if one letter is used multiple times it marks every instance as used instead of just 1
				{
					break;
				}
			}

			if (!valid_char)	//if a character is invalid, we know the word is invalid
			{
				valid_flag = false;

				break; //can break out of the loop as if a single letter is invalid we don't need to check the rest.Theroretically helps performance but it takes a small time anyway doesn't matter
			}
		}
		


		for (int i = 0; i < unique_letters; i++) //resets check if a letter was used
		{
			wanted_letter_used[i] = false;
		}


		if (valid_flag) //if the word is valid we know all possible characters are valid
		{
			valid_words.push_back(word_check); //pushes known valid word onto the vector
		}
	}
	
	words = valid_words;

	/*
	for (string final_list : valid_words)
	{
		cout << final_list << endl;
	}
	*/
}
