#include "game.h"
#include <iostream>

int main() {
    using namespace std;

    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    LightsOff game;
    int choice;
    int moves = 0;
    bool game_loaded = false;
    bool game_won = false;

    do {
        cout << "\n ИГРА 'ГАСИМ СВЕТ' " << endl;
        cout << "1. Новая игра" << endl;

        if (game_loaded && !game_won) {
            cout << "2. Сделать ход" << endl;
            cout << "3. Сохранить игру" << endl;
            cout << "4. Показать поле" << endl;
        }

        cout << "5. Загрузить игру" << endl;
        cout << "6. Правила игры" << endl;
        cout << "7. Выход" << endl;

        cout << "Выберите действие: ";
        if (!(game_loaded && !game_won)) {
            while (!(cin >> choice) || choice < 1 || choice > 7 || (choice > 1 && choice < 5)) {
                cout << "Неверный выбор! Введите число 1, 5, 6 или 7: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
        }
        else {
            while (!(cin >> choice) || choice < 1 || choice > 7) {
                cout << "Неверный выбор! Введите число от 1 до 7: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
        }
        switch (choice) {
        case 1: { // Новая игра
            int size;
            cout << "Введите размер поля (от 3 до 10): ";

            while (!(cin >> size) || size < 3 || size > 10) {
                cout << "Введите целое число от 3 до 10: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            game = LightsOff(size);
            game.generate_game();
            moves = 0;
            game_loaded = true;
            game_won = false;

            cout << "НОВАЯ ИГРА! Размер: " << size << "x" << size << endl;
            game.print_field();
            break;
        }

        case 2: { // Сделать ход
            if (!game_loaded) {
                cout << "Сначала начните новую игру!" << endl;
                break;
            }

            if (game_won) {
                cout << "Игра уже завершена победой! Начните новую игру." << endl;
                break;
            }

            game.print_field();
            cout << "Текущие ходы: " << moves << endl;

            int row, col;
            cout << "\nВведите координаты для хода (строка столбец): ";

            while (!(cin >> row >> col) || row < 1 || row > game.get_size() || col < 1 || col > game.get_size()) {
                cout << "Неверные координаты! Введите два числа от 1 до "
                    << game.get_size() << ": ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            game.make_move(row, col);
            moves++;

            if (game.check_win()) {
                game_won = true;
                cout << "ПОЗДРАВЛЯЕМ! ВЫ ПОБЕДИЛИ!" << endl;
                cout << "Всего ходов: " << moves << endl;
                game.print_field();
            }
            else {
                cout << "Ход выполнен! Всего ходов: " << moves << endl;
                game.print_field();
            }
            break;
        }

        case 3: { // Сохранить игру
            if (!game_loaded) {
                cout << "Нет активной игры для сохранения!" << endl;
                break;
            }
            game.save_game(moves);
            cout << "Игра сохранена. Ходов сделано: " << moves;
            if (game_won) {
                cout << " (Игра завершена победой)";
            }
            cout << endl;
            break;
        }

        case 4: { // Показать поле
            if (!game_loaded) {
                cout << "Нет активной игры!" << endl;
                break;
            }

            game.print_field();
            cout << "Ходов сделано: " << moves;
            if (game_won) {
                cout << " (Игра завершена победой)";
            }
            cout << endl;
            break;
        }

        case 5: { // Загрузить игру из файла
            int loaded_moves = game.download_game();
            if (loaded_moves >= 0) {
                game_loaded = true;
                moves = loaded_moves;

                game_won = game.check_win();

                game.print_field();
                if (game_won) {
                    cout << " (Игра завершена победой)";
                }
                cout << endl;
            }
            break;

        }
        case 6:
            cout << "Цель игры: Погасить все огни на игровом поле. 1 - огонёк горит, 0 - не горит." << endl;
            cout << "Механика игры: При нажатии на любой огонёк переключается его состояние (свет включается или выключается) вместе с состоянием четырёх соседних огоньков (верхнего, нижнего, левого и правого)." << endl;
            cout << "Условие победы: Все огоньки на игровом поле должны быть погашены. То есть должны остаться лишь нули." << endl;
            break;

        case 7: { // Выход
            cout << "Спасибо за игру! До свидания!" << endl;
            break;
        }

        default:
            break;
        }

    } while (choice != 7);

    return 0;
}
