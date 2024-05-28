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
    // std::map<int, Vector<int>> graph_map;
    Vector<int>* graph_map = nullptr;
    int wynik_liczba_skladowych_spojnosci;
    bool wynik_dwudzielnosc_grafu;

    char czerwony = 'r';
    char niebieski = 'b';
    long long n = -1;

public:
    Task() = default;
    ~Task()
    {
        delete[] graph_map;
    }
    void perform_task();
    void liczba_skladowych_spojnosci(int node_index, Vector<int>& node_values, Vector<int>& visited, Stack<int>& stack);
    void dwudzielnosc_grafu(int node_index, Vector<int>& node_values, Vector<int>& kolory, Stack<int>& stack);

    void get_graph();
    void zadania();
    void output() const;
};