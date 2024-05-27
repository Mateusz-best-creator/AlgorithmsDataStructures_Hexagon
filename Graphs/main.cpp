#include "task.h"
#include <stdio.h>

int main()
{
    int k;
    scanf("%d", &k);
    Task task;
    for (int i = 0; i < k; i++)
        task.perform_task();   
}