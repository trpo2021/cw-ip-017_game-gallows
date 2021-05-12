#include <SFML/Graphics.hpp>
#include "functions.h"
#include <string>
#include <iostream>
using namespace sf;

std::string alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

void FillingIndexArray(std::string word, int WORDSIZE, int *IndexWord) {
	for (int i = 0; i < WORDSIZE; ++i)
		for (int j = 0; j < 32; ++j)
			if (word[i] == alphabet[j])
				IndexWord[i] = j;
}
int CheckLetter(std::string word, int a) {
	for (int i = 0; i < 7; ++i) {
		if (alphabet[a] == word[i])
			return 1;
	}
	return 0;
}
