UI.cpp
#include "UI.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
UI::UI() {
    if (!font.loadFromFile("ka1.ttf")) {
        cout << "Error loading text" << std::endl;
    }

    tetrisText.setFont(font);
    tetrisText.setString("Tetris");
    tetrisText.setCharacterSize(50);
    tetrisText.setFillColor(Color::Yellow);
    tetrisText.setPosition(Vector2f(100, 50));

    scoreTextTitle.setFont(font);
    scoreTextTitle.setFillColor(Color::Color(20, 180, 60));
    scoreTextTitle.setPosition(Vector2f(235, 25));
    scoreTextTitle.setString("Score");

    maxScoreTextTitle.setFont(font);
    maxScoreTextTitle.setFillColor(Color::Color(60, 60, 130));
    maxScoreTextTitle.setPosition(Vector2f(210, 200));
    maxScoreTextTitle.setString("Max Score");
    maxScoreTextTitle.setCharacterSize(25);

    scoreText.setFont(font);
    scoreText.setFillColor(Color::Color(20, 180, 60));
    scoreText.setPosition(Vector2f(250, 70));

    maxScoreText.setFont(font);
    maxScoreText.setFillColor(Color::Color(60, 60, 130));
    maxScoreText.setPosition(Vector2f(240, 245));

    byText.setFont(font);
    byText.setFillColor(Color::Color(211, 211, 211));
    byText.setPosition(Vector2f(230, 340));
    byText.setString("BY PARBAT \nAnd Pratap");
    byText.setCharacterSize(18);

    gameOverText.setFont(font);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(Vector2f(115, 170));
    gameOverText.setString("Game Over !!!");
    gameOverText.setCharacterSize(22);

    newScoreText.setFont(font);
    newScoreText.setFillColor(Color::White);
    newScoreText.setPosition(Vector2f(8, 150));
    newScoreText.setString("New Score");
    newScoreText.setCharacterSize(25);

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(30);
    playText.setFillColor(Color::White);
    playText.setPosition(Vector2f(150, 150));

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(Color::White);
    exitText.setPosition(Vector2f(150, 200));

    highScoreText.setFont(font);
    highScoreText.setString("High Scores");
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(Color::White);
    highScoreText.setPosition(Vector2f(110, 250));

    gameOver = false;
    newScore = false;
    showHighScores = false;
}

void UI::SetScore(int x) {
    if (x <= 9) scoreText.setString("000" + std::to_string(x));
    else if (x <= 99) scoreText.setString("00" + std::to_string(x));
    else if (x <= 999) scoreText.setString("0" + std::to_string(x));
    else if (x <= 9999) scoreText.setString(std::to_string(x));
    else scoreText.setString("9999");
}

void UI::SetMaxScore(int x) {
    if (x <= 9) maxScoreText.setString("000" + std::to_string(x));
    else if (x <= 99) maxScoreText.setString("00" + std::to_string(x));
    else if (x <= 999) maxScoreText.setString("0" + std::to_string(x));
    else if (x <= 9999) maxScoreText.setString(std::to_string(x));
    else maxScoreText.setString("9999");
}

void UI::GameOver() {
    gameOver = true;
    clock.restart();
}

void UI::NewScore() {
    newScore = true;
}

void UI::ResetGameOverFlags() {
    gameOver = false;
    newScore = false;
}

bool UI::AskToPlayAgain(RenderWindow& window) {
    Text prompt("Press Y To Play Again\n\nPress M to go Main Menu", font, 20);
    prompt.setFillColor(Color::Color(0, 255, 255));
    prompt.setPosition(20, 80);
    bool playAgain = false;
    bool promptDisplayed = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == Event::KeyPressed && promptDisplayed) {
                if (event.key.code == Keyboard::Y) {
                    playAgain = true;
                    return playAgain;
                }
                else if (event.key.code == Keyboard::M) {
                    playAgain = false;
                    return playAgain;
                }
            }
        }
        window.clear(Color(20, 20, 20));
        if (clock.getElapsedTime().asSeconds() >= 2.5) {
            window.draw(prompt);
            promptDisplayed = true;
        }
        else {
            window.draw(gameOverText);
        }
        window.display();
    }
    return false;
}

bool UI::ShowMainMenu(RenderWindow& window) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (playText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        return true;  // Start the game
                    }
                    if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                        return false;  // Exit the game
                    }
                    if (highScoreText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        ShowHighScores(window);
                    }
                }
            }
        }
        window.clear(Color(20, 20, 20));
        window.draw(tetrisText);
        window.draw(playText);
        window.draw(exitText);
        window.draw(highScoreText);
        window.draw(byText);
        window.display();
    }
    return false;
}

void UI::ShowHighScores(RenderWindow& window) {
    std::vector<std::pair<std::string, int>> highScores;
    std::ifstream file("highscores.txt");
    std::string name;
    int score;
    while (file >> name >> score) {
        highScores.push_back({ name, score });
    }
    file.close();

    std::sort(highScores.begin(), highScores.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                return;
            }
        }

        window.clear(Color(20, 20, 20));
        Text title("High Scores", font, 30);
        title.setPosition(55, 20);
        window.draw(title);

        for (int i = 0; i < std::min(5, (int)highScores.size()); i++) {
            Text scoreText(highScores[i].first + ": " + std::to_string(highScores[i].second), font, 30);
            scoreText.setPosition(50, 100 + i * 50);
            window.draw(scoreText);
        }

        Text backText("Press ESC to go back", font, 20);
        backText.setPosition(90, 350);
        window.draw(backText);

        window.display();
    }
}

std::string UI::GetPlayerName(RenderWindow& window) {
    std::string playerName;
    Text namePrompt("NEW HIGH SCORE!!\n\nEnter Your Name:", font, 25);
    namePrompt.setPosition(50, 40);
    Text currentName("", font, 25);
    currentName.setPosition(50, 180);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return playerName;
            }
            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b' && !playerName.empty()) {
                    playerName.pop_back();
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    return playerName;
                }
                else if (event.text.unicode < 128 && playerName.length() < 15) {
                    playerName += static_cast<char>(event.text.unicode);
                }
                currentName.setString(playerName);
            }
        }

        window.clear(Color(20, 20, 20));
        window.draw(namePrompt);
        window.draw(currentName);
        window.display();
    }
    return playerName;
}

void UI::draw(RenderTarget& rt, RenderStates rs) const {
    if (gameOver) {
        rt.draw(gameOverText, rs);
        return; // Stop drawing other elements when game is over
    }

    // Draw only if not showing high scores
    if (!showHighScores) {
        rt.draw(scoreTextTitle, rs);
        rt.draw(scoreText, rs);
        rt.draw(maxScoreTextTitle, rs);
        rt.draw(maxScoreText, rs);
        rt.draw(byText, rs);
    }
}
