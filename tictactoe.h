#include "iostream"

class TicTacToe {
public:
    void NameCheck();
    void Game();

private:
    bool     xWin = false;
    bool     oWin = false;
    bool game_end = false;

    int row = 0;
    int col = 0;
    int squareIdx = 0;
    int count = 0;

    std::string player1 = "";
    std::string player2 = "";
    std::string box[3][3] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

    bool  RowFull(std::string box[3][3]);
    bool  ColFull(std::string box[3][3]);
    bool DiagFull(std::string box[3][3]);
    
    bool InputCheck();
    void xCheck();
    void oCheck();
    bool FullCheck();
};

void TicTacToeBox(std::string box[3][3], int row, int col) { // Prints tic tac toe grid
    int i = 0;
    while (i < 3) {
        for (int j = 0; j < 3; j++) {
            std::cout << " " << box[i][j];
            if (j < 2) std::cout << " |";
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "-----------" << std::endl;
        i++;
    }
}

void TicTacToe::NameCheck() {
    std::cout << "\nTicTacToe Game!\n\n";
    std::cout << "Enter name of Player 1: ";
    std::cin >> player1;
    std::cout << "Enter name of Player 2: ";
    std::cin >> player2;

    if (player1 == player2) {
        do {
            std::cout << "Names must not be the same!\n";
            std::cout << "Re-enter name of Player 2: ";
            std::cin >> player2;

        }
        while (player1 == player2);
    }
    std::cout << player1 << " will go first!\n";
    TicTacToeBox (box, row, col);
}

bool TicTacToe::InputCheck() {
    int arrayIdx[3][3] = {0};
    int idx = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arrayIdx[i][j] = idx;
            idx++;
        }
    }
    do {
        if (count % 2) std::cout << player2 << ", Enter your square number for 'o': ";
        else std::cout << player1 << ", Enter your square number for 'x': ";
        std::cin >> squareIdx;
        
        row = (squareIdx - 1) / 3;
        col = (squareIdx - 1) % 3;
        if (squareIdx < 1 || squareIdx > 9 || box[row][col] == "x" || box[row][col] == "o") std::cout << "Invalid input!\n"; 
        
    } 
    while (squareIdx < 1 || squareIdx > 9 || box[row][col] == "x" || box[row][col] == "o");
    return true;
}

void TicTacToe::xCheck() {
    if (InputCheck()) box[row][col] = "x";
    TicTacToeBox(box, row, col);
}

void TicTacToe::oCheck() {
    if (InputCheck()) box[row][col] = "o";
    TicTacToeBox (box, row, col);
}

bool TicTacToe::FullCheck() {
    if (RowFull(box) == true || ColFull(box) == true || DiagFull(box) == true) { // Checks if x fills any rows, cols, or diags
            if (xWin == true) std::cout << player1 << " wins!" << std::endl;
            else std::cout << player2 << " wins!" << std::endl;
            game_end = true;
            return true;
    }
    else return false;
}

void TicTacToe::Game() {
    while (!game_end) {

        xCheck();
        count++;
        if (FullCheck()) break;

        if (count >= 9 && !xWin && !oWin) { // Check for tie game
            std::cout << "Tie Game!\n";
            game_end = true;
            break;
        }
            
        oCheck();
        if (FullCheck()) break;
        count++;
    }
}

bool TicTacToe::RowFull(std::string box[3][3]) { // Checks if any row is full
    int sumX = 0;
    int sumO = 0;

    for (int i = 0; i < 3; i++) {
        sumX = 0;
        sumO = 0;
        for (int j = 0; j < 3; j++) {

            if (box[i][j] == "x") sumX++;
            else if (box[i][j] == "o") sumO++;

            if (sumX == 3) {
                xWin = true;
                return true;
            }
            else if (sumO == 3) {
                oWin = true;
                return true;
            }
        }
    }
    return false;
}

bool TicTacToe::ColFull(std::string box[3][3]) { // Checks if any column is full
    int sumX = 0;
    int sumO = 0;
    
    for (int j = 0; j < 3; j++) {
        sumX = 0;
        sumO = 0;
        for (int i = 0; i < 3; i++) {
            if (box[i][j] == "x") sumX++;
            else if (box[i][j] == "o") sumO++;

            if (sumX == 3) {
                xWin = true;
                return true;
            }
            else if (sumO == 3) {
                oWin = true;
                return true;
            }
        }
    }
    return false;
}

bool TicTacToe::DiagFull(std::string box[3][3]) {
    int sumX = 0;
    int sumO = 0;

    for (int k = 0; k < 3; k++) { // diagonal from left to right [0,0], [1,1], [2,2]
        if (box[k][k] == "x") sumX++;
        else if (box[k][k] == "o") sumO++;

        if (sumX == 3) {
            xWin = true;
            return true;
        }
        else if (sumO == 3) {
            oWin = true;
            return true;
        }
    }
    sumX = 0;
    sumO = 0;
    int j = 2;

    for (int i = 0; i < 3; i++) { // diagonal from right to left [0,2], [1,1], [2,0]
        if (box[i][j] == "x") sumX++;
        else if (box[i][j] == "o") sumO++;

        if (sumX == 3) {
            xWin = true;
            return true;
        }
        else if (sumO == 3) {
            oWin = true;
            return true;
        }
        j--;
    }
    return false;
}