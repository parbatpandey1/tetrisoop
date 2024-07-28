#include "UI.hpp"
#include <iostream>
using namespace std;

UI::UI() {
    if (!font.loadFromFile("ka1.ttf")) {
        cout << "Error al cargar fuente de texto" << endl;
    }

    // Initialize "Tetris" text
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

    // New elements for main menu
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
}

void UI::SetScore(int x) {
    if (x <= 9) scoreText.setString("000" + to_string(x));
    else if (x <= 99) scoreText.setString("00" + to_string(x));
    else if (x <= 999) scoreText.setString("000" + to_string(x));
    else if (x <= 9999) scoreText.setString(to_string(x));
    else scoreText.setString("9999");
}

void UI::SetMaxScore(int x) {
    if (x <= 9) maxScoreText.setString("000" + to_string(x));
    else if (x <= 99) maxScoreText.setString("00" + to_string(x));
    else if (x <= 999) maxScoreText.setString("000" + to_string(x));
    else if (x <= 9999) maxScoreText.setString(to_string(x));
    else maxScoreText.setString("9999");
}

void UI::GameOver() {
    gameOver = true;
    clock.restart();  // Restart the clock when game is over
}

void UI::NewScore() {
    newScore = true;
}

void UI::ResetGameOverFlags() {
    gameOver = false;
    newScore = false;
}

void UI::draw(RenderTarget& rt, RenderStates rs) const {
    rt.draw(scoreTextTitle, rs);
    rt.draw(scoreText, rs);
    rt.draw(maxScoreTextTitle, rs);
    rt.draw(maxScoreText, rs);
    rt.draw(byText, rs);
    if (gameOver) {
        rt.draw(gameOverText, rs);
    }
    if (newScore) rt.draw(newScoreText, rs);
}

bool UI::AskToPlayAgain(RenderWindow& window) {
    Text prompt("Play again? (Y/N)", font, 20);
    prompt.setFillColor(Color::Color(0, 255, 255));
    prompt.setPosition(100, 180);
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
                }
                else if (event.key.code == Keyboard::N) {
                    playAgain = false;
                }
                return playAgain;
            }
        }
        window.clear(Color(20, 20, 20));
        if (clock.getElapsedTime().asSeconds() >= 2) {
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
                }
            }
        }

        window.clear(Color(20, 20, 20));
        window.draw(tetrisText);  // Draw the "Tetris" text
        window.draw(playText);
        window.draw(exitText);
        window.draw(byText);  // Display the "BY PARBAT And Pratap" text
        window.display();
    }
    return false;
}
