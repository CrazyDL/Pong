#include "Player.h"
#include "Game.h"

Player::Player(float x, float y, int32_t id) : x(x), y(y), id(id), score(0) {
    texture.loadFromFile("../Images/player.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    sprite.setOrigin((float)HALF_PLAYER_WIDTH, (float)HALF_PLAYER_HEIGHT);
    sprite.setPosition(x, y);
    if (id == 2) {
        sprite.scale(-1, 1);
    }
}

void Player::SetY() {
    if (y - HALF_PLAYER_HEIGHT < 0) {
        y = HALF_PLAYER_HEIGHT;
    }
    else if (y + HALF_PLAYER_HEIGHT > FIELD_HEIGHT) {
        y = FIELD_HEIGHT - HALF_PLAYER_HEIGHT;
    }
    sprite.setPosition(x, y);
}

void Player::Update(float time) {
    if (id == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y -= time * PLAYER_SPEED;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += time * PLAYER_SPEED;

        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= time * PLAYER_SPEED;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y += time * PLAYER_SPEED;
        }
    }
    SetY();
}