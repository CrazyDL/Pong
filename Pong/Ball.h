#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

const float BALL_SPEED = 0.0003f;
const int32_t BALL_SIZE = 20;
const int32_t HALF_BALL_SIZE = BALL_SIZE / 2;

class Game;

class Ball {
public:
    friend Game;

    Ball(float x, float y);
    void Update(float time, Player &player1, Player &player2);
private:
    float x, y, dx, dy;
    sf::Sprite sprite;
    sf::Texture texture;

    bool CheckCollision(int8_t route, float playerX, float playerY);
};