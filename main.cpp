#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "UI.hpp"
#include "Sounds.hpp"
#include <fstream>
using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(400, 400), "Tetris");  // Increased window size
    window.setFramerateLimit(60);

    UI ui;
    Sounds sounds;

    // Show main menu and wait for user choice
    bool startGame = ui.ShowMainMenu(window);

    while (window.isOpen() && startGame) {
        Board board;
        int right = 0, left = 0, up = 0;
        int score = 0;
        int maxScore = 0;
        ifstream in("maxScore.txt");
        in >> maxScore;
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
                }
            }
            if (live) {
                if (Keyboard::isKeyPressed(Keyboard::Up) && !up) board.RotatePart(), up = 1;
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
                        if (score > maxScore) {
                            ui.NewScore();
                            ofstream out("maxScore.txt");
                            out << score;
                        }
                        ui.GameOver();
                        sounds.PlayGameOver();
                    }
                }
                board.UpdateBoardColors();
                int newScore = board.CheckLine() * 5;
                score += newScore;

                if (newScore > 0) sounds.PlayLine();
            }
            window.clear(Color(20, 20, 20));
            window.draw(board);
            window.draw(ui);
            window.display();
        }

        // Call ResetGameOverFlags before starting a new game
        ui.ResetGameOverFlags();

        startGame = ui.AskToPlayAgain(window);
        score = 0;
        ui.SetScore(score);
        live = true;
    }

    return 0;
}
