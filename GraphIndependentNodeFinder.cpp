#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

void add_edge(std::unordered_map<std::string, std::vector<std::string>>& graph,
    std::unordered_map<std::string, int>& in_degree,
    const std::string& from, const std::string& to) {
    graph[from].push_back(to);
    in_degree[to]++;

    if (in_degree.find(from) == in_degree.end()) {
        in_degree[from] = 0;
    }
}

void display_graph(const std::unordered_map<std::string, std::vector<std::string>>& graph) {
    for (const auto& node : graph) {
        std::cout << "Node " << node.first << " has edges to: ";
        for (const auto& edge : node.second) {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
    }
}

void remove_independent_nodes(std::unordered_map<std::string, std::vector<std::string>>& graph,
    std::unordered_map<std::string, int>& in_degree) {
    int round = 1;

    while (true) {
        std::queue<std::string> to_remove;
        for (const auto& node : in_degree) {
            if (node.second == 0) {
                to_remove.push(node.first);
            }
        }

        if (to_remove.empty()) {
            break;  // No more independent nodes to remove
        }

        std::cout << "Independent nodes " << round << ": ";
        while (!to_remove.empty()) {
            std::string node = to_remove.front();
            to_remove.pop();

            std::cout << node << " ";

            for (const auto& neighbor : graph[node]) {
                in_degree[neighbor]--;
            }

            graph.erase(node);
            in_degree.erase(node);
        }

        std::cout << std::endl;
        round++;
    }
}

int main() {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> in_degree;

    std::cout << "Enter edges (format: from to), end with an empty line:" << std::endl;

    std::string line;

    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string from, to;
        if (iss >> from >> to) {
            add_edge(graph, in_degree, from, to);
        }
        else {
            std::cerr << "Invalid input format. Use 'from to' format." << std::endl;
        }
    }

    std::cout << "Original graph:" << std::endl;
    display_graph(graph);

    remove_independent_nodes(graph, in_degree);

    return 0;
}
