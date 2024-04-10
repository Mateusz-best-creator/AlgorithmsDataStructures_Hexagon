#pragma once

#include <vector>
#include <string>

class Game
{
private:
    std::vector<std::vector<char>> board;
    int height = 0, width = 0;
    bool board_is_correct;
    int red_pawns = 0, blue_pawns = 0;
    bool blue_player_win = false, red_player_win = false;

protected:
    struct Point
    {
        int row, column;
    };

public:
    Game() = default;
    ~Game() = default;

    void GameLoop();

    void process_test_case();
    void print_board();
    void get_options();
    void get_board();
    void clear_input_buffer();
    int max(int, int);
    void check_correctness();
    void get_pawns_number();

    void check_if_red_win();
    void check_if_blue_win();

    template<typename T, typename P>
    T remove_if(T beg, T end, P pred)
    {
        T dest = beg;
        for (T itr = beg;itr != end; ++itr)
            if (!pred(*itr))
                *(dest++) = *itr;
        return dest;
    }
};