void Task::components_bipartite_calculate_eccentricity(std::map<int, int>& depth, std::queue<int>& queue, std::map<int, Color>& node_colors, 
std::set<int> visited, const std::pair<int, std::vector<int>>& pair) 
{
    int current_node = pair.first;
    if (pair.second.empty()) 
    {
        eccentricity.push_back(0);
        visited.insert(current_node);
        return;
    }

    int max_depth = -1;

    queue.push(current_node);
    visited.insert(current_node);
    depth[current_node] = 0;

    if (visited.find(current_node) == visited.end())
    {
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