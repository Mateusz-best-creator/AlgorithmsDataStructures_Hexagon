#include "task.h"
#include <algorithm>
#include <stdio.h>
#include "vector.h"

void Task::perform_task()
{
    wynik_degree_sequence.clear();
    graph_map.clear();
    this->get_graph();
    this->wynik_liczba_skladowych_spojnosci = 0;
    this->wynik_dwudzielnosc_grafu = true;
    this->wynik_acentrycznosc.clear();
    this->wynik_podgrafy_c4 = 0;
    this->zadania();
    // this->podgrafy_c4();
    this->output();
}

void Task::get_graph()
{
    long long n;
    scanf("%lld", &n);
    long long krawedzie = 0;
    for (int i = 0; i < n; i++)
    {
        int amount;
        scanf("%d", &amount);
        wynik_degree_sequence.push_back(amount);
        for (int j = 0; j < amount; j++)
        {
            int value;
            scanf("%d", &value);
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

void Task::zadania()
{
    std::map<int, bool> spojnosci_visited;
    std::stack<int> spojnosci_stack;
    
    std::map<int, char> dwudielnosc_kolory;
    std::stack<int> dwudzielnosc_stack;

    for (auto& pair : graph_map)
    {
        this->liczba_skladowych_spojnosci(pair, spojnosci_visited, spojnosci_stack);
        this->dwudzielnosc_grafu(pair, dwudielnosc_kolory, dwudzielnosc_stack);
        // this->acentrycznosc_wierzcholkow(pair);
        // this->podgrafy_c4(pair);
    }
}

void Task::liczba_skladowych_spojnosci(const std::pair<int, std::vector<int>>& pair, std::map<int, bool>& visited, std::stack<int>& stack)
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

void Task::dwudzielnosc_grafu(const std::pair<int, std::vector<int>>& pair, std::map<int, char>& kolory, std::stack<int>& stack)
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
void Task::acentrycznosc_wierzcholkow(const std::pair<int, std::vector<int>>& pair)
{
    if (pair.second.empty()) 
    {
        wynik_acentrycznosc.push_back(0);
        return;
    }

    int current_node = pair.first;
    std::map<int, bool> visited;
    std::queue<int> queue;
    std::map<int, int> depth;

    int max_depth = 0;

    queue.push(current_node);
    visited[current_node] = true;
    depth[current_node] = 0;

    while (!queue.empty()) 
    {
        int node = queue.front();
        queue.pop();

        visited[node] = true;

        for (int neighbor : graph_map[node]) 
        {
            if (!visited[neighbor]) 
            {
                queue.push(neighbor);
                depth[neighbor] = depth[node] + 1;
                if (depth[neighbor] > max_depth)
                    max_depth = depth[neighbor];
            }
        }
    }
    wynik_acentrycznosc.push_back(max_depth);
}

void Task::podgrafy_c4()
{
    // for (auto& pair : graph_map)
    // {
    //     int start_node = pair.first;
    //     if (start_node == 2)
    //         return;
    //     std::map<int, bool> visited;
    //     std::stack<int> stack;
    //     std::map<int, int> depth;
    //     depth[start_node] = 1;
    //     stack.push(start_node);

    //     while (!stack.empty())
    //     {
    //         int stack_node = stack.top();
    //         stack.pop();
    //         visited[stack_node] = true;


    //         for (int i = 0; i < graph_map.at(stack_node).size(); i++)
    //         {
    //             int neighbor = graph_map.at(stack_node).at(i);
    //             if (!visited[neighbor])
    //             {
    //                 stack.push(neighbor);
    //                 depth[neighbor] = depth[stack_node] + 1;
    //             }
    //             else if (stack_node == start_node)
    //             {
    //                 stack.push(neighbor);
    //             }
    //         }
    //     }
    // }
    /*
    każdy cykl dwukrotnie - przechodząc zgodnie z ruchem wskazówek zegara i przeciwnie. 
    Dodatkowo każdy cykl zostanie policzony przez każdy z jego czterech wierzchołków. 
    2 * 4 = 8
    */
    this->wynik_podgrafy_c4 /= 8;
}

void Task::output() const
{
    for (const int& v : wynik_degree_sequence)
        printf("%d ", v);
    printf("\n");
    printf("%d\n", this->wynik_liczba_skladowych_spojnosci);
    if (this->wynik_dwudzielnosc_grafu)
        printf("T\n");
    else
        printf("F\n");
    // for (int i = 0; i < wynik_acentrycznosc.size(); i++)
        // printf("%d ", wynik_acentrycznosc.at(i));
    // printf("\n");
    for (int i = 0; i < 6; i++)
        printf("?\n");
    // std::cout << wynik_podgrafy_c4 << std::endl;
    printf("%lld\n", wynik_dopelnienie_grafu);
}