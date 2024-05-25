#include "task.hpp"
#include <iostream>
#include <algorithm>
#include <stack>

void Task::perform_task()
{
    wynik_degree_sequence.clear();
    graph_map.clear();
    this->get_graph();
    this->wynik_liczba_skladowych_spojnosci = 0;
    this->liczba_skladowych_spojnosci();
    this->wynik_dwudzielnosc_grafu = true;
    this->dwudzielnosc_grafu();
    this->output();
}

void Task::get_graph()
{
    long long n;
    std::cin >> n;
    long long krawedzie = 0;
    for (int i = 0; i < n; i++)
    {
        int amount;
        std::cin >> amount;
        wynik_degree_sequence.push_back(amount);
        for (int j = 0; j < amount; j++)
        {
            int value;
            std::cin >> value;
            graph_map[i+1].push_back(value);
            krawedzie++;
        }
        if (amount == 0)
            graph_map[i+1];
    }
    krawedzie /= 2;
    wynik_dopelnienie_grafu = (n * (n - 1) / 2) - krawedzie;

    std::sort(wynik_degree_sequence.begin(), wynik_degree_sequence.end(), [](int a, int b){
        return a > b;
    });

    // for (const auto& [key, value] : graph_map)
    // {
    //     std::cout << key << ": ";
    //     for (const int& v : value)
    //         std::cout << v << " ";
    //     std::cout << std::endl;
    // }
}

void Task::liczba_skladowych_spojnosci()
{
    std::map<int, bool> visited;
    std::stack<int> stack;

    for (auto pair : graph_map)
    {
        if (!visited[pair.first])
        {
            stack.push(pair.first);
            while (!stack.empty())
            {
                int stack_node = stack.top();
                stack.pop();
                if (visited[stack_node])
                    continue;
                visited[stack_node] = true;
                for (int i = 0; i < graph_map[stack_node].size(); i++)
                {
                    int neighbor = graph_map[stack_node].at(i);
                    if (!visited[neighbor])
                    {
                        stack.push(neighbor);
                    }
                }
            }
            wynik_liczba_skladowych_spojnosci++;
        }
    }
}

void Task::dwudzielnosc_grafu()
{
    char czerwony = 'r';
    char niebieski = 'b';

    std::map<int, char> kolory;
    std::stack<int> stack;

    for (auto pair : graph_map)
    {
        int start_node = pair.first;
        if (kolory.count(start_node) == 0)
        {
            stack.push(start_node);
            kolory[start_node] = czerwony;

            while (!stack.empty())
            {
                int stack_node = stack.top();
                stack.pop();
                char obecny_kolor = kolory[stack_node];
                char przeciwny_kolor = (obecny_kolor == czerwony) ? niebieski : czerwony;

                for (int i = 0; i < graph_map[stack_node].size(); i++)
                {
                    int neighbor = graph_map[stack_node].at(i);
                    if (kolory.count(neighbor) == 0)
                    {
                        kolory[neighbor] = przeciwny_kolor;
                        stack.push(neighbor);
                    }
                    else if (kolory[neighbor] == obecny_kolor)
                    {
                        this->wynik_dwudzielnosc_grafu = false;
                        return;
                    }
                }
            }
        }
    }
}

void Task::output() const
{
    for (const int& v : wynik_degree_sequence)
        std::cout << v << " ";
    std::cout << std::endl;
    std::cout << wynik_liczba_skladowych_spojnosci << std::endl; 
    if (this->wynik_dwudzielnosc_grafu)
        std::cout << "T" << std::endl;
    else
        std::cout << "F" << std::endl;
    for (int i = 0; i < 6; i++)
        std::cout << "?" << std::endl;
    std::cout << wynik_dopelnienie_grafu << std::endl;
}