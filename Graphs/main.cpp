#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "task.hpp"

int main()
{
    int k;
    std::cin >> k;
    Task task;
    for (int i = 0; i < k; i++)
        task.perform_task();   
}