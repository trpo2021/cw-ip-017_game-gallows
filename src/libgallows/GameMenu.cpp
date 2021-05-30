#include "functions.h"
#include "menu.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace sf;
using namespace std;

void GameMenu(RenderWindow& window, int Selectnum)
{
    //srand(time(NULL));
    string theme, word;
    Theme_Word(theme, word);
    cout << word;
    int rand_letter;
    const int CountPossibleMistakes = 6;
    int WORDSIZE = word.length();
    int Themewordsize = theme.length();
    int* IndexTheme = new int[Themewordsize];
    int CountRightLetters;
    CountRightLetters = non_repeating_characters(WORDSIZE, word);
    const int NUMBERLETTERS = 32; // Количество букв в алфавите

    int* IndexWord = new int[WORDSIZE];
    FillingIndexArray(word, WORDSIZE, NUMBERLETTERS, IndexWord);
    FillingIndexArray(theme, Themewordsize, NUMBERLETTERS, IndexTheme);
    rand_letter = rand() % WORDSIZE;
    Music GameMusic;
    GameMusic.openFromFile("Music/GameMenuMusic.wav");
    GameMusic.setVolume(15.f);
    GameMusic.play();

    Music Last10Sec;
    Last10Sec.openFromFile("Music/Last10sec.wav");
    Last10Sec.setVolume(5.f);

    Texture GameMenuTexture, GameMenuTexture_victory0, GameMenuTexture_victory1,
            GameMenuTexture_victory2 ,AlphabetTexture, cell_file,
            MarkerTexture,
            WordImage, GameMenuDefeatTexture, VictoryTexture, DefeatTexture,
            PartsGallowsTexture,
            TimerNumbersTexture;
    GameMenuDefeatTexture.loadFromFile(
            "Images/Background_in_the_game_defeat.jpg");
    GameMenuTexture.loadFromFile("Images/Background_in_the_game.jpg");
    AlphabetTexture.loadFromFile("Images/alphavite.png");
    GameMenuTexture_victory0.loadFromFile("Images/four_mistakes.jpg");
    GameMenuTexture_victory1.loadFromFile("Images/Victory_animation.jpg");
    GameMenuTexture_victory2.loadFromFile("Images/victory.jpg");
    cell_file.loadFromFile("Images/cell.jpg");
    MarkerTexture.loadFromFile("Images/markers.png");
    WordImage.loadFromFile("Images/alphavite.png");
    VictoryTexture.loadFromFile("Images/initial_victory.jpg");
    PartsGallowsTexture.loadFromFile("Images/Parts_Of_Gallows.png");
    DefeatTexture.loadFromFile("Images/defeat.jpg");
    TimerNumbersTexture.loadFromFile("Images/numbers_for_timer.png");

    Sprite TimerNumbersSprite[9];
    int CutImageXPartsTimerNumbers = 56;
    for (int i = 0; i < 9; ++i) {
        TimerNumbersSprite[i].setTexture(TimerNumbersTexture);
        TimerNumbersSprite[i].setTextureRect(
                IntRect(CutImageXPartsTimerNumbers, 1, 54, 98));
        TimerNumbersSprite[i].setPosition(1080, 530);
        CutImageXPartsTimerNumbers += 55;
    }

    Sprite DefeatSprite;
    DefeatSprite.setTexture(DefeatTexture);
    DefeatSprite.setPosition(65, 100);

    Sprite PartsGallowsSprite[CountPossibleMistakes-1];
    int CutImageXPartsGallows = 1;
    for (int i = 0; i < CountPossibleMistakes-1; ++i) {
        PartsGallowsSprite[i].setTexture(PartsGallowsTexture);
        PartsGallowsSprite[i].setTextureRect(
                IntRect(CutImageXPartsGallows, 1, 241, 398));
        PartsGallowsSprite[i].setPosition(800, 240);
 
            CutImageXPartsGallows += 242;
    }

    Sprite GameBackground(GameMenuTexture),
            GameBackground_defeat(GameMenuDefeatTexture),
            GameBackground_victory[3];
    GameBackground.setPosition(0, 0);
    GameBackground_victory[0].setTexture(GameMenuTexture_victory0);
    GameBackground_victory[1].setTexture(GameMenuTexture_victory1);
    GameBackground_victory[2].setTexture(GameMenuTexture_victory2);
    for (int  i = 0; i < 3; i++) {
        GameBackground_victory[i].setPosition(0, 0);
    }
    GameBackground_defeat.setPosition(0, 0);
    Sprite AlphabetSprite[NUMBERLETTERS];
    int CutImageX = 3; // Координата, с которой нужно начать вырезать буквы
    for (int i = 0; i < NUMBERLETTERS; ++i) {
        AlphabetSprite[i].setTexture(AlphabetTexture);
        AlphabetSprite[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
        CutImageX += 53;
    }

    Sprite* MarkerSprite = new Sprite[NUMBERLETTERS];
    for (int i = 0; i < NUMBERLETTERS; ++i) {
        MarkerSprite[i].setTexture(MarkerTexture);
        if (CheckLetter(word, WORDSIZE, i))
            MarkerSprite[i].setTextureRect(IntRect(40, 0, 40, 55));
        else
            MarkerSprite[i].setTextureRect(IntRect(0, 0, 40, 55));
    }

    int StartRowAlphabetX = 250, StartRowAlphabetY = 700;
    int RowAlphabetX = StartRowAlphabetX, RowAlphabetY = StartRowAlphabetY;
    for (int i = 0; i < 32; ++i) {
        AlphabetSprite[i].setPosition(RowAlphabetX, RowAlphabetY);
        MarkerSprite[i].setPosition(RowAlphabetX, RowAlphabetY + 5);
        RowAlphabetX += 50;
        if (i == 12) {
            RowAlphabetX = StartRowAlphabetX;
            RowAlphabetY += 80;
        } else if (i == 25) {
            RowAlphabetX = StartRowAlphabetX + 150;
            RowAlphabetY += 80;
        }
    }
    RowAlphabetX = StartRowAlphabetX;
    RowAlphabetY = StartRowAlphabetY;

    Sprite* WordSprite = new Sprite[WORDSIZE];
    for (int i = 0; i < WORDSIZE; i++) {
        CutImageX = 53 * (IndexWord[i] + 1) - 53 + 3;
        WordSprite[i].setTexture(WordImage);
        WordSprite[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
    }
    CutImageX = 3;
    Sprite* ThemeSprite = new Sprite[Themewordsize];
    for (int i = 0; i < Themewordsize; i++) {
        CutImageX = 53 * (IndexTheme[i] + 1) - 53 + 3;
        ThemeSprite[i].setTexture(WordImage);
        ThemeSprite[i].setTextureRect(IntRect(CutImageX, 25, 47, 69));
    }
    int Theme_Letter_positionX = 420;
    for (int i = 0; i < Themewordsize; i++) {
        ThemeSprite[i].setPosition(Theme_Letter_positionX, 160);
        Theme_Letter_positionX += 35;
    }
    Sprite* CellSprite = new Sprite[WORDSIZE];
    for (int i = 0; i < WORDSIZE; i++)
        CellSprite[i].setTexture(cell_file);
    int CellPositionX = 260;
    for (int i = 0; i < WORDSIZE; i++) {
        CellSprite[i].setPosition(CellPositionX, 150);
        WordSprite[i].setPosition(CellPositionX + 8, 80);
        CellPositionX += 100;
    }

    Sprite VictorySprite;
    VictorySprite.setTexture(VictoryTexture);
    VictorySprite.setPosition(200, 100);

    bool isGameOver = 0;
    bool isGameMenu = 1;
    int LetterNum = -1;
    bool Markers[NUMBERLETTERS] = {0};
    Markers[IndexWord[rand_letter]] = 1;
    bool* WordLetter = new bool[WORDSIZE];
    for (int i = 0; i < WORDSIZE; ++i)
        WordLetter[i] = 0;
    int SummMistakes = -1;
    int SumRightLettersSelectPlayer = 0;

    Clock timer;
    int tm = 10;
    bool StartTimer = 0;
    int state = 0;

    if (Selectnum == 1) {
        SumRightLettersSelectPlayer++;
        WordLetter[rand_letter] = 1;
    }
    SoundBuffer shotBuffer;
    shotBuffer.loadFromFile("Music/Shot_sound.wav");
    Sound shoot;
    shoot.setBuffer(shotBuffer);
    bool testsound = 0;
    while (isGameMenu) {

        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        LetterNum = -1;
        
        SumRightLettersSelectPlayer
                = ManYouRight(Markers, word, NUMBERLETTERS, WORDSIZE);
        
        if (tm != 0)
            SummMistakes = SumMistakes(Markers, word, NUMBERLETTERS, WORDSIZE);
        else {
            SummMistakes++;
        }

        if (StartTimer == 0 && SummMistakes == CountPossibleMistakes - 1) {
            GameMusic.stop();
            Last10Sec.play();
            Clock TempTimer;
            timer = TempTimer;
            StartTimer = 1;
        }
        if (SummMistakes == (CountPossibleMistakes - 1) && tm != 0
            && SumRightLettersSelectPlayer < CountRightLetters)
            tm = 10 - timer.getElapsedTime().asSeconds();

        for (int i = 0; i < NUMBERLETTERS; ++i) {
            AlphabetSprite[i].setColor(Color::Black);
        }
        for (int i = 0; i < Themewordsize; i++) {
            ThemeSprite[i].setColor(Color::Black);
        }
        for (int i = 0; i < WORDSIZE; ++i) {
            WordSprite[i].setColor(Color::Black);
        }

        for (int i = 0; i < 9; ++i) {
            if (tm > 3)
                TimerNumbersSprite[i].setColor(Color::Black);
            else
                TimerNumbersSprite[i].setColor(Color::Red);
        }

        if (SumRightLettersSelectPlayer == CountRightLetters
            || SummMistakes == CountPossibleMistakes)
            isGameOver = 1;
        if (isGameOver == 0) {
            for (int i = 0; i < 32; ++i) {
                if (IntRect(RowAlphabetX, RowAlphabetY, 44, 60)
                            .contains(Mouse::getPosition(window))) {
                    AlphabetSprite[i].setColor(sf::Color::Blue);
                    (LetterNum) = i;
                }
                RowAlphabetX += 50;
                if (i == 12) {
                    RowAlphabetX = StartRowAlphabetX;
                    RowAlphabetY += 80;
                } else if (i == 25) {
                    RowAlphabetX = StartRowAlphabetX + 150;
                    RowAlphabetY += 80;
                }
            }
            RowAlphabetX = StartRowAlphabetX;
            RowAlphabetY = StartRowAlphabetY;

            if (Mouse::isButtonPressed(Mouse::Left))
                for (int i = 0; i < NUMBERLETTERS; ++i)
                    if (LetterNum == i) {
                        Markers[i] = 1;
                        for (int j = 0; j < WORDSIZE; ++j)
                            if (IndexWord[j] == i)
                                WordLetter[j] = 1;
                    }

            for (int i = 0; i < NUMBERLETTERS; ++i) {
                if (Markers[i] == 1) {
                    if (CheckLetter(word, WORDSIZE, i))
                        MarkerSprite[i].setColor(Color::Green);
                    else
                        MarkerSprite[i].setColor(Color::Red);
                }
            }
        }
        
        if (tm) {
            if (SummMistakes == CountPossibleMistakes - 1 && tm != 0
                && tm != 10) {
                window.draw(GameBackground_victory[0]);
                window.draw(TimerNumbersSprite[tm - 1]);
                state = 1;
            } else
                window.draw(GameBackground);
        } else {
            window.draw(GameBackground_defeat);
            window.draw(DefeatSprite);
        }
        for (int i = 0; i < NUMBERLETTERS; ++i) {
            window.draw(AlphabetSprite[i]);
        }

        if (SumRightLettersSelectPlayer == CountRightLetters && state == 1) {
            if (testsound == 0) {
                shoot.play();
                testsound = 1;
            }
            window.draw(GameBackground_victory[2]);

        }
         else if (SumRightLettersSelectPlayer == CountRightLetters && state == 0)
            window.draw(VictorySprite);
            
        

        if (SummMistakes > -1 && SummMistakes < CountPossibleMistakes-1
            && SumRightLettersSelectPlayer < CountRightLetters)
            window.draw(PartsGallowsSprite[SummMistakes]);

        for (int i = 0; i < NUMBERLETTERS; ++i)
            if (Markers[i])
                window.draw(MarkerSprite[i]);


        

        if (SummMistakes < CountPossibleMistakes
            && SumRightLettersSelectPlayer < CountRightLetters) {
            if (Selectnum == 1) {
               
                for (int i = 0; i < Themewordsize; i++)
                    window.draw(ThemeSprite[i]);
            }
            if (Selectnum == 2)

                for (int i = 0; i < Themewordsize; i++)
                    window.draw(ThemeSprite[i]);
            for (int i = 0; i < WORDSIZE; i++) {
                window.draw(CellSprite[i]);

                if (WordLetter[i])
                    window.draw(WordSprite[i]);
            }
        }

        
        window.display();
    }

    delete[] IndexWord;
    delete[] WordSprite;
    delete[] CellSprite;
    delete[] WordLetter;
    delete[] MarkerSprite;
    delete[] IndexTheme;
}
