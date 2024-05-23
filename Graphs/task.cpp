#include "task.hpp"
#include <map>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

void Task::perform_task()
{
    this->num_of_connected_components = 0;
    this->bipartite = false;
    degree_sequence.clear();
    graph_map.clear();
    eccentricity.clear();
    this->get_graph();
    this->number_of_connected_components();
    this->is_bipartite();
    this->get_eccentricity();
    this->output();
}

void Task::get_graph()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int amount;
        std::cin >> amount;
        degree_sequence.push_back(amount);
        for (int j = 0; j < amount; j++)
        {
            int value;
            std::cin >> value;
            graph_map[i+1].push_back(value);
        }
        if (amount == 0)
        {
            // We need to increate number of components
            this->num_of_connected_components++;
        }
    }

    std::sort(degree_sequence.begin(), degree_sequence.end(), [](int a, int b){
        return a > b;
    });
}

bool node_visited(std::vector<int> visited, int node)
{
    for (int i = 0; i < visited.size(); i++)
    {
        if (visited.at(i) == node)
            return true;
    }
    return false;
}

void Task::number_of_connected_components() 
{
    std::vector<int> visited;

    for (const auto& pair : graph_map) 
    {
        int start_node = pair.first;
        if (!node_visited(visited, start_node)) 
        {
            std::stack<int> stack;
            stack.push(start_node);
            while (!stack.empty()) 
            {
                int node = stack.top();
                stack.pop();
                if (node_visited(visited, node)) 
                    continue;
                visited.push_back(node);
                for (int neighbor : graph_map.at(node)) 
                    if (!node_visited(visited, neighbor))
                        stack.push(neighbor);
            }
            num_of_connected_components++;
        }
    }
}

void Task::is_bipartite() 
{
    std::map<int, Color> node_colors;
    this->bipartite = true;

    for (const auto& pair : graph_map) 
    {
        int start_node = pair.first;
        if (node_colors.find(start_node) == node_colors.end()) 
        {
            std::queue<int> q;
            q.push(start_node);
            node_colors[start_node] = RED; 

            while (!q.empty()) 
            {
                int node = q.front();
                q.pop();
                Color current_color = node_colors[node];
                Color next_color = (current_color == RED) ? BLUE : RED;

                for (int neighbor : graph_map.at(node)) 
                {
                    if (node_colors.find(neighbor) == node_colors.end()) 
                    {
                        node_colors[neighbor] = next_color;
                        q.push(neighbor);
                    } 
                    else if (node_colors[neighbor] == current_color) 
                    {
                        this->bipartite = false;
                        return;
                    }
                }
            }
        }
    }
}

void Task::get_eccentricity()
{

}

void Task::output() const
{
    for (const int& v : degree_sequence)
        std::cout << v << " ";
    std::cout << std::endl;
    std::cout << this->num_of_connected_components << std::endl;
    if (this->bipartite) std::cout << "T" << std::endl;
    else std::cout << "F" << std::endl;
    for (int i = 0; i < 7; i++)
        std::cout << "?" << std::endl;
}