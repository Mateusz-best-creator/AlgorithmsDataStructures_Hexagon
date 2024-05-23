#pragma once

#include <vector>
#include <map>

class Task
{
private:
    std::vector<int> degree_sequence;
    std::map<int, std::vector<int>> graph_map;
    int num_of_connected_components = 0;
    bool bipartite = false;
    std::vector<int> eccentricity;

protected:
    enum Color : char {
        RED = 'r',
        BLUE = 'b'
    };

public:
    void perform_task();

    void get_graph();
    void number_of_connected_components();
    void is_bipartite();
    void get_eccentricity();
    void output() const;
};