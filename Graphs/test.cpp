

void Task::calculate_eccentricity() 
{
    std::map<int, int> depth;
    std::queue<int> queue;

    for (const auto& outer_pair : graph_map) 
    {
        int current_node = outer_pair.first;
        if (outer_pair.second.empty()) 
        {
            eccentricity.push_back(0);
            continue;
        }

        std::set<int> visited;
        int max_depth = -1;

        queue.push(current_node);
        visited.insert(current_node);
        depth[current_node] = 0;

        while (!queue.empty()) 
        {
            int node = queue.front();
            queue.pop();

            for (int neighbor : graph_map[node]) 
            {
                if (visited.find(neighbor) == visited.end()) 
                {
                    queue.push(neighbor);
                    visited.insert(neighbor);
                    depth[neighbor] = depth[node] + 1;
                    if (depth[neighbor] > max_depth)
                        max_depth = depth[neighbor];
                }
            }
        }
        eccentricity.push_back(max_depth);
    }
}

void Task::components_eccentricity() 
{
    std::map<int, int> depth;
    std::queue<int> queue;
    std::set<int> global_visited;

    // Calculate Eccentricity
    for (const auto& outer_pair : graph_map) 
    {
        int current_node = outer_pair.first;
        if (outer_pair.second.empty()) {
            eccentricity.push_back(0);
            continue;
        }

        std::unordered_set<int> visited;
        int max_depth = -1;

        queue.push(current_node);
        visited.insert(current_node);
        depth[current_node] = 0;

        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();

            for (int neighbor : graph_map[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    queue.push(neighbor);
                    visited.insert(neighbor);
                    depth[neighbor] = depth[node] + 1;
                    if (depth[neighbor] > max_depth)
                        max_depth = depth[neighbor];
                }
            }
        }

        eccentricity.push_back(max_depth);
    }

    // Calculate Number of Connected Components
    for (const auto& pair : graph_map) {
        int start_node = pair.first;

        if (global_visited.find(start_node) != global_visited.end()) {
            continue;
        }

        std::stack<int> stack;
        stack.push(start_node);
        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();
            if (global_visited.find(node) != global_visited.end()) {
                continue;
            }
            global_visited.insert(node);
            for (int neighbor : graph_map[node]) {
                if (global_visited.find(neighbor) == global_visited.end()) {
                    stack.push(neighbor);
                }
            }
        }
        num_of_connected_components++;
    }
}