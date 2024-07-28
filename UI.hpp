#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class UI : public Drawable {
public:
    UI();
    void SetScore(int x);
    void SetMaxScore(int x);
    void GameOver();
    void NewScore();
    void ResetGameOverFlags(); // Method declaration for resetting flags
    bool AskToPlayAgain(RenderWindow& window);
    bool ShowMainMenu(RenderWindow& window);

private:
    Font font;
    Text scoreTextTitle;
    Text maxScoreTextTitle;
    Text scoreText;
    Text maxScoreText;
    Text byText;
    Text gameOverText;
    Text newScoreText;
    Text playText;
    Text exitText;
    Text tetrisText; // New text for "Tetris"

    bool gameOver = false;
    bool newScore = false;
    Clock clock;

    virtual void draw(RenderTarget& rt, RenderStates rs) const override;
};

#endif // UI_HPP
