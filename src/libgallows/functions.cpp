#include <SFML/Graphics.hpp>
#include "functions.h"
#include <string>
#include <iostream>
using namespace sf;

std::string alphabet = "AFFFFFFFFFKFFFFFFFFUFFFFSFFFFFFF";
//std::string alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

void FillingIndexArray(std::string word, int WORDSIZE, int NUMBERLETTERS, int* IndexWord) {
	for (int i = 0; i < WORDSIZE; ++i)
		for (int j = 0; j < NUMBERLETTERS; ++j)
			if (word[i] == alphabet[j])
				IndexWord[i] = j;
}
int CheckLetter(std::string word, int WORDSIZE, int a) {
	for (int i = 0; i < WORDSIZE; ++i) {
		if (alphabet[a] == word[i])
			return 1;
	}
	return 0;
}
int SumMistakes(bool* Markers, std::string word, int NUMBERLETTERS, int WORDSIZE) {
	int s = -1;
	for (int i = 0; i < NUMBERLETTERS; ++i) {
		if (!CheckLetter(word, WORDSIZE, i))
			s += Markers[i];
	}
	return s;
}
int ManYouRight(bool* Markers, std::string word, int NUMBERLETTERS, int WORDSIZE) {
	int s = 0;
	for (int i = 0; i < NUMBERLETTERS; ++i) {
		if (CheckLetter(word, WORDSIZE, i))
			s += Markers[i];
	}
	return s;
}
