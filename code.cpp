#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

// Function to print the Tic Tac Toe board
void printBoard(const vector<char> &board) {
    cout << "*************       *************\n";
    for (int i = 0; i < 3; ++i) {
        cout << "* ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " * ";
        }
        cout << "      * " << i * 3 + 1 << " * " << i * 3 + 2 << " * " << i * 3 + 3 << " *\n";
        cout << "*************       *************\n";
    }
}

// Function to check if the game is over (win/draw)
bool gameOver(const vector<char> &board, char symbol) {
    // Check rows, columns, and diagonals for a win
    return ((board[0] == symbol && board[1] == symbol && board[2] == symbol) ||
            (board[3] == symbol && board[4] == symbol && board[5] == symbol) ||
            (board[6] == symbol && board[7] == symbol && board[8] == symbol) ||
            (board[0] == symbol && board[3] == symbol && board[6] == symbol) ||
            (board[1] == symbol && board[4] == symbol && board[7] == symbol) ||
            (board[2] == symbol && board[5] == symbol && board[8] == symbol) ||
            (board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
            (board[2] == symbol && board[4] == symbol && board[6] == symbol));
}

// Function to check if the board is full
bool boardFull(const vector<char> &board) {
    for (char cell : board) {
        if (cell == EMPTY)
            return false;
    }
    return true;
}

// Function to evaluate the score of the board for minimax algorithm
int evaluate(const vector<char> &board) {
    if (gameOver(board, COMPUTER)) return 10;
    if (gameOver(board, HUMAN)) return -10;
    return 0;
}

// Minimax algorithm implementation
int minimax(vector<char> &board, int depth, bool isMaximizer) {
    int score = evaluate(board);
    if (score != 0) return score;

    if (boardFull(board)) return 0;

    if (isMaximizer) {
        int bestScore = -1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == EMPTY) {
                board[i] = COMPUTER;
                bestScore = max(bestScore, minimax(board, depth + 1, !isMaximizer));
                board[i] = EMPTY;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == EMPTY) {
                board[i] = HUMAN;
                bestScore = min(bestScore, minimax(board, depth + 1, !isMaximizer));
                board[i] = EMPTY;
            }
        }
        return bestScore;
    }
}

// Function to let the computer make a move using minimax algorithm
void computerMove(vector<char> &board) {
    int bestMove = -1;
    int bestScore = -1000;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == EMPTY) {
            board[i] = COMPUTER;
            int score = minimax(board, 0, false);
            board[i] = EMPTY;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    board[bestMove] = COMPUTER;
}

int main() {
    vector<char> board(9, EMPTY); // Initialize the empty board
    char choice;
    cout << "Welcome to Tic Tac Toe!\n";
    do {
        cout << "Menu:\n";
        cout << "1. Play against a friend\n";
        cout << "2. Play against computer\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': {
                cout << "Player 1: X, Player 2: O\n";
                char currentPlayer = 'X';
                while (!gameOver(board, currentPlayer) && !boardFull(board)) {
                    printBoard(board);
                    cout << "Player " << currentPlayer << "'s turn.\n";
                    int move;
                    cout << "Enter your move (1-9): ";
                    cin >> move;
                    if (board[move - 1] == EMPTY) {
                        board[move - 1] = currentPlayer;
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    } else {
                        cout << "Invalid move! Try again.\n";
                    }
                }
                printBoard(board);
                if (gameOver(board, 'X')) {
                    cout << "Player X wins!\n";
                } else if (gameOver(board, 'O')) {
                    cout << "Player O wins!\n";
                } else {
                    cout << "It's a draw!\n";
                }
                break;
            }
            case '2': {
                cout << "You: X, Computer: O\n";
                char currentPlayer = 'X';
                while (!gameOver(board, currentPlayer) && !boardFull(board)) {
                    printBoard(board);
                    if (currentPlayer == 'X') {
                        cout << "Your turn.\n";
                        int move;
                        cout << "Enter your move (1-9): ";
                        cin >> move;
                        if (board[move - 1] == EMPTY) {
                            board[move - 1] = currentPlayer;
                            currentPlayer = 'O';
                        } else {
                            cout << "Invalid move! Try again.\n";
                        }
                    } else {
                        cout << "Computer's turn.\n";
                        computerMove(board);
                        currentPlayer = 'X';
                    }
                    
                    // Check if the game is over after each move
                    if (gameOver(board, 'X') || gameOver(board, 'O') || boardFull(board)) {
                        break; // Exit the loop if the game is over
                    }
                }
                printBoard(board);
                if (gameOver(board, 'X')) {
                    cout << "You win!\n";
                } else if (gameOver(board, 'O')) {
                    cout << "Computer wins!\n";
                } else {
                    cout << "It's a draw!\n";
                }
                break;
            }
            case '3':
                cout << "Thanks for playing!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        // Reset the board for a new game
        board = vector<char>(9, EMPTY);
    } while (choice != '3');

    return 0;
}
