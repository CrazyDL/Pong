#include "Game.h"

Game::Game() : player1(10 + HALF_PLAYER_WIDTH, FIELD_HEIGHT / 2, 1),
               player2(FIELD_WIDTH - 10 - HALF_PLAYER_WIDTH, FIELD_HEIGHT / 2, 2),
               ball(FIELD_WIDTH / 2, FIELD_HEIGHT / 2),
               window(sf::VideoMode(FIELD_WIDTH, FIELD_HEIGHT), "Pong", sf::Style::Close),
               active(false), newGame(true), pause(false) {
    window.setVerticalSyncEnabled(true);
    DrawField();
}

void Game::Menu() {
    menuFon.setSize(sf::Vector2f(FIELD_WIDTH / 3, FIELD_HEIGHT / 3));
    menuFon.setOutlineColor(sf::Color(255, 255, 255, 220));
    menuFon.setOutlineThickness(2);
    menuFon.setFillColor(sf::Color(20, 20, 20));
    menuFon.setOrigin(FIELD_WIDTH / 6, FIELD_HEIGHT / 6);
    menuFon.setPosition(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);

    menuItems[0].setString("Continue");
    menuItems[1].setString("New Game");
    menuItems[2].setString("Exit");

    float maxHeight = (menuFon.getGlobalBounds().height / (MENU_COUNT * 2));
    for (int32_t i = 0; i < MENU_COUNT; i++) {
        menuItems[i].setFont(font);
        menuItems[i].setCharacterSize((uint32_t)(maxHeight * 1.5));
        menuItems[i].setFillColor(sf::Color::White);
        menuItems[i].setStyle(sf::Text::Bold);
        menuItems[i].setPosition(menuFon.getGlobalBounds().left + 20, menuFon.getGlobalBounds().top + maxHeight * 1.8f * i);
    }

}

void Game::DrawField() {
    textureFon.loadFromFile("../Images/fon.png");
    spriteFon.setTexture(textureFon);
    spriteFon.setTextureRect(sf::IntRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT));
    font.loadFromFile("../Images/CyrilicOld.ttf");
    score.setFont(font);
    score.setCharacterSize(60);
    score.setFillColor(sf::Color::White);
    score.setStyle(sf::Text::Bold);
}

void Game::Start() {
    sf::Event event;
    float time;
    Menu();
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        time = (float)clock.getElapsedTime().asMicroseconds();
        clock.restart();
        if (player1.score == 7 || player2.score == 7) {
            active = false;
            newGame = true;
            if (player1.score == 7 ) {
                score.setString("Left Player win!");
            }
            else {
                score.setString("Right Player win!");
            }
        }
        else {
            score.setString(std::to_string(player1.score) + " : " + std::to_string(player2.score));
        }
        score.setPosition(FIELD_WIDTH / 2 - score.getGlobalBounds().width / 2, 0);

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::LostFocus:
                pause = true;
                break;
            case sf::Event::GainedFocus:
                pause = false;
                break;
            default:
                break;
            }
        }
        
        if (!pause) {
            if (active) {
                newGame = false;
                player1.Update(time);
                player2.Update(time);
                ball.Update(time, player1, player2);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    active = false;
                }
            }
            else {
                int8_t menuNum = -1;
                for (int32_t i = 0; i < MENU_COUNT; i++) {
                    if (i == 0 && newGame) {
                        menuItems[i].setFillColor(sf::Color(128, 128, 128));
                        continue;
                    }
                    if (sf::IntRect(menuItems[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window))) {
                        menuItems[i].setFillColor(sf::Color::Cyan);
                        menuNum = i;
                    }
                    else {
                        menuItems[i].setFillColor(sf::Color::White);
                    }
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    switch (menuNum) {
                    case 0:
                        active = true;
                        break;
                    case 1:
                        Reset();
                        active = true;
                        break;
                    case 2:
                        window.close();
                        break;
                    default:
                        break;
                    }
                }
            }

            window.clear();
            window.draw(spriteFon);
            window.draw(player1.sprite);
            window.draw(player2.sprite);
            window.draw(ball.sprite);
            window.draw(score);
            if (!active) {
                window.draw(menuFon);
                for (int32_t i = 0; i < MENU_COUNT; i++) {
                    window.draw(menuItems[i]);
                }
            }
            window.display();
        }
    }
}

void Game::Reset() {
    player1.score = 0;
    player2.score = 0;
    player1.y = FIELD_HEIGHT / 2;
    player2.y = FIELD_HEIGHT / 2;
    ball.dx = 0;
    ball.dy = 0;
    ball.x = FIELD_WIDTH / 2;
    ball.y = FIELD_HEIGHT / 2;
    newGame = true;
}