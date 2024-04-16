#include "game.h"

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <limits>

void Game::GameLoop()
{
    while (true)
    {
        process_test_case();
        clear_input_buffer();
    }
}

void Game::process_test_case()
{
    get_board();
    // print_board();
    get_options();
    board.clear();
}

void Game::get_options()
{
    std::string option;
    std::cin >> option;

    height = board.size() % 2 == 0 ? board.size() / 2 : board.size() / 2 + 1;

    get_pawns_number();
    check_correctness();

    if (option == "BOARD_SIZE")
    {
        std::cout << height << std::endl;
    }

    else if (option == "PAWNS_NUMBER")
    {
        int pawns = red_pawns + blue_pawns;
        std::cout << pawns << std::endl;
    }

    else if (option == "IS_BOARD_CORRECT")
    {
        if (board_is_correct)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }

    else if (option == "IS_GAME_OVER")
    {
        if (!board_is_correct)
            std::cout << "NO\n";
        else
        {
            check_if_red_win();
            if (red_player_win)
            {
                std::cout << "YES RED\n";
                std::cin.clear();
                red_player_win = false;
                return;
            }
            check_if_blue_win();
            if (blue_player_win)
            {
                std::cout << "YES BLUE\n";
                std::cin.clear();
                blue_player_win = false;
                return;
            }
            std::cout << "NO\n";
        }
    }

    std::cin.clear();
}

void Game::get_board()
{
    arleady_visited.clear();
    std::string line;
    bool beginning = true, previous_line_empty = false;

    while (true)
    {
        std::vector<char> characters;
        std::getline(std::cin, line);

        if (!line.size())
        {
            if (previous_line_empty) // If both current and previous lines are empty
                exit(EXIT_SUCCESS);  // Quit the program
            previous_line_empty = true;
            clear_input_buffer();
            continue;
        }
        previous_line_empty = false;

        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
        // Check if line starts with ---
        if (line.find("---") == 0 && !beginning)
            break;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '<' && i + 1 < line.size())
            {
                if (line[i + 1] == '>')
                    characters.push_back('e');
                else
                    characters.push_back(line[i + 1]);
            }
        }
        width = max(width, characters.size());
        if (characters.size())
            board.push_back(characters);
        beginning = false;
    }
}

void Game::print_board()
{
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Game::clear_input_buffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Game::max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

void Game::check_correctness()
{
    board_is_correct = red_pawns == blue_pawns || red_pawns - 1 == blue_pawns;
}

void Game::get_pawns_number()
{
    red_pawns = blue_pawns = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'r')
                red_pawns++;
            else if (board[i][j] == 'b')
                blue_pawns++;
        }
    }
}

bool Game::isPointVisited(int i, int j)
{
    for (const auto &p : arleady_visited)
    {
        if (p.i == i && p.j == j)
            return true;
    }
    return false;
}

void Game::check_if_red_win()
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'r' && !isPointVisited(i, j))
            {
                red_player_win = check_red_route(i, j);
                if (red_player_win)
                    return;
            }
        }
    }
}

void Game::check_if_blue_win()
{
    blue_player_win = false;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'b' && !isPointVisited(i, j))
            {
                blue_player_win = check_blue_route(i, j);
                if (blue_player_win)
                    return;
            }
        }
    }
}

/*
    i -> row
    j -> column
*/
bool Game::check_blue_route(int i, int j)
{
    bool is_top_right = false, is_bottom_left = false;

    std::stack<Point> stack;
    stack.push(Point(i, j));

    while (!stack.empty())
    {
        Point point = stack.top();
        stack.pop();
        int row = point.i, column = point.j;
        arleady_visited.push_back(Point(row, column));

        if (blue_pawn_top_right(row, column))
            is_top_right = true;
        if (blue_pawn_bottom_left(row, column))
            is_bottom_left = true;

        if (is_top_right && is_bottom_left)
        {
            
            return true;
        }

        // Check all neighbours squares
        check_neighbours(stack, row, column, 'b');
    }
    return false;
}

bool Game::check_red_route(int i, int j)
{
    bool is_bottom_right = false, is_top_left = false;

    std::stack<Point> stack;
    stack.push(Point(i, j));
    while (!stack.empty())
    {
        Point point = stack.top();
        stack.pop();
        int row = point.i, column = point.j;

        arleady_visited.push_back(Point(row, column));

        if (red_pawn_top_left(row, column))
            is_top_left = true;
        if (red_pawn_bottom_right(row, column))
            is_bottom_right = true;

        if (is_bottom_right && is_top_left)
        {
            
            return true;
        }

        // Check all neighbours squares
        check_neighbours(stack, row, column, 'r');
    }
    return false;
}

void Game::check_neighbours(std::stack<Point> &stack, int row, int column, char ch)
{
    using std::cout;
    using std::endl;
    //int init_size = stack.size();
    
    // middle row
    if (row == board.size() / 2)
    {
        // top top
        if (row - 2 >= 0 && column - 1 < board[row - 2].size() && column - 1 >= 0 && board[row - 2][column - 1] == ch && !isPointVisited(row - 2, column - 1))
            stack.push(Point(row - 2, column - 1));
        // top left
        if (row - 1 >= 0 && column - 1 >= 0 && board[row - 1][column - 1] == ch && !isPointVisited(row - 1, column - 1))
            stack.push(Point(row - 1, column - 1));
        // top right
        if (row - 1 >= 0 && column >= 0 && column < board[row - 1].size() && board[row - 1][column] == ch && !isPointVisited(row - 1, column))
            stack.push(Point(row - 1, column));
        // bottom left
        if (row + 1 < board.size() && column - 1 < board[row + 1].size() && column - 1 >= 0 && board[row + 1][column - 1] == ch && !isPointVisited(row + 1, column - 1))
            stack.push(Point(row + 1, column - 1));
        // bottom right
        if (row + 1 < board.size() && column < board[row + 1].size() && column >= 0 && board[row + 1][column] == ch && !isPointVisited(row + 1, column))
            stack.push(Point(row + 1, column));
        // bottom bottom
        if (row + 2 < board.size() && column - 1 >= 0 && column - 1 < board[row + 2].size() && board[row + 2][column - 1] == ch && !isPointVisited(row + 2, column - 1))
            stack.push(Point(row + 2, column - 1));
    }
    else if (row == board.size() / 2 - 1)
    {
        // top top
        if (row - 2 >= 0 && column - 1 < board[row - 2].size() && column - 1 >= 0 && board[row - 2][column - 1] == ch && !isPointVisited(row - 2, column - 1))
            stack.push(Point(row - 2, column - 1));
        // top left
        if (row - 1 >= 0 && column - 1 < board[row - 1].size() && column - 1 >= 0 && board[row - 1][column - 1] == ch && !isPointVisited(row - 1, column - 1))
            stack.push(Point(row - 1, column - 1));
        // top right
        if (row - 1 >= 0 && column < board[row - 1].size() && column >= 0 && column < board[row - 1].size() && board[row - 1][column] == ch && !isPointVisited(row - 1, column))
            stack.push(Point(row - 1, column));
        // bottom left
        if (row + 1 < board.size() && column < board[row + 1].size() && column >= 0 && board[row + 1][column] == ch && !isPointVisited(row + 1, column))
            stack.push(Point(row + 1, column));
        // bottom right
        if (row + 1 < board.size() && column + 1 >= 0 && column + 1 < board[row + 1].size() && board[row + 1][column + 1] == ch && !isPointVisited(row + 1, column + 1))
            stack.push(Point(row + 1, column + 1));
        // bottom bottom
        if (row + 2 < board.size() && column >= 0 && column < board[row + 2].size() && board[row + 2][column] == ch && !isPointVisited(row + 2, column))
            stack.push(Point(row + 2, column));
    }

    else if (row == board.size() / 2 + 1)
    {
        // top top
        if (row - 2 >= 0 && column < board[row - 2].size() && column >= 0 && board[row - 2][column] == ch && !isPointVisited(row - 2, column))
            stack.push(Point(row - 2, column));
        // top left
        if (row - 1 >= 0 && column < board[row - 1].size() && column >= 0 && board[row - 1][column] == ch && !isPointVisited(row - 1, column))
            stack.push(Point(row - 1, column));
        // top right
        if (row - 1 >= 0 && column + 1 >= 0 && column + 1 < board[row - 1].size() && board[row - 1][column + 1] == ch && !isPointVisited(row - 1, column + 1))
            stack.push(Point(row - 1, column + 1));
        // bottom left
        if (row + 1 < board.size() && column - 1 < board[row + 1].size() && column - 1 >= 0 && board[row + 1][column - 1] == ch && !isPointVisited(row + 1, column - 1))
            stack.push(Point(row + 1, column - 1));
        // bottom right
        if (row + 1 < board.size() && column < board[row + 1].size() && column >= 0 && board[row + 1][column] == ch && !isPointVisited(row + 1, column))
            stack.push(Point(row + 1, column));
        // bottom bottom
        if (row + 2 < board.size() && column - 1 >= 0 && column - 1 < board[row + 2].size() && board[row + 2][column - 1] == ch && !isPointVisited(row + 2, column - 1))
            stack.push(Point(row + 2, column - 1));
    }

    else if (row < board.size() / 2)
    {
        // top top
        if (row - 2 >= 0 && column - 1 < board[row - 2].size() && column - 1 >= 0 && board[row - 2][column - 1] == ch && !isPointVisited(row - 2, column - 1))
            stack.push(Point(row - 2, column - 1));
        // top left
        if (row - 1 >= 0 && column - 1 < board[row - 1].size() && column - 1 >= 0 && board[row - 1][column - 1] == ch && !isPointVisited(row - 1, column - 1))
            stack.push(Point(row - 1, column - 1));
        // top right
        if (row - 1 >= 0 && column >= 0 && column < board[row - 1].size() && board[row - 1][column] == ch && !isPointVisited(row - 1, column))
            stack.push(Point(row - 1, column));
        // bottom left
        if (row + 1 < board.size() && column >= 0 && column < board[row + 1].size() && board[row + 1][column] == ch && !isPointVisited(row + 1, column))
            stack.push(Point(row + 1, column));
        // bottom right
        if (row + 1 < board.size() && column + 1 < board[row + 1].size() && column + 1 >= 0 && board[row + 1][column + 1] == ch && !isPointVisited(row + 1, column + 1))
            stack.push(Point(row + 1, column + 1));
        // bottom bottom
        if (row + 2 < board.size() && column + 1 > 0 && column + 1 < board[row + 2].size() && board[row + 2][column + 1] == ch && !isPointVisited(row + 2, column + 1))
            stack.push(Point(row + 2, column + 1));
    }

    else if (row > board.size() / 2)
    {
        // top top
        if (row - 2 >= 0 && column + 1 < board[row - 2].size() && column + 1 >= 0 && board[row - 2][column + 1] == ch && !isPointVisited(row - 2, column + 1))
            stack.push(Point(row - 2, column + 1));
        // top left
        if (row - 1 >= 0 && column < board[row - 1].size() && column >= 0 && board[row - 1][column] == ch && !isPointVisited(row - 1, column))
            stack.push(Point(row - 1, column));
        // top right
        if (row - 1 >= 0 && column + 1 >= 0 && column + 1 < board[row - 1].size() && board[row - 1][column + 1] == ch && !isPointVisited(row - 1, column + 1))
            stack.push(Point(row - 1, column + 1));
        // bottom left
        if (row + 1 < board.size() && column - 1 < board[row + 1].size() && column - 1 >= 0 && board[row + 1][column - 1] == ch && !isPointVisited(row + 1, column - 1))
            stack.push(Point(row + 1, column - 1));
        // bottom right
        if (row + 1 < board.size() && column < board[row + 1].size() && column >= 0 && board[row + 1][column] == ch && !isPointVisited(row + 1, column))
            stack.push(Point(row + 1, column));
        // bottom bottom
        if (row + 2 < board.size() && column - 1 >= 0 && column - 1 < board[row + 2].size() && board[row + 2][column - 1] == ch && !isPointVisited(row + 2, column - 1))
            stack.push(Point(row + 2, column - 1));
    }
    int new_size = stack.size();
    /*if (new_size != init_size)
    {
        std::cout << "Point : " << stack.top().i << ", " << stack.top().j << std::endl;
    }*/
}
