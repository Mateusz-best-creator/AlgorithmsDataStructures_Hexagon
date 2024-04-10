#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <limits>

void clear_input_buffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int get_pawns_number(const std::vector<std::vector<char>>& board)
{
    int counter = 0;
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'r' || board[i][j] == 'b')
                counter++;
        }
    }
    return counter;
}

template<typename T, typename P>
T remove_if(T beg, T end, P pred)
{
    T dest = beg;
    for (T itr = beg;itr != end; ++itr)
        if (!pred(*itr))
            *(dest++) = *itr;
    return dest;
}

void get_board(std::vector<std::vector<char>>& board, int& width)
{
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

void get_option(const std::vector<std::vector<char>>& board, const int& width)
{
    std::string option;
    std::cin >> option;

    int height = board.size() % 2 == 0 ? board.size() / 2 : board.size() / 2 + 1;

    //std::cout << "H & W = " << height << " " << width << std::endl;

    if (option == "BOARD_SIZE")
    {
        std::cout << height << std::endl;
    }

    else if (option == "PAWNS_NUMBER")
    {
        int pawns = 0;
        pawns = get_pawns_number(board);
        std::cout << pawns << std::endl;
    }

    else if (option == "IS_BOARD_CORRECT")
    {
        if (height == width)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }

    std::cin.clear();
}

void process_test_case()
{
    std::vector<std::vector<char>> board;
    int width = 0;
    get_board(board, width);
    get_option(board, width);
    board.clear();
}


int main()
{
    while (true)
    {
        process_test_case();
        clear_input_buffer();
    }
}