#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "menu.h"
#include "functions.h"
using namespace sf;
using namespace std;

void GameMenu(RenderWindow& window)
{
	setlocale(LC_ALL, "Russian");
	string word = "KUKUSKA";
	// string word = "КУКУШКА";
	const int WORDSIZE = 7;

	cout << "";

	int IndexWord[WORDSIZE];
	FillingIndexArray(word, WORDSIZE, IndexWord);

	Texture GameMenuTexture, AlphabetTexture, cell_file, MarkerTexture, WordImage;
	GameMenuTexture.loadFromFile("Images/Background_in_the_game.jpg"); // Задний план игры
	AlphabetTexture.loadFromFile("Images/alphavite.png"); // Алфавит для выбора букв
	cell_file.loadFromFile("Images/cell.jpg"); // Ячейки для растановки загаданного слова
	MarkerTexture.loadFromFile("Images/markers.png"); // Маркеры для букв, что уже нажали
	WordImage.loadFromFile("Images/alphavite.png");

	Sprite GameBackground(GameMenuTexture);
	GameBackground.setPosition(0, 0);

	Sprite AlphabetSprite[32];
	int CutImageX = 3; // Координата, с которой нужно начать вырезать буквы
	for (int i = 0; i < 32; ++i) {
		AlphabetSprite[i].setTexture(AlphabetTexture);
		AlphabetSprite[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
		CutImageX += 53;
	}

	Sprite MarkerSprite[32];
	for (int i = 0; i < 32; ++i) {
		MarkerSprite[i].setTexture(MarkerTexture);
		if (CheckLetter(word, i))
			MarkerSprite[i].setTextureRect(IntRect(40, 0, 40, 55));
		else
			MarkerSprite[i].setTextureRect(IntRect(0, 0, 40, 55));
	}
	int StartRowAlphabetX = 250, StartRowAlphabetY = 700;
	int RowAlphabetX = StartRowAlphabetX, RowAlphabetY = StartRowAlphabetY;
	for (int i = 0; i < 13; ++i) {
		AlphabetSprite[i].setPosition(RowAlphabetX, RowAlphabetY);
		MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY + 5);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX;
	RowAlphabetY += 80;
	for (int i = 13; i < 26; ++i) {
		AlphabetSprite[i].setPosition(RowAlphabetX, RowAlphabetY);
		MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY + 5);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX + 150;
	RowAlphabetY += 80;
	for (int i = 26; i < 32; ++i) {
		AlphabetSprite[i].setPosition(RowAlphabetX, RowAlphabetY);
		MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY + 5);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX; RowAlphabetY = StartRowAlphabetY;

	Sprite WordSprite[WORDSIZE];
	for (int i = 0; i < WORDSIZE; i++) {
		CutImageX = 53 * (IndexWord[i] + 1 ) - 53 + 3;
		WordSprite[i].setTexture(WordImage);
		WordSprite[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
	}

	Sprite CellSprite[7];
	for (int i = 0; i < 7; i++)
		CellSprite[i].setTexture(cell_file);
	int CellPositionX = 260;
	for (int i = 0; i < WORDSIZE; i++) {
		CellSprite[i].setPosition(CellPositionX, 150);
		WordSprite[i].setPosition(CellPositionX + 8, 80);
		CellPositionX += 100;
	}

	bool isGameMenu = 1;
	int LetterNum = -1;
	bool Markers[32] = { 0 };
	bool WordLetter[WORDSIZE] = { 0 };

	while (isGameMenu) {
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		LetterNum = -1;

		for (int i = 0; i < 32; ++i) {
			AlphabetSprite[i].setColor(Color::Black);
		}

		for (int i = 0; i < WORDSIZE; ++i) {
			WordSprite[i].setColor(Color::Black);
		}

			for (int i = 0; i < 13; ++i) {
				if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
					AlphabetSprite[i].setColor(sf::Color::Blue);
					(LetterNum) = i;
				}
				RowAlphabetX += 50;
			}
			RowAlphabetX = StartRowAlphabetX;
			RowAlphabetY += 80;
			for (int i = 13; i < 26; ++i) {
				if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
					AlphabetSprite[i].setColor(sf::Color::Blue);
					(LetterNum) = i;
				}
				RowAlphabetX += 50;
			}
			RowAlphabetX = StartRowAlphabetX + 150;
			RowAlphabetY += 80;
			for (int i = 26; i < 32; ++i) {
				if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
					AlphabetSprite[i].setColor(sf::Color::Blue);
					(LetterNum) = i;
				}
				RowAlphabetX += 50;
			}
			RowAlphabetX = StartRowAlphabetX; RowAlphabetY = StartRowAlphabetY;


			if (Mouse::isButtonPressed(Mouse::Left))
				for (int i = 0; i < 32; ++i)
					if (LetterNum == i) {
						Markers[i] = 1;
						for (int j = 0; j < WORDSIZE; ++j)
							if (IndexWord[j] == i)
								WordLetter[j] = 1;
					}

			for (int i = 0; i < 32; ++i) {
				if (Markers[i] == 1) {
					if (CheckLetter(word, i))
						MarkerSprite[i].setColor(Color::Green);
					else
						MarkerSprite[i].setColor(Color::Red);
				}
			}

			window.draw(GameBackground);
			for (int i = 0; i < 32; ++i) {
				window.draw(AlphabetSprite[i]);
			}
			for (int i = 0; i < 32; ++i)
				if (Markers[i])
					window.draw(MarkerSprite[i]);
			for (int i = 0; i < WORDSIZE; i++) {
				window.draw(CellSprite[i]);

				if (WordLetter[i])
					window.draw(WordSprite[i]);
			}

			window.display();
	}
}
