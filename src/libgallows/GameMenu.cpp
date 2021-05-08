#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "menu.h"
#include "functions.h"
using namespace sf;
using namespace std;

void GameMenu(RenderWindow& window)
{
	Texture GameMenuTexture, AlphabetTexture;
	GameMenuTexture.loadFromFile("Images/Background_in_the_game.jpg");
	AlphabetTexture.loadFromFile("Images/alphavite.png");
	Sprite GameBackground(GameMenuTexture), Alphabet[32];

	setlocale(LC_ALL, "Russian");
	//char AlphabetMass[32] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };
	string AlphabetMass = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	std::string word = "КУКУШКА";
	const int WORDSIZE = 7;
	int IndexWord[WORDSIZE];
	for (int i = 0; i < WORDSIZE; ++i)
		for (int j = 0; j < 32; ++j)
			if (word[i] == AlphabetMass[j])
				IndexWord[i] = j;

	Texture IndexWordImage;
	IndexWordImage.loadFromFile("Images/alphavite.png");
	Sprite IndexWordSprite[WORDSIZE];

	Texture cell_file;
	cell_file.loadFromFile("Images/cell.jpg");
	Sprite cell[7];
	for (int i = 0; i < 7; i++)
		cell[i].setTexture(cell_file);

	bool Markers[32] = { 0 };
	Texture MarkerTexture;
	MarkerTexture.loadFromFile("Images/markers.png");
	Sprite MarkerSprite[32];
	for (int i = 0; i < 32; ++i) {
		MarkerSprite[i].setTexture(MarkerTexture);
		if (CheckLetter(AlphabetMass, word, i))
			MarkerSprite[i].setTextureRect(IntRect(40, 0, 40, 55));
		else
			MarkerSprite[i].setTextureRect(IntRect(0, 0, 40, 55));
	}

	int CutImageX = 3;
	for (int i = 0; i < 32; ++i) {
		Alphabet[i].setTexture(AlphabetTexture);
		Alphabet[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
		CutImageX += 53;
	}

	for (int i = 0; i < 7; i++) {
		CutImageX = 56 * IndexWord[i];
		IndexWordSprite[i].setTexture(IndexWordImage);
	}

	bool isGameMenu = 1;
	int LetterNum = -1;

	GameBackground.setPosition(0, 0);

	int CellPositionX = 260;
	for (int i = 0; i < 7; i++) {
		cell[i].setPosition(CellPositionX, 150);
		CellPositionX += 100;
	}
	// SET POSITION
	int StartRowAlphabetX = 250, StartRowAlphabetY = 700;
	int RowAlphabetX = StartRowAlphabetX, RowAlphabetY = StartRowAlphabetY;
	for (int i = 0; i < 13; ++i) {
		Alphabet[i].setPosition(RowAlphabetX, RowAlphabetY);
		MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY+5);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX;
	RowAlphabetY += 80;
	for (int i = 13; i < 26; ++i) {
		Alphabet[i].setPosition(RowAlphabetX, RowAlphabetY);
		MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY+5);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX + 150;
	RowAlphabetY += 80;
	for (int i = 26; i < 32; ++i) {
		Alphabet[i].setPosition(RowAlphabetX, RowAlphabetY);
		MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY+5);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX; RowAlphabetY = StartRowAlphabetY;

	while (isGameMenu) {
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		for (int i = 0; i < 32; ++i) {
			Alphabet[i].setColor(Color::Black);

			LetterNum = -1;

			// Paints on hover
			for (int i = 0; i < 13; ++i) {
				if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
					Alphabet[i].setColor(sf::Color::Blue);
					LetterNum = i;
				}
				RowAlphabetX += 50;
			}
			RowAlphabetX = StartRowAlphabetX;
			RowAlphabetY += 80;
			for (int i = 13; i < 26; ++i) {
				if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
					Alphabet[i].setColor(sf::Color::Blue);
					LetterNum = i;
				}
				RowAlphabetX += 50;
			}
			RowAlphabetX = StartRowAlphabetX + 150;
			RowAlphabetY += 80;
			for (int i = 26; i < 32; ++i) {
				if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
					Alphabet[i].setColor(sf::Color::Blue);
					LetterNum = i;
				}
				RowAlphabetX += 50;
			}
			RowAlphabetX = StartRowAlphabetX; RowAlphabetY = StartRowAlphabetY;

			if (Mouse::isButtonPressed(Mouse::Left))
				for (int i = 0; i < 32; ++i)
					if (LetterNum == i)
						Markers[i] = 1;

			for (int i = 0; i < 32; ++i) {
				if (Markers[i] == 1) {
					if (CheckLetter(AlphabetMass, word, i) == 1)
						MarkerSprite[i].setColor(Color::Green);
					else
						MarkerSprite[i].setColor(Color::Red);
				}
			}


			window.draw(GameBackground);
			for (int i = 0; i < 32; ++i) {
				window.draw(Alphabet[i]);
			}
			for (int i = 0; i < 32; ++i)
				if (Markers[i] == 1)
					window.draw(MarkerSprite[i]);
			for (int i = 0; i < 7; i++)
				window.draw(cell[i]);

			window.display();
		}
	}
}
