#include "task.h"
#include <stdio.h>
#include "vector.h"
#include "stack.h"

void Task::perform_task()
{
    wynik_degree_sequence.clear();
    graph_map.clear();
    this->get_graph();
    this->wynik_liczba_skladowych_spojnosci = 0;
    this->wynik_dwudzielnosc_grafu = true;
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

    graph_map_2 = new Vector<int>[n];

    for (int i = 0; i < n; i++)
    {
        int amount;
        scanf("%d", &amount);
        wynik_degree_sequence.push_back(amount);
        for (int j = 0; j < amount; j++)
        {
            int value;
            scanf("%d", &value);
            graph_map_2[i].push_back(value);
            graph_map[i+1].push_back(value);
            krawedzie++;
        }
        if (amount == 0)
        {
            graph_map_2[i];
            graph_map[i+1];
        }
    }
    krawedzie /= 2;
    wynik_dopelnienie_grafu = (n * (n - 1) / 2) - krawedzie;

    wynik_degree_sequence.sort();


    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < graph_map_2[i].size(); j++)
    //     {
    //         std::cout << graph_map_2[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

void Task::zadania()
{
    std::map<int, bool> spojnosci_visited;
    Stack<int> spojnosci_stack;
    
    std::map<int, char> dwudzielnosc_kolory;
    Stack<int> dwudzielnosc_stack;

    for (auto& pair : graph_map)
    {
        this->liczba_skladowych_spojnosci(pair, spojnosci_visited, spojnosci_stack);
        this->dwudzielnosc_grafu(pair, dwudzielnosc_kolory, dwudzielnosc_stack);
        // this->podgrafy_c4(pair);
    }
}

void Task::liczba_skladowych_spojnosci(const std::pair<int, Vector<int>>& pair, std::map<int, bool>& visited, Stack<int>& stack)
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

void Task::dwudzielnosc_grafu(const std::pair<int, Vector<int>>& pair, std::map<int, char>& kolory, Stack<int>& stack)
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

void Task::output() const
{
    for (size_t i = 0; i < wynik_degree_sequence.size(); i++)
        printf("%d ", wynik_degree_sequence[i]);
    printf("\n");
    printf("%d\n", this->wynik_liczba_skladowych_spojnosci);
    if (this->wynik_dwudzielnosc_grafu)
        printf("T\n");
    else
        printf("F\n");
    for (int i = 0; i < 6; i++)
        printf("?\n");
    printf("%lld\n", wynik_dopelnienie_grafu);
}