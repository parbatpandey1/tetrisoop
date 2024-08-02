#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <ctime>
#include "Parts.hpp"

using namespace sf;

/**
 * @class Board
 * @brief Manages the Tetris game board, including the placement and movement of parts.
 */
class Board : public Drawable {
private:
    Parts parts;              ///< Manages the Tetris parts.
    int indNewPart, indColorNewPart; ///< Current part and its color index.
    Color newPartColor;       ///< Color of the new part.
    int indX, indY;           ///< Position of the part on the board.
    int timer = 0;            ///< Timer for updates.
    int limitTimer = 30;      ///< Limit for the timer.
    int board[20][10];        ///< 2D array representing the board.
    RectangleShape boardShapes[20][10]; ///< 2D array of shapes representing the visual board.

public:
    Board();                  ///< Constructor: Initializes the board and shapes.
    bool InstallPart();       ///< Installs a new part on the board.
    bool UpdateBoard();       ///< Updates the board state.
    void UpdateBoardColors(); ///< Updates the colors of the board shapes.
    void UpdateLimitTimer(int l); ///< Sets the limit timer.
    void RotatePart();        ///< Rotates the current part.
    void Right();             ///< Moves the current part right.
    void Left();              ///< Moves the current part left.
    int CheckLine();          ///< Checks for and clears completed lines.
    void ClearBoard();        ///< Clears the entire board.
    virtual void draw(RenderTarget&, RenderStates) const override; ///< Draws the board.
};

#endif // BOARD_HPP
