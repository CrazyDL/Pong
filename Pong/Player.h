#pragma once
#include <SFML/Graphics.hpp>

const float PLAYER_SPEED = 0.0006f;
const int32_t PLAYER_WIDTH = 18;
const int32_t PLAYER_HEIGHT = 104;
const int32_t HALF_PLAYER_WIDTH = PLAYER_WIDTH / 2;
const int32_t HALF_PLAYER_HEIGHT = PLAYER_HEIGHT / 2;

class Game;
class Ball;

class Player {
public:
    friend Game;
    friend Ball;

    Player(float x, float y, int32_t id);
    void Update(float time);

private:
    float x, y;
    int32_t id, score;
    sf::Sprite sprite;
    sf::Texture texture;

    void SetY();
};