#pragma once

#include <vector>
#include <map>
#include <queue>

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
    void number_of_connected_components(std::vector<int>& visited, const std::pair<int, std::vector<int>>& pair);
    void is_bipartite(std::map<int, Color>& node_colors, const std::pair<int, std::vector<int>>& pair);
    void bipartite_calculate_eccentricity(std::map<int, int>&, std::queue<int>&, std::map<int, Color>&, const std::pair<int, std::vector<int>>&);
    void components_bipartite_eccentricity();
    void output() const;
};