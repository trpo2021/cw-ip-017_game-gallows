#pragma once
#include <string>

int CheckLetter(std::string word, int WORDSIZE, int a);
void FillingIndexArray(std::string word, int WORDSIZE, int NUMBERLETTERS, int* IndexWord);
int SumMistakes(bool* Markers, std::string word, int NUMBERLETTERS, int WORDSIZE);
int ManYouRight(bool* Markers, std::string word, int NUMBERLETTERS, int WORDSIZE);
