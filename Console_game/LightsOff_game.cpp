#include "game.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime> 

using namespace std;

// Приватный метод, основная функция совершения хода
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

// Конструкторы
LightsOff::LightsOff() : size_(0) {}

LightsOff::LightsOff(int size) {
    size_ = size;
    field_ = vector<vector<int>>(size_, vector<int>(size_));
}

// Генерация игры
void LightsOff::generate_game() {
    srand(time(nullptr));

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            field_[i][j] = 0;
        }
    }
    // Проверяем размер поля на нечетность для того, чтобы исключить вероятность генерации выигрышного поля
    // Если размер поля число четное, то может случиться двойное нажатие на один и тот же огонёк и поле не изменится
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

// Ход игрока
void LightsOff::make_move(int row, int col) {
    if (row < 1 || row > size_ || col < 1 || col > size_) {
        cout << "Неверные координаты! Используйте значения от 1 до " << size_ << endl;
        return;
    }
    switching(row - 1, col - 1);
}

// Проверка победы
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

// Отображение поля на консоли
void LightsOff::print_field() {
    if (size_ == 0) {
        cout << "Поле не инициализировано!" << endl;
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

// Сохранение игры в файл
void LightsOff::save_game(int moves) {
    ofstream file("game_save.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для сохранения!" << endl;
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

    cout << "Игра сохранена в файл game_save.txt" << endl;
}

// Загрузка игры из файла
int LightsOff::download_game() {
    ifstream file("game_save.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для загрузки!" << endl;
        cout << "Файл game_save.txt не найден." << endl;
        return 0;
    }

    file >> size_;
    if (file.fail() || size_ <= 2 || size_ > 10) {
        cout << "Ошибка чтения размера поля из файла!" << endl;
        file.close();
        return 0;
    }

    field_.resize(size_, vector<int>(size_));

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (!(file >> field_[i][j])) {
                cout << "Ошибка чтения данных поля из файла!" << endl;
                file.close();
                return 0;
            }
        }
    }

    int moves;
    if (!(file >> moves)) {
        cout << "Ошибка чтения количества ходов из файла!" << endl;
        file.close();
        return 0;
    }

    file.close();

    cout << "Игра успешно загружена из файла game_save.txt" << endl;
    cout << "Размер поля: " << size_ << "x" << size_ << endl;
    cout << "Ходов сделано: " << moves << endl;

    return moves;
}

int LightsOff::get_size() const {
    return size_;
}
