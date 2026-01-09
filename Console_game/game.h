#include <iostream>
#include <vector>
using namespace std;

class LightsOff {
private:
    vector<vector<int>> field_;
    int size_;
    void switching(int row, int col);

public:
    LightsOff();
    LightsOff(int size);

    void generate_game();
    void make_move(int row, int col);
    bool check_win();
    void print_field();
    void save_game(int moves);
    int download_game();
    int get_size() const;
};