#include "Game.h"

Game::Game() : player1(10 + HALF_PLAYER_WIDTH, FIELD_HEIGHT / 2, 1),
               player2(FIELD_WIDTH - 10 - HALF_PLAYER_WIDTH, FIELD_HEIGHT / 2, 2),
               ball(FIELD_WIDTH / 2, FIELD_HEIGHT / 2),
               window(sf::VideoMode(FIELD_WIDTH, FIELD_HEIGHT), "Pong", sf::Style::Close) {
    window.setVerticalSyncEnabled(true);
    DrawField();
}

void Game::DrawField() {
    textureFon.loadFromFile("../Images/fon.png");
    spriteFon.setTexture(textureFon);
    spriteFon.setTextureRect(sf::IntRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT));
}

void Game::Start() {
    sf::Event event;
    float time;
    while (window.isOpen()) {
        time = (float)clock.getElapsedTime().asMicroseconds();
        clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        player1.Update(time);
        player2.Update(time);
        ball.Update(time, player1, player2);

        /*score.setString("kek");//std::to_string(player1.score) + ":" + std::to_string(player2.score));
        score.setCharacterSize(100);
        score.setFillColor(sf::Color::White);
        score.setStyle(sf::Text::Bold);
        score.setPosition(0, 0);*/


        window.clear();
        window.draw(spriteFon);
        window.draw(player1.sprite);
        window.draw(player2.sprite);
        window.draw(ball.sprite);
        window.draw(score);
        window.display();
    }
}