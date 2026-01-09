#include "game.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime> 

using namespace std;

// Private method, the main function of making a move
void LightsOff::switching(int row, int col) {
    field_[row][col] = 1 - field_[row][col];

    if (row > 0) {
        field_[row - 1][col] = 1 - field_[row - 1][col];
    }
    if (row < size_ - 1) {
        field_[row + 1][col] = 1 - field_[row + 1][col];
    }
    if (col > 0) {
        field_[row][col - 1] = 1 - field_[row][col - 1];
    }
    if (col < size_ - 1) {
        field_[row][col + 1] = 1 - field_[row][col + 1];
    }
}

// Constructors
LightsOff::LightsOff() : size_(0) {}

LightsOff::LightsOff(int size) {
    size_ = size;
    field_ = vector<vector<int>>(size_, vector<int>(size_));
}

// Game generation
void LightsOff::generate_game() {
    srand(time(nullptr));

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            field_[i][j] = 0;
        }
    }
    if (size_ % 2 == 0) {
        for (int k = 0; k < size_ - 1; k++) {
            int row = rand() % size_;
            int col = rand() % size_;
            switching(row, col);
        }
    }
    else {
        for (int k = 0; k < size_; k++) {
            int row = rand() % size_;
            int col = rand() % size_;
            switching(row, col);
        }
    }

}

// Player's move
void LightsOff::make_move(int row, int col) {
    if (row < 1 || row > size_ || col < 1 || col > size_) {
        cout << "Invalid coordinates! Use values ​​from 1 to " << size_ << endl;
        return;
    }
    switching(row - 1, col - 1);
}

// Check for win
bool LightsOff::check_win() {
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (field_[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

// Displaying a field to the console
void LightsOff::print_field() {
    if (size_ == 0) {
        cout << "The field is not initialized!" << endl;
        return;
    }
    cout << "    ";
    for (int j = 0; j < size_; j++) {
        cout << setw(3) << j + 1;
    }
    cout << endl;
    cout << "    ";
    for (int j = 0; j < size_; j++) {
        cout << setw(3) << "---";
    }
    cout << endl;

    for (int i = 0; i < size_; i++) {
        cout << setw(2) << i + 1 << " |";
        for (int j = 0; j < size_; j++) {
            cout << setw(3) << field_[i][j];
        }
        cout << endl;
    }
}

// Saving the game to a file
void LightsOff::save_game(int moves) {
    ofstream file("game_save.txt");
    if (!file.is_open()) {
        cout << "Error opening file for saving!" << endl;
        return;
    }

    file << size_ << endl;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            file << field_[i][j] << " ";
        }
        file << endl;
    }
    file << moves;
    file.close();

    cout << "The game is saved to a file game_save.txt" << endl;
}

// Loading a game from a file
int LightsOff::download_game() {
    ifstream file("game_save.txt");
    if (!file.is_open()) {
        cout << "Error opening file for download!" << endl;
        cout << "File game_save.txt not found." << endl;
        return 0;
    }

    file >> size_;
    if (file.fail() || size_ <= 2 || size_ > 10) {
        cout << "Error reading field size from file!" << endl;
        file.close();
        return 0;
    }

    field_.resize(size_, vector<int>(size_));

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (!(file >> field_[i][j])) {
                cout << "Error reading field data from file!" << endl;
                file.close();
                return 0;
            }
        }
    }

    int moves;
    if (!(file >> moves)) {
        cout << "Error reading number of moves from file!" << endl;
        file.close();
        return 0;
    }

    file.close();

    cout << "The game has been successfully loaded from the game_save.txt file." << endl;
    cout << "Field size: " << size_ << "x" << size_ << endl;
    cout << "Moves made: " << moves << endl;


    return moves;
}

int LightsOff::get_size() const {
    return size_;
}