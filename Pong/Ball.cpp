#include "Ball.h"
#include "Game.h"

Ball::Ball(float x, float y) : x(x), y(y), dx(0), dy(0) {
    texture.loadFromFile("../Images/ball.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, BALL_SIZE, BALL_SIZE));
    sprite.setOrigin((float)HALF_BALL_SIZE, (float)HALF_BALL_SIZE);
    sprite.setPosition(x, y);
}

bool Ball::CheckCollision(int8_t route, float playerX, float playerY) {
    switch (route){
    case 1: // Down
        if (y + HALF_BALL_SIZE >= playerY - HALF_PLAYER_HEIGHT && y < playerY - HALF_PLAYER_HEIGHT && x + HALF_BALL_SIZE >= playerX - HALF_PLAYER_WIDTH && x - HALF_BALL_SIZE <= playerX + HALF_PLAYER_WIDTH)
            return true;
        break;
    case 2: // Up
        if (y - HALF_BALL_SIZE <= playerY + HALF_PLAYER_HEIGHT && y > playerY + HALF_PLAYER_HEIGHT && x + HALF_BALL_SIZE >= playerX - HALF_PLAYER_WIDTH && x - HALF_BALL_SIZE <= playerX + HALF_PLAYER_WIDTH)
            return true;
        break;
    case 3: // Left
        if (x - HALF_BALL_SIZE <= playerX + HALF_PLAYER_WIDTH && y + HALF_BALL_SIZE >= playerY - HALF_PLAYER_HEIGHT && y - HALF_BALL_SIZE <= playerY + HALF_PLAYER_HEIGHT)
            return true;
        break;
    case 4: // Right
        if (x + HALF_BALL_SIZE >= playerX - HALF_PLAYER_WIDTH && y + HALF_BALL_SIZE >= playerY - HALF_PLAYER_HEIGHT && y - HALF_BALL_SIZE <= playerY + HALF_PLAYER_HEIGHT)
            return true;
        break;
    default:
        return false;
    }
    return false;
}

void Ball::Update(float time, Player &player1, Player &player2) {
    if (!dx && !dy) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            int32_t rnd = std::rand() % 2;
            dx = BALL_SPEED * (rnd ? 2 : -2);
            rnd = std::rand() % 2;
            dy = BALL_SPEED * (rnd ? 1 : -1);
        }
    }
    x += dx * time;
    y += dy * time;

    if ((dy > 0 && (CheckCollision(1, player1.x, player1.y) || CheckCollision(1, player2.x, player2.y))) ||
        ((dy < 0 && (CheckCollision(2, player1.x, player1.y) || CheckCollision(2, player2.x, player2.y))))) {
        dy = -dy;
    }

    if ((dx < 0 && CheckCollision(3, player1.x, player1.y)) ||
        (dx > 0 && CheckCollision(4, player2.x, player2.y))) {
        dx = -dx;
    }

    if (y + HALF_BALL_SIZE >= FIELD_HEIGHT) {
        y = FIELD_HEIGHT - HALF_BALL_SIZE;
        dy = -dy;
    }
    else if (y - HALF_BALL_SIZE <= 0) {
        y = HALF_BALL_SIZE;
        dy = -dy;
    }

    if (x + HALF_BALL_SIZE >= FIELD_WIDTH || x - HALF_BALL_SIZE <= 0) {
        if (x + HALF_BALL_SIZE >= FIELD_WIDTH)
            player1.score++;
        else
            player2.score++;
        dx = 0;
        dy = 0;
        x = FIELD_WIDTH / 2;
        y = FIELD_HEIGHT / 2;
        _sleep(200);
    }
    sprite.setPosition(x, y);
}