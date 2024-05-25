#pragma once

#include <vector>
#include <map>
#include <queue>
#include <set>

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

public:
    Task() = default;
    void perform_task();
    void liczba_skladowych_spojnosci();
    void dwudzielnosc_grafu();
    void acentrycznosc_wierzcholkow();
    void podgrafy_c4();

    void get_graph();
    void zadania();
    void output() const;
};