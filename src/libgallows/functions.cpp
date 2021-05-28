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
void Theme_Word(string& tema, string& word)
{
    string path[5]
            = {"ARXITEKTYRA.txt",
               "JIVOTNuE.txt",
               "EDA.txt",
               "RASTENIa.txt",
               "TRANSPORT.txt"};
    int k;
    k = rand() % 5;
    switch (k) {
    case 0:
        tema = "ARXITEKTYRA";
    case 1:
        tema = "JIVOTNuE";
    case 2:
        tema = "EDA";
    case 3:
        tema = "RASTENIa";
    case 4:
        tema = "TRANSPORT";
    }

    ifstream fin;
    fin.open(path[k]);

    string str[11];
    k = rand() % 11;
    int i = 0;
    while (!fin.eof()) {
        fin >> str[i];
        i++;
    }
    fin.close();
    word = str[k];
}
void non_repeating_characters(int amount, int& non_repeating, string word)
{
    string outw; // Слово-контейнер (в него помещаются все неповторяющиеся
                 // символы)
    bool flag = false; // Флаг повтора
    for (int i = 0; i < amount; i++) {
        flag = false;
        for (int j = 0; j < non_repeating; j++) {
            if (word[i] == outw[j]) {
                flag = true;
            }
        }
        if (!flag) // Если не было повтора
        {
            outw += word[i];
            non_repeating = outw.length();
        }
    }
}