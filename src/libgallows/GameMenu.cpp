#include <SFML/Graphics.hpp>
#include "menu.h"
using namespace sf;

void GameMenu(RenderWindow& window)
{
	//char AlphabetMass[32] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };
	Texture GameMenuTexture, AlphabetTexture;
	GameMenuTexture.loadFromFile("Images/Background_in_the_game.jpg");
	AlphabetTexture.loadFromFile("Images/alphavite.png");
	Sprite GameBackground(GameMenuTexture), Alphabet[32];

	int CutImageX = 3;
	for (int i = 0; i < 32; ++i) {
		Alphabet[i].setTexture(AlphabetTexture);
		Alphabet[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
		CutImageX += 53;
	}

	bool isMenu = 1;
	//int MenuNum = 0;

	GameBackground.setPosition(0, 0);
// SET POSITION FOR ALPHABET
	int StartRowAlphabetX = 250, StartRowAlphabetY = 700;
	int RowAlphabetX = StartRowAlphabetX, RowAlphabetY = StartRowAlphabetY;
	for (int i = 0; i < 13; ++i) {
		Alphabet[i].setPosition(RowAlphabetX, RowAlphabetY);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX;
	RowAlphabetY += 80;
	for (int i = 13; i < 26; ++i) {
		Alphabet[i].setPosition(RowAlphabetX, RowAlphabetY);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX + 150;
	RowAlphabetY += 80;
	for (int i = 26; i < 32; ++i) {
		Alphabet[i].setPosition(RowAlphabetX, RowAlphabetY);
		RowAlphabetX += 50;
	}
	RowAlphabetX = StartRowAlphabetX; RowAlphabetY = StartRowAlphabetY;

	while (isMenu) {
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		for (int i = 0; i < 32; ++i)
			Alphabet[i].setColor(Color::Black);

		//MenuNum = 0;

		// Paints on hover
		for (int i = 0; i < 13; ++i) {
			if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
				Alphabet[i].setColor(sf::Color::Blue);
				//MenuNum = i;
			}
			RowAlphabetX += 50;
		}
		RowAlphabetX = StartRowAlphabetX;
		RowAlphabetY += 80;
		for (int i = 13; i < 26; ++i) {
			if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
				Alphabet[i].setColor(sf::Color::Blue);
				//MenuNum = i;
			}
			RowAlphabetX += 50;
		}
		RowAlphabetX = StartRowAlphabetX + 150;
		RowAlphabetY += 80;
		for (int i = 26; i < 32; ++i) {
			if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60).contains(Mouse::getPosition(window))) {
				Alphabet[i].setColor(sf::Color::Blue);
				//MenuNum = i;
			}
			RowAlphabetX += 50;
		}
		RowAlphabetX = StartRowAlphabetX; RowAlphabetY = StartRowAlphabetY;



		window.draw(GameBackground);
		for (int i = 0; i < 32; ++i)
			window.draw(Alphabet[i]);

		window.display();
	}
}
