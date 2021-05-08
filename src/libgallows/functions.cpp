#include <SFML/Graphics.hpp>
#include "functions.h"
#include <string>
#include <iostream>
using namespace sf;

int CheckLetter(std::string alphabet, std::string word, int a) {
	for (int i = 0; i < 7; ++i) {
		if (alphabet[a] == word[i])
			return 1;
	}
	return 0;
}
