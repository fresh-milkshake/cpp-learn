#include<iostream>

class TicTacToe {
    private:
        char board[3][3];
        char current_player = 'X';
        bool game_over = false;
        const char default_char = '-';
    public:
        TicTacToe() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    board[i][j] = default_char;
                }
            }
        }

        void print_board() {
            std::cout << "  0 1 2\n";
            for (int i = 0; i < 3; i++) {
                std::cout << i << " ";
                for (int j = 0; j < 3; j++) {
                    std::cout << board[i][j] << " ";
                }
                std::cout << "\n";
            }
        }

        void next_player() { current_player = (current_player == 'X') ? 'O' : 'X'; }

        bool validate_turn(int row, int col) {
            return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == default_char);
        }

        void set_value(int row, int col) {
            board[row][col] = current_player;
        }

        void make_turn() {
            char row, col;
            int row_int, col_int;
            while (true) {
                std::cout << "Player " << current_player << " turn:\n";
                std::cout << "Row: ";
                std::cin >> row;
                std::cout << "Col: ";
                std::cin >> col;
                if (!std::isdigit(row) && !std::isdigit(col)) {
                    std::cout << "Inputs not are numbers\n";
                    continue;
                }

                row_int = row - '0';
                col_int = col - '0';

                if (!validate_turn(row_int, col_int)) {
                    std::cout << "Invalid turn, number out of range or position already taken\n";
                    continue;
                }
                set_value(row_int, col_int);
                break;
            }
        }

        char check_winner() {
            for (int i = 0; i < 3; i++) {
                if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != default_char) {
                    return board[i][0];
                }
                if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != default_char) {
                    return board[0][i];
                }
            }

            if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != default_char) {
                return board[0][0];
            }
            if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != default_char) {
                return board[0][2];
            }

            return default_char;
        }

        void play() {
            while (!game_over) {
                print_board();
                make_turn();
                char winner = check_winner();
                if (winner != default_char) {
                    std::cout << "Player " << winner << " wins!" << std::endl;
                    game_over = true;
                }
                next_player();
            }
        }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}