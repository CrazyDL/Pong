#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"

const int32_t FIELD_WIDTH = 1000;
const int32_t FIELD_HEIGHT = 600;

class Game {
public:
    friend Ball;
    Game();
    void Start();
protected:
    void DrawField();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Sprite spriteFon;
    sf::Texture textureFon;
    sf::Text score;
    Player player1;
    Player player2;
    Ball ball;
};
