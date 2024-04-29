#pragma once

#include <vector>
#include <string>
#include <stack>

struct Point
{
    int i, j;
    Point(int row, int column)
        : i(row), j(column) {}
};

class Game
{
private:
    std::vector<std::vector<char>> board;
    int height = 0, width = 0;
    bool board_is_correct;
    int red_pawns = 0, blue_pawns = 0;
    bool blue_player_win = false, red_player_win = false;
    int red_route_length = 0, blue_route_length = 0;

    std::vector<Point> arleady_visited;

public:
    Game() = default;
    ~Game() = default;

    void GameLoop();

    void process_test_case();
    void get_options();
    void get_board();
    void clear_input_buffer();
    int max(int, int);
    void check_correctness();
    void get_pawns_number();

    bool isPointVisited(int i, int j);
    void check_if_red_win();
    void check_if_blue_win();
    bool check_blue_route(int, int);
    bool check_red_route(int i, int j);

    void check_neighbours(std::stack<Point>&, int, int, char);

    bool check_if_board_possible();

    template <typename T, typename P>
    T remove_if(T beg, T end, P pred)
    {
        T dest = beg;
        for (T itr = beg; itr != end; ++itr)
            if (!pred(*itr))
                *(dest++) = *itr;
        return dest;
    }

    bool blue_pawn_top_right(int i, int j) const { return i <= board.size() / 2 && j == board[i].size() - 1; }
    bool blue_pawn_bottom_left(int i, int j) const { return i >= board.size() / 2 && j == 0; }
    bool red_pawn_top_left(int i, int j) const { return i <= board.size() / 2 && j == 0; }
    bool red_pawn_bottom_right(int i, int j) const { return i >= board.size() / 2 && j == board[i].size() - 1; }

    void winning_options(bool&, bool&, bool&, bool&);
    void print_result(bool is_true);
    void check_future_win_red(int, bool& red_in_1_move, bool& red_in_2_moves);
    void check_future_win_blue(int free_cells, bool& blue_in_1_move, bool& blue_in_2_moves);
};