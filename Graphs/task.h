#pragma once

#include "vector.h"
#include "stack.h"
#include <map>

class Task
{
private:
    long long wynik_dopelnienie_grafu;
    int wynik_podgrafy_c4;
    Vector<int> wynik_degree_sequence;
    std::map<int, Vector<int>> graph_map;
    Vector<int>* graph_map_2 = nullptr;
    int wynik_liczba_skladowych_spojnosci;
    bool wynik_dwudzielnosc_grafu;

    char czerwony = 'r';
    char niebieski = 'b';

public:
    Task() = default;
    ~Task()
    {
        delete[] graph_map_2;
    }
    void perform_task();
    void liczba_skladowych_spojnosci(const std::pair<int, Vector<int>>& pair, std::map<int, bool>& visited, Stack<int>& stack);
    void dwudzielnosc_grafu(const std::pair<int, Vector<int>>& pair, std::map<int, char>& kolory, Stack<int>& stack);

    void get_graph();
    void zadania();
    void output() const;
};