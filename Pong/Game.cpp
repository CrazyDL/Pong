#include "Game.h"

Game::Game() : player1(10 + HALF_PLAYER_WIDTH, FIELD_HEIGHT / 2, 1),
               player2(FIELD_WIDTH - 10 - HALF_PLAYER_WIDTH, FIELD_HEIGHT / 2, 2),
               ball(FIELD_WIDTH / 2, FIELD_HEIGHT / 2),
               window(sf::VideoMode(FIELD_WIDTH, FIELD_HEIGHT), "Pong", sf::Style::Close),
               active(false), newGame(true), pause(false) {
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    DrawField();
}

void Game::Menu() {
    menuFon.setSize(sf::Vector2f(FIELD_WIDTH / 3, FIELD_HEIGHT / 3));
    menuFon.setOutlineColor(sf::Color::White);
    menuFon.setOutlineThickness(2);
    menuFon.setFillColor(sf::Color(20, 20, 20));
    menuFon.setOrigin(FIELD_WIDTH / 6, FIELD_HEIGHT / 6);
    menuFon.setPosition(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);

    menuItems[0].setString("Continue");
    menuItems[1].setString("New Game");
    menuItems[2].setString("Exit");

    float maxHeight = (menuFon.getGlobalBounds().height / (MENU_COUNT * 2));
    for (int8_t i = 0; i < MENU_COUNT; i++) {
        menuItems[i].setFont(font);
        menuItems[i].setCharacterSize((uint32_t)(maxHeight * 1.5));
        menuItems[i].setFillColor(sf::Color::White);
        menuItems[i].setStyle(sf::Text::Bold);
        menuItems[i].setPosition(menuFon.getGlobalBounds().left + 20, menuFon.getGlobalBounds().top + maxHeight * 1.8f * i);
    }
}

void Game::DrawField() {
    textureFon.loadFromFile("./Resurses/fon.png");
    spriteFon.setTexture(textureFon);
    spriteFon.setTextureRect(sf::IntRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT));
    font.loadFromFile("./Resurses/CyrilicOld.ttf");
    score.setFont(font);
    score.setCharacterSize(60);
    score.setFillColor(sf::Color::White);
    score.setStyle(sf::Text::Bold);
}

void Game::Start() {
    sf::Event event;
    float time;
    int8_t menuNumKeyboard = -1;
    Menu();
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        time = (float)clock.getElapsedTime().asMicroseconds();
        clock.restart();
        if ((player1.score == 7 || player2.score == 7) && !newGame) {
            active = false;
            newGame = true;
            menuNumKeyboard = -1;
            if (player1.score == 7 ) {
                score.setString("Left Player win!");
            }
            else {
                score.setString("Right Player win!");
            }
        }
        else if(player1.score != 7 && player2.score != 7) {
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
            case sf::Event::KeyPressed:
                if (!active && !pause) {
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        menuNumKeyboard++;
                        if (menuNumKeyboard >= MENU_COUNT) {
                            menuNumKeyboard = 0;
                        }
                        if (menuNumKeyboard == 0 && newGame) {
                            menuNumKeyboard++;
                        }
                        menuItems[menuNumKeyboard].setFillColor(sf::Color::Cyan);
                    }
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        menuNumKeyboard--;
                        if (menuNumKeyboard < 0 || (menuNumKeyboard == 0 && newGame)) {
                            menuNumKeyboard = MENU_COUNT - 1;
                        }
                        menuItems[menuNumKeyboard].setFillColor(sf::Color::Cyan);
                    }
                }
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
                    menuNumKeyboard = -1;
                }
            }
            else {
                int8_t menuNum = -1;
                for (int8_t i = 0; i < MENU_COUNT; i++) {
                    if (i == 0 && newGame) {
                        menuItems[i].setFillColor(sf::Color(128, 128, 128));
                        continue;
                    }
                    if (sf::IntRect(menuItems[i].getGlobalBounds()).contains(sf::Mouse::getPosition(window))) {
                        if (menuNumKeyboard != -1) {
                            menuItems[menuNumKeyboard].setFillColor(sf::Color::White);
                        }
                        menuNumKeyboard = -1;
                        menuItems[i].setFillColor(sf::Color::Cyan);
                        menuNum = i;
                    }
                    else if(menuNumKeyboard != i){
                        menuItems[i].setFillColor(sf::Color::White);
                    }
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if (menuNum == 0 || menuNumKeyboard == 0) {
                        active = true;
                    }
                    else if (menuNum == 1 || menuNumKeyboard == 1) {
                        Reset();
                        active = true;
                    }
                    else if (menuNum == 2 || menuNumKeyboard == 2) {
                        window.close();
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
                for (int8_t i = 0; i < MENU_COUNT; i++) {
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