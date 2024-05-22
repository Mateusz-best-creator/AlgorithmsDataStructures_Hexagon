#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

void task();

int main()
{
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++)
        task();   
}

void task()
{
    int n;
    std::cin >> n;
    std::map<int, std::vector<int>> map;
    std::vector<int> degree_sequence;
    for (int i = 0; i < n; i++)
    {
        int amount;
        std::cin >> amount;
        degree_sequence.push_back(amount);
        for (int j = 0; j < amount; j++)
        {
            int value;
            std::cin >> value;
            map[i+1].push_back(value);
        }
    }

    std::sort(degree_sequence.begin(), degree_sequence.end(), [](int a, int b){
        return a > b;
    });
    for (const int& v : degree_sequence)
        std::cout << v << " ";
    std::cout << std::endl;

    // for (auto [key, value] : map)
    // {
    //     std::cout << key << ": ";
    //     for (auto v : value)
    //         std::cout << v << " ";
    //     std::cout << std::endl;
    // }


}