#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"

const int16_t FIELD_WIDTH = 1000;
const int16_t FIELD_HEIGHT = 600;
const int8_t MENU_COUNT = 3;

class Game {
public:
    friend Ball;
    Game();
    void Start();
    void Menu();
protected:
    void DrawField();
    void Reset();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Sprite spriteFon;
    sf::Texture textureFon;
    sf::RectangleShape menuFon;
    sf::Text menuItems[MENU_COUNT];
    sf::Font font;
    sf::Text score;
    Player player1;
    Player player2;
    Ball ball;
    bool pause;
    bool active;
    bool newGame;
};
