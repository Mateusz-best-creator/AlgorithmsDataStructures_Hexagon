#include "task.h"
#include <stdio.h>
#include "vector.h"
#include "stack.h"

void Task::perform_task()
{
    wynik_degree_sequence.clear();
    if (this->n != -1)
    {
        for (int i = 0; i < this->n; i++)
            graph_map[i].clear();
    }
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
    this->n = n;
    long long krawedzie = 0;
    
    graph_map = new Vector<int>[n];

    for (int i = 0; i < n; i++)
    {
        int amount;
        scanf("%d", &amount);
        wynik_degree_sequence.push_back(amount);
        for (int j = 0; j < amount; j++)
        {
            int value;
            scanf("%d", &value);
            graph_map[i].push_back(value - 1);
            krawedzie++;
        }
        if (amount == 0)
        {
            graph_map[i];
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
    // std::map<int, bool> spojnosci_visited;
    Vector<int> spojnosci_visited;
    Stack<int> spojnosci_stack;
    
    // std::map<int, char> dwudzielnosc_kolory;
    Vector<int> dwudzielnosc_kolory(n, 'e');
    Stack<int> dwudzielnosc_stack;

    for (int i = 0; i < this->n; i++)
    {
        this->liczba_skladowych_spojnosci(i, graph_map[i], spojnosci_visited, spojnosci_stack);
        this->dwudzielnosc_grafu(i, graph_map[i], dwudzielnosc_kolory, dwudzielnosc_stack);
        // this->podgrafy_c4(pair);
    }
}

void Task::liczba_skladowych_spojnosci(int node_index, Vector<int>& node_values, Vector<int>& visited, Stack<int>& stack)
{
    if (!visited.contain(node_index))
    {
        stack.push(node_index);
        while (!stack.empty())
        {
            int stack_node = stack.top();
            stack.pop();
            if (visited.contain(stack_node))
                continue;
            visited.push_back(stack_node);
            for (int i = 0; i < graph_map[stack_node].size(); i++)
            {
                int neighbor = graph_map[stack_node][i];
                if (!visited.contain(neighbor))
                    stack.push(neighbor);
            }
        }
        wynik_liczba_skladowych_spojnosci++;
    }
}

void Task::dwudzielnosc_grafu(int node_index, Vector<int>& node_values, Vector<int>& kolory, Stack<int>& stack)
{
    if (kolory[node_index] == 'e')
    {
        stack.push(node_index);
        kolory[node_index] = czerwony;

        while (!stack.empty())
        {
            int stack_node = stack.top();
            stack.pop();
            char obecny_kolor = kolory[stack_node];
            char przeciwny_kolor = (obecny_kolor == czerwony) ? niebieski : czerwony;

            for (int i = 0; i < graph_map[stack_node].size(); i++)
            {
                int neighbor = graph_map[stack_node][i];
                if (kolory[neighbor] == 'e')
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