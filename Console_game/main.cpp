#include "game.h"
#include <iostream>

int main() {
    using namespace std;

    srand(time(nullptr));

    LightsOff game;
    int choice;
    int moves = 0;
    bool game_loaded = false;
    bool game_won = false;

    do {
        cout << "\nLIGHTS OUT GAME " << endl;
        cout << "1. New game" << endl;

        if (game_loaded && !game_won) {
            cout << "2. Make a move" << endl;
            cout << "3. Save game" << endl;
            cout << "4. Show field" << endl;
        }

        cout << "5. Load game" << endl;
        cout << "6. Game rules" << endl;
        cout << "7. Exit" << endl;

        cout << "Select action: ";
        if (!(game_loaded && !game_won)) {
            while (!(cin >> choice) || choice < 1 || choice > 7 || (choice > 1 && choice < 5)) {
                cout << "Invalid choice! Enter number 1, 5, 6 or 7: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
        }
        else {
            while (!(cin >> choice) || choice < 1 || choice > 7) {
                cout << "Invalid choice! Enter number from 1 to 7: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
        }
        switch (choice) {
        case 1: { // New game
            int size;
            cout << "Enter field size (from 3 to 10): ";

            while (!(cin >> size) || size < 3 || size > 10) {
                cout << "Enter integer from 3 to 10: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            game = LightsOff(size);
            game.generate_game();
            moves = 0;
            game_loaded = true;
            game_won = false;

            cout << "NEW GAME! Size: " << size << "x" << size << endl;
            game.print_field();
            break;
        }

        case 2: { // Make a move
            if (!game_loaded) {
                cout << "First start a new game!" << endl;
                break;
            }

            if (game_won) {
                cout << "Game already won! Start a new game." << endl;
                break;
            }

            game.print_field();
            cout << "Current moves: " << moves << endl;

            int row, col;
            cout << "\nEnter coordinates for move (row column): ";

            while (!(cin >> row >> col) || row < 1 || row > game.get_size() || col < 1 || col > game.get_size()) {
                cout << "Invalid coordinates! Enter two numbers from 1 to "
                    << game.get_size() << ": ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            game.make_move(row, col);
            moves++;

            if (game.check_win()) {
                game_won = true;
                cout << "CONGRATULATIONS! YOU WON!" << endl;
                cout << "Total moves: " << moves << endl;
                game.print_field();
            }
            else {
                cout << "Move completed! Total moves: " << moves << endl;
                game.print_field();
            }
            break;
        }

        case 3: { // Save the game
            if (!game_loaded) {
                cout << "No active game to save!" << endl;
                break;
            }
            game.save_game(moves);
            cout << "Game saved. Moves made: " << moves;
            if (game_won) {
                cout << " (Game completed with victory)";
            }
            cout << endl;
            break;
        }

        case 4: { // Displaying a field
            if (!game_loaded) {
                cout << "No active game!" << endl;
                break;
            }

            game.print_field();
            cout << "Moves made: " << moves;
            if (game_won) {
                cout << " (Game completed with victory)";
            }
            cout << endl;
            break;
        }

        case 5: { // Loading a game from a file
            int loaded_moves = game.download_game();
            if (loaded_moves >= 0) {
                game_loaded = true;
                moves = loaded_moves;

                game_won = game.check_win();

                game.print_field();
                if (game_won) {
                    cout << " (Game completed with victory)";
                }
                cout << endl;
            }
            break;

        }
        case 6:
            cout << "Game goal: Turn off all lights on the game field. 1 - lights are on, 0 - lights are off" << endl;
            cout << "Game mechanics: When clicking on any light, its state toggles (light turns on or off) together with the state of four neighboring lights (top, bottom, left, and right)." << endl;
            cout << "Victory condition: All lights on the game field must be turned off." << endl;
            break;

        case 7: { // Exit
            cout << "Thank you for playing! Goodbye!" << endl;
            break;
        }

        default:
            break;
        }

    } while (choice != 7);

    return 0;
}