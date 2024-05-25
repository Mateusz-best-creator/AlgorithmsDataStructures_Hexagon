#include <iostream>
#include "task.hpp"

int main()
{
    std::ios_base::sync_with_stdio(false);
    int k;
    std::cin >> k;
    Task task;
    for (int i = 0; i < k; i++)
        task.perform_task();   
}