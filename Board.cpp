#include "Board.hpp"

// Constructor: Initializes the board and the shapes with default values
Board::Board() {
    memset(board, 0, sizeof(board)); // Initialize the board to 0
    
    // Initialize each block on the board with default RectangleShape properties
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            boardShapes[i][j] = RectangleShape(Vector2f(20, 20));
            boardShapes[i][j].setPosition(j * 20, i * 20);
            boardShapes[i][j].setFillColor(Color(50, 50, 50));
            boardShapes[i][j].setOutlineThickness(2);
            boardShapes[i][j].setOutlineColor(Color(0, 0, 0));
        }
    }
}

// Install a new part on the board
bool Board::InstallPart() {
    srand(time(NULL));
    indNewPart = rand() % 7; // Randomly choose a new part
    
    // Get the shape of the new part
    vector<vector<bool>> part = parts.ConsultPart(indNewPart);
    int sz = (int)part.size();
    
    indY = 0;
    indX = 5 - sz / 2;
    
    // Check if the part can be placed on the board
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            if(part[i][j]) {
                if(board[i][j + indX] > 0) return false;
                board[i][j + indX] = -1;
            }
        }
    }
    
    int color = 1 + rand() % 7;
    indColorNewPart = color;
    
    // Set the color of the new part
    switch(color) {
        case 1: newPartColor = Color(255, 166, 0); break;
        case 2: newPartColor = Color(245, 152, 245); break;
        case 3: newPartColor = Color(51, 204, 153); break;
        case 4: newPartColor = Color(255, 110, 110); break;
        case 5: newPartColor = Color(255, 204, 77); break;
        case 6: newPartColor = Color(166, 166, 255); break;
        case 7: newPartColor = Color(138, 194, 247); break;
    }
    return true;
}

// Update the board state and check for part limits
bool Board::UpdateBoard() {
    bool limit = 0;
    int aux;
    
    if(timer >= limitTimer) {
        aux = 0;
        
        // Check if the part can move down
        for(int i = 18; i >= 0; i--) {
            for(int j = 0; j < 10; j++) {
                if(board[i][j] == -1) {
                    if(board[i + 1][j] <= 0) aux++;
                }
            }
        }
        
        // Move the part down if possible
        if(aux == 4) {
            indY++;
            for(int i = 18; i >= 0; i--) {
                for(int j = 0; j < 10; j++) {
                    if(board[i][j] == -1) {
                        board[i][j] = 0;
                        board[i + 1][j] = -1;
                    }
                }
            }
        } else {
            // Fix the part on the board if it can't move down
            for(int i = 19; i >= 0; i--) {
                for(int j = 0; j < 10; j++) {
                    if(board[i][j] == -1) board[i][j] = indColorNewPart;
                }
            }
            limit = 1;
        }
        
        timer = 0;
    }
    
    timer++;
    return limit;
}

// Update the colors of the board shapes based on the board state
void Board::UpdateBoardColors() {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            switch(board[i][j]) {
                case 0: boardShapes[i][j].setFillColor(Color(50, 50, 50)); break;
                case 1: boardShapes[i][j].setFillColor(Color(255, 166, 0)); break;
                case 2: boardShapes[i][j].setFillColor(Color(245, 152, 245)); break;
                case 3: boardShapes[i][j].setFillColor(Color(51, 204, 153)); break;
                case 4: boardShapes[i][j].setFillColor(Color(255, 110, 110)); break;
                case 5: boardShapes[i][j].setFillColor(Color(255, 204, 77)); break;
                case 6: boardShapes[i][j].setFillColor(Color(166, 166, 255)); break;
                case 7: boardShapes[i][j].setFillColor(Color(138, 194, 247)); break;
                default:
                    boardShapes[i][j].setFillColor(newPartColor); // New part color
                    break;
            }
        }
    }
}

// Set the limit timer for the board update
void Board::UpdateLimitTimer(int l) {
    limitTimer = l;
}

// Rotate the current part on the board
void Board::RotatePart() {
    parts.RotatePart(indNewPart);
    vector<vector<bool>> part = parts.ConsultPart(indNewPart);
    int sz = (int)part.size();
    
    // Check if the part can be rotated
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            if(part[i][j]) {
                if(indY + i < 0 || indY + i >= 20 || indX + j < 0 || indX + j >= 10 || board[indY + i][indX + j] > 0) {
                    parts.DerotatePart(indNewPart);
                    return;
                }
            }
        }
    }
    
    // Clear the current part position
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            if(board[i][j] == -1) board[i][j] = 0;
        }
    }
    
    // Set the rotated part position
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            if(part[i][j]) {
                board[i + indY][j + indX] = -1;
            }
        }
    }
}

// Move the current part to the right
void Board::Right() {
    int aux = 0;
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 9; j++) {
            if(board[i][j] == -1) {
                if(board[i][j + 1] <= 0) {
                    aux++;
                }
            }
        }
    }
    
    // Move the part to the right if possible
    if(aux == 4) {
        indX++;
        for(int i = 0; i < 20; i++) {
            for(int j = 9; j >= 0; j--) {
                if(board[i][j] == -1) board[i][j] = 0, board[i][j + 1] = -1;
            }
        }
    }
}

// Move the current part to the left
void Board::Left() {
    int aux = 0;
    for(int i = 0; i < 20; i++) {
        for(int j = 1; j < 10; j++) {
            if(board[i][j] == -1) {
                if(board[i][j - 1] <= 0) {
                    aux++;
                }
            }
        }
    }
    
    // Move the part to the left if possible
    if(aux == 4) {
        indX--;
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                if(board[i][j] == -1) board[i][j] = 0, board[i][j - 1] = -1;
            }
        }
    }
}

// Check for and clear any completed lines on the board
int Board::CheckLine() {
    int aux = 0, lines = 0;
    
    for(int i = 19; i >= 0; i--) {
        aux = 0;
        for(int j = 0; j < 10; j++) {
            if(board[i][j] > 0) aux++;
            if(lines > 0) board[i + lines][j] = board[i][j], board[i][j] = 0;
        }
        if(aux == 10) {
            for(int j = 0; j < 10; j++) board[i][j] = 0;
            lines++;
        }
    }
    return lines;
}

// Draw the board on the provided render window
void Board::Draw(RenderWindow &window) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            window.draw(boardShapes[i][j]);
        }
    }
}
