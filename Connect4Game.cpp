#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Board {
protected:
    static const int rows = 6;
    static const int columns = 7;
    static const int connectWin = 4;
    vector<vector<char>> board;

public:
    Board() {
        // Initialize the game board
        board.resize(rows, vector<char>(columns, ' '));
    }

    virtual ~Board() {}

    // Displaying the Game Board
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

    // Check if the board is full
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

    // Check if a move is valid
    virtual bool isValidMove(int column) const = 0;

    // Make a move
    virtual void makeMove(int column, char currentPlayer) = 0;

    // Check for a win
    virtual bool checkWin(int row, int column, char currentPlayer) const = 0;
};

class Connect4Game : public Board {
private:
    char currentPlayer;
    bool gameWon;
    // Clear the input buffer
    void clearInputBuffer() const {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore last input
    }

public:
    Connect4Game() : currentPlayer('R'), gameWon(false) {}

    // Switch Players
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'R') ? 'B' : 'R';
    }

    // Input validation for a valid column number
    bool isValidMove(int column) const override {
        return column >= 0 && column < columns && board[0][column] == ' ';
    }

    // Make a move
    void makeMove(int column, char currentPlayer) override {
        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][column] == ' ') {
                board[i][column] = currentPlayer;
                break;
            }
        }
    }

    // Check for a win
    bool checkWin(int row, int column, char currentPlayer) const override {
        // Check horizontally, vertically, and diagonally for a win
        return checkHorizontal(row, column) || checkVertical(row, column) || checkDiagonal(row, column);
    }

    // Check for a win horizontally
    bool checkHorizontal(int row, int column) const {
        for (int j = 0; j <= columns - connectWin; ++j) {
            if (board[row][j] == currentPlayer &&
                board[row][j + 1] == currentPlayer &&
                board[row][j + 2] == currentPlayer &&
                board[row][j + 3] == currentPlayer) {
                return true;
            }
        }
        return false;
    }

    // Check for a win vertically
    bool checkVertical(int row, int column) const {
        for (int i = 0; i <= rows - connectWin; ++i) {
            if (board[i][column] == currentPlayer &&
                board[i + 1][column] == currentPlayer &&
                board[i + 2][column] == currentPlayer &&
                board[i + 3][column] == currentPlayer) {
                return true;
            }
        }
        return false;
    }

    // Check for a win diagonally
    bool checkDiagonal(int row, int column) const {
        for (int i = 0; i <= rows - connectWin; ++i) {
            for (int j = 0; j <= columns - connectWin; ++j) {
                // Check diagonally (from top-left to bottom-right)
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j + 1] == currentPlayer &&
                    board[i + 2][j + 2] == currentPlayer &&
                    board[i + 3][j + 3] == currentPlayer) {
                    return true;
                }
                // Check diagonally (from top-right to bottom-left)
                if (board[i][j + connectWin - 1] == currentPlayer &&
                    board[i + 1][j + connectWin - 2] == currentPlayer &&
                    board[i + 2][j + connectWin - 3] == currentPlayer &&
                    board[i + 3][j + connectWin - 4] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

      // Input validation with clearing the input buffer
      int getValidColumn() const {
          int column;
          while (true) {
              cout << "Player " << currentPlayer << ", enter the column number (0-6): ";
              if (cin >> column) {
                  // Input was successfully converted to an integer
                  if (isValidMove(column)) {
                      break;
                  } else {
                      cout << "Invalid move. Please try again.\n";
                  }
              } else {
                  // Input was not an integer
                  clearInputBuffer();
                  cout << "Invalid input. Please enter a valid column number.\n";
              }
          }
          return column;
      }

      // Start the game
      void startGame() {
          while (!gameWon && !isBoardFull()) {
              displayBoard();
              cout << endl;
              int column = getValidColumn();

              makeMove(column, currentPlayer);
              gameWon = checkWin(rows - 1, column, currentPlayer);
              switchPlayer();
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
            startGame();
        } else {
            cout << "---------------------------------\n";
            cout << "|                               |\n";
            cout << "|          GAME ENDS !!!        |\n";
            cout << "|          THANK YOU !!!        |\n";
            cout << "|       SEE YOU NEXT TIME !!!   |\n";
            cout << "|                               |\n";
            cout << "---------------------------------\n";
            cout << endl;
        }
    }
};

class GameManager : public Connect4Game {
public:
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
      cout << " 1. Two-player Red(R) & Blue(B) game." << endl;
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

        Connect4Game::startGame();
    }
};

int main() {
    GameManager manager;
    manager.playGame();

    return 0;
}
