#include <iostream>
#include <cstdlib>
#include <ctime>

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(char board[][3]) {
    std::cout << "\n\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "\t\t\t " << board[i][0] << "  |  " << board[i][1] << "  |  " << board[i][2] << "  \n";
        if (i != 2) {
            std::cout << "\t\t\t ----|------|----  \n";
        }
    }
}

void showInstructions() {
    std::cout << "\t\t\t TIC-TAC-TOE\n\n";
    std::cout << "Choose a cell numbered from 1 to 9 as below and play \n\n";
    std::cout << "\t\t\t  1  |   2  |  3   \n";
    std::cout << "\t\t\t ----|------|----  \n";
    std::cout << "\t\t\t  4  |   5  |   6  \n";
    std::cout << "\t\t\t ----|------|----  \n";
    std::cout << "\t\t\t  7  |   8  |   9  \n\n";
    std::cout << "-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n";
}

void initialize(char board[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

bool isGameover(char board[][3]) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return true;
    }
    return false;
}

bool isBoardFull(char board[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void declareWinner(char winner) {
    if (winner == COMPUTERMOVE) {
        std::cout << "COMPUTER has won\n";
    } else if (winner == HUMANMOVE) {
        std::cout << "HUMAN has won\n";
    } else {
        std::cout << "It's a draw\n";
    }
}

bool isValidMove(int move, char board[][3]) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    return board[row][col] == ' ';
}

bool canWinNextMove(char board[][3], char player) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == ' ') {
            return true;
        }
        if (board[i][0] == player && board[i][2] == player && board[i][1] == ' ') {
            return true;
        }
        if (board[i][1] == player && board[i][2] == player && board[i][0] == ' ') {
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == ' ') {
            return true;
        }
        if (board[0][i] == player && board[2][i] == player && board[1][i] == ' ') {
            return true;
        }
        if (board[1][i] == player && board[2][i] == player && board[0][i] == ' ') {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == ' ') {
        return true;
    }
    if (board[0][0] == player && board[2][2] == player && board[1][1] == ' ') {
        return true;
    }
    if (board[1][1] == player && board[2][2] == player && board[0][0] == ' ') {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == ' ') {
        return true;
    }
    if (board[0][2] == player && board[2][0] == player && board[1][1] == ' ') {
        return true;
    }
    if (board[1][1] == player && board[2][0] == player && board[0][2] == ' ') {
        return true;
    }
    return false;
}

bool needsToBlock(char board[][3], char opponent) {
    return canWinNextMove(board, opponent);
}

int findWinningMove(char board[][3], char player) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == ' ') {
            return 3 * i + 3;
        }
        if (board[i][0] == player && board[i][2] == player && board[i][1] == ' ') {
            return 3 * i + 2;
        }
        if (board[i][1] == player && board[i][2] == player && board[i][0] == ' ') {
            return 3 * i + 1;
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == ' ') {
            return 3 * 2 + i + 1;
        }
        if (board[0][i] == player && board[2][i] == player && board[1][i] == ' ') {
            return 3 * 1 + i + 1;
        }
        if (board[1][i] == player && board[2][i] == player && board[0][i] == ' ') {
            return 3 * 0 + i + 1;
        }
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == ' ') {
        return 9;
    }
    if (board[0][0] == player && board[2][2] == player && board[1][1] == ' ') {
        return 5;
    }
    if (board[1][1] == player && board[2][2] == player && board[0][0] == ' ') {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == ' ') {
        return 7;
    }
    if (board[0][2] == player && board[2][0] == player && board[1][1] == ' ') {
        return 5;
    }
    if (board[1][1] == player && board[2][0] == player && board[0][2] == ' ') {
        return 3;
    }
    return -1; // No winning move found
}

void playTicTacToe() {
    char board[3][3];
    char currentPlayer = HUMANMOVE;
    char winner = ' ';
    int move;

    std::srand(std::time(nullptr));

    initialize(board);
    showInstructions();

    while (!isGameover(board) && !isBoardFull(board)) {
        if (currentPlayer == HUMANMOVE) {
            std::cout << "Enter your move (1-9): ";
            std::cin >> move;
            if (!isValidMove(move, board)) {
                std::cout << "Invalid move. Please try again.\n";
                continue;
            }
        } else {
            // AI computer player's turn
            if (canWinNextMove(board, COMPUTERMOVE)) {
                move = findWinningMove(board, COMPUTERMOVE);
            } else if (needsToBlock(board, HUMANMOVE)) {
                move = findWinningMove(board, HUMANMOVE);
            } else {
                do {
                    move = std::rand() % 9 + 1;
                } while (!isValidMove(move, board));
            }
        }

        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
        board[row][col] = currentPlayer;
        showBoard(board);

        if (isGameover(board)) {
            winner = currentPlayer;
            break;
        }

        currentPlayer = (currentPlayer == HUMANMOVE) ? COMPUTERMOVE : HUMANMOVE;
    }

    declareWinner(winner);
}

int main() {
    playTicTacToe();
    return 0;
}
