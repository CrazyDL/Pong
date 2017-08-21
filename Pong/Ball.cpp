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
    if ((x - HALF_BALL_SIZE <= player1.x + HALF_PLAYER_WIDTH && y <= player1.y + HALF_PLAYER_HEIGHT && y >= player1.y - HALF_PLAYER_HEIGHT) ||
        (x + HALF_BALL_SIZE >= player2.x - HALF_PLAYER_WIDTH && y <= player2.y + HALF_PLAYER_HEIGHT && y >= player2.y - HALF_PLAYER_HEIGHT)) {
        dx = -dx;
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
    }
    if (dy > 0 && (y + HALF_BALL_SIZE >= player1.y + HALF_PLAYER_HEIGHT || y + HALF_BALL_SIZE >= player2.y + HALF_PLAYER_HEIGHT)
        && ((x <= player1.x + HALF_PLAYER_WIDTH && x >= player1.x - HALF_PLAYER_WIDTH) || (x <= player2.x + HALF_PLAYER_WIDTH && x >= player2.x - HALF_PLAYER_WIDTH))) {
        dy = -dy;
    }
    if (y + HALF_BALL_SIZE >= FIELD_HEIGHT) {
        y = FIELD_HEIGHT - HALF_BALL_SIZE;
        dy = -dy;
    }  
    if (y - HALF_BALL_SIZE <= 0) {
        y = HALF_BALL_SIZE;
        dy = -dy;
    }
    sprite.setPosition(x, y);
    /*switch (dir)
    {
    case 0: dx = speed; dy = -speed / 3; break;
    case 1: dx = -speed; dy = speed / 3; break;
    case 2: dx = speed; dy = speed / 3; break;
    case 3: dx = -speed; dy = -speed / 3; break;
    }
    x1 += dx*time;
    y1 += dy*time;
    sprite.setPosition(x1, y1);
    if (f)
    {
        x1 += speed*time;
        y1 += speed*time;
        sprite.setPosition(x1, y1);
    }
    //sprite.setPosition(400, 300);*/
}