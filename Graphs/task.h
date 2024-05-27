#pragma once

#include <vector>
#include <map>
#include <queue>
#include <stack>

class Task
{
private:
    long long wynik_dopelnienie_grafu;
    int wynik_podgrafy_c4;
    std::vector<int> wynik_degree_sequence;
    std::map<int, std::vector<int>> graph_map;
    int wynik_liczba_skladowych_spojnosci;
    bool wynik_dwudzielnosc_grafu;
    std::vector<int> wynik_acentrycznosc;

    char czerwony = 'r';
    char niebieski = 'b';

public:
    Task() = default;
    void perform_task();
    void liczba_skladowych_spojnosci(const std::pair<int, std::vector<int>>& pair, std::map<int, bool>& visited, std::stack<int>& stack);
    void dwudzielnosc_grafu(const std::pair<int, std::vector<int>>& pair, std::map<int, char>& kolory, std::stack<int>& stack);
    void acentrycznosc_wierzcholkow(const std::pair<int, std::vector<int>>& pair);
    void podgrafy_c4();

    void get_graph();
    void zadania();
    void output() const;
};