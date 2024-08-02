UI.hpp
#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class UI : public Drawable {
private:
    Font font;
    Text tetrisText, scoreTextTitle, maxScoreTextTitle, scoreText, maxScoreText, byText, gameOverText, newScoreText;
    Text playText, exitText, highScoreText;
    bool gameOver, newScore, showHighScores;
    Clock clock;

    virtual void draw(RenderTarget& rt, RenderStates rs) const;

public:
    UI();
    void SetScore(int x);
    void SetMaxScore(int x);
    void GameOver();
    void NewScore();
    void ResetGameOverFlags();
    bool AskToPlayAgain(RenderWindow& window);
    bool ShowMainMenu(RenderWindow& window);
    void ShowHighScores(RenderWindow& window);
    std::string GetPlayerName(RenderWindow& window);
};

#endif // UI_HPP
