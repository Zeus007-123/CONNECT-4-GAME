#include <iostream>
#include <vector>

using namespace std;

class Connect4Game {
private:
    const int rows = 6;
    const int columns = 7;
    vector<vector<char>> board;
    char currentPlayer;
    bool gameWon;

public:
    Connect4Game() : currentPlayer('R'), gameWon(false) {
        // Initialize the game board
        board.resize(rows, vector<char>(columns, ' '));
    }

    // For Displaying the Game Board
    void displayBoard() const {
      cout << "-----------------------------\n";
      for (int i = 0; i < rows; ++i) {
        cout << "| ";
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == 'R') {
                cout << "\033[1;31mR \033[0m| ";
            } else if (board[i][j] == 'B') {
                cout << "\033[1;34mB \033[0m| ";
            } else {
                cout << board[i][j] << " | ";
            }
        }
        cout << "\n-----------------------------\n";
      }
    }

    // For Switching Players
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'R') ? 'B' : 'R';
    }

    // For Checking if the Move is Valid or Not
    bool isValidMove(int column) const {
        return column >= 0 && column < columns && board[0][column] == ' ';
    }

    // For Making the move based Player Input
    void makeMove(int column) {
        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][column] == ' ') {
                board[i][column] = currentPlayer;
                break;
            }
        }
    }

    // For Checking if the Player has Won or not
    bool checkWin() {
        // Check horizontally, vertically, and diagonally for a win
        return checkHorizontal() || checkVertical() || checkDiagonal();
    }

    // HORIZONTAL CHECK
    bool checkHorizontal() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j <= columns - 4; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i][j + 1] == currentPlayer &&
                    board[i][j + 2] == currentPlayer &&
                    board[i][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    // VERTICAL CHECK
    bool checkVertical() const {
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j] == currentPlayer &&
                    board[i + 2][j] == currentPlayer &&
                    board[i + 3][j] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    // DIAGONAL CHECK
    bool checkDiagonal() const {
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 0; j <= columns - 4; ++j) {
                // Check diagonally (from top-left to bottom-right)
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j + 1] == currentPlayer &&
                    board[i + 2][j + 2] == currentPlayer &&
                    board[i + 3][j + 3] == currentPlayer) {
                    return true;
                }
                // Check diagonally (from top-right to bottom-left)
                if (board[i][j + 3] == currentPlayer &&
                    board[i + 1][j + 2] == currentPlayer &&
                    board[i + 2][j + 1] == currentPlayer &&
                    board[i + 3][j] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    // For Checking if the Game is Tied or not
    bool isBoardFull() const {
        for (int i = 0; i < columns; ++i) {
            if (board[0][i] == ' ') {
                return false;
            }
        }
        return true;
    }

    // For playing again
    bool playAgain() const {
        char choice;
        cout << "Do you want to play again? (Press 'S' to start again, any other key to exit): ";
        cin >> choice;
        return (choice == 'S' || choice == 's');
    }

    void playGame() {
        cout << "                ---------------------------------             \n";
        cout << "                |                               |             \n";
        cout << "                |     WELCOME TO CONNECT 4!     |             \n";
        cout << "                |                               |             \n";
        cout << "                ---------------------------------             \n";
        cout << endl; 
        cout << endl;
        cout << "                ---------------------------------             \n";
        cout << "                |                               |             \n";
        cout << "                |             RULES             |             \n";
        cout << "                |                               |             \n";
        cout << "                ---------------------------------             \n";
        cout << endl; 
        cout << endl;
        cout << " 1. Two-playe Red(R) & Blue(B) game." << endl;
        cout << " 2. Board Size is 6 rows & 7 columns." << endl;
        cout << " 3. A player wins, if he/she is able to connect 4 letters horizontally, vertically or diagonally. " << endl;
        cout << " 4. Game Draw when matrix is fully filled." << endl;
        cout << endl;
        cout << endl;
        cout << "                ---------------------------------             \n";
        cout << "                |                               |             \n";
        cout << "                |          HOW TO PLAY          |             \n";
        cout << "                |                               |             \n";
        cout << "                ---------------------------------             \n";
        cout << endl; 
        cout << endl;
        cout << " 1. Game always starts with player- 1 i.e. Red(R)." << endl;
        cout << " 2. In each step choose the column number in which you want to drop the letter." << endl;
        cout << " 3. Rows will be filled from bottom to top in any column. " << endl;
        cout << endl;
        cout << "                ---------------------------------             \n";
        cout << "                |                               |             \n";
        cout << "                |          GAME STARTS          |             \n";
        cout << "                |                               |             \n";
        cout << "                ---------------------------------             \n";
        cout << endl;
      
        while (!gameWon && !isBoardFull()) {
            displayBoard();
            cout << endl;
            cout << "Player " << currentPlayer << ", enter the column number (0-6) : ";
            int column;
            cin >> column;
            cout << endl;

            if (isValidMove(column)) {
                makeMove(column);
                gameWon = checkWin();
                switchPlayer();
            } else {
                cout << "Invalid move. Please try again.\n";
            }
        }

        displayBoard();
        cout << endl;
        if (gameWon) {
            cout << "Player " << ((currentPlayer == 'R') ? 'B' : 'R') << " wins !\n";
        } else {
            cout << "It's a draw !\n";
        }
        cout << endl;
        if (playAgain()) {
            // Reset the game and start again
            gameWon = false;
            currentPlayer = 'R';
            board = vector<vector<char>>(rows, vector<char>(columns, ' '));
            playGame();
        } else {
        cout << "                ---------------------------------             \n";
        cout << "                |          GAME ENDS !!!        |             \n";
        cout << "                |          THANK YOU !!!        |             \n";
        cout << "                |       SEE YOU NEXT TIME !!!   |             \n";
        cout << "                ---------------------------------             \n";
        cout << endl;
    }
  }
};

int main() {
    Connect4Game game;
    game.playGame();

    return 0;
}
