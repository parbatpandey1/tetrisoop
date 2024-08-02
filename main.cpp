main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "UI.hpp"
#include "Board.hpp"
#include "Sounds.hpp"
#include <fstream>
#include <thread>
#include <chrono>

using namespace sf;

void DisplayGameOver(UI& ui, Sounds& sounds, RenderWindow& window) {
    // Display "Game Over" and play sound
    ui.GameOver();
    sounds.PlayGameOver();

    // Display "Game Over" text for a few seconds
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2.0f) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear(Color(20, 20, 20));
        window.draw(ui);
        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(400, 400), "Tetris");
    window.setFramerateLimit(60);

    UI ui;
    Sounds sounds;

    bool isPlaying = false;

    while (window.isOpen()) {
        if (!isPlaying) {
            // Show the main menu and start the game if 'Play' is selected
            if (ui.ShowMainMenu(window)) {
                isPlaying = true;
                ui.ResetGameOverFlags();
            }
            else {
                window.close();
                return 0;
            }
        }
        else {
            Board board;
            int right = 0, left = 0, up = 0;
            int score = 0;
            int maxScore = 0;

            std::ifstream in("maxScore.txt");
            if (in.is_open()) {
                in >> maxScore;
                in.close();
            }
            ui.SetMaxScore(maxScore);
            ui.SetScore(score);
            bool live = true;

            board.InstallPart();
            sounds.PlayMusic();

            while (window.isOpen() && live) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        return 0;
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Up) && !up) {
                    board.RotatePart();
                    up = 1;
                }
                else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
                    up = 0;
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) board.UpdateLimitTimer(5);
                else board.UpdateLimitTimer(30);

                if (Keyboard::isKeyPressed(Keyboard::Right) && !right) {
                    board.Right();
                    right = 1;
                }
                else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
                    right = 0;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Right) && right) {
                    right++;
                    if (right == 8) right = 0;
                }

                if (Keyboard::isKeyPressed(Keyboard::Left) && !left) {
                    board.Left();
                    left = 1;
                }
                else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
                    left = 0;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left) && left) {
                    left++;
                    if (left == 8) left = 0;
                }

                if (board.UpdateBoard()) {
                    if (!board.InstallPart()) {
                        live = false;
                        board.ClearBoard();
                        sounds.PauseMusic();

                        // Display "Game Over" and play sound
                        DisplayGameOver(ui, sounds, window);

                        // Check if new high score and get player's name
                        if (score > maxScore) {
                            ui.NewScore();
                            std::string playerName = ui.GetPlayerName(window);

                            std::ofstream out("highscores.txt", std::ios::app);
                            if (out.is_open()) {
                                out << playerName << " " << score << "\n";
                                out.close();
                            }

                            maxScore = score;
                            ui.SetMaxScore(maxScore);

                            std::ofstream maxScoreFile("maxScore.txt");
                            if (maxScoreFile.is_open()) {
                                maxScoreFile << maxScore;
                                maxScoreFile.close();
                            }
                        }

                        // Ask to play again or go to main menu
                        bool playAgain = ui.AskToPlayAgain(window);
                        if (!playAgain) {
                            isPlaying = false; // Go back to the main menu
                        }
                    }
                }

                board.UpdateBoardColors();
                int newScore = board.CheckLine() * 5;
                score += newScore;
                ui.SetScore(score);
                if (newScore > 0) sounds.PlayLine();

                window.clear(Color(20, 20, 20));
                window.draw(board);
                window.draw(ui);
                window.display();
            }

            ui.ResetGameOverFlags();
        }
    }

    return 0;
}
