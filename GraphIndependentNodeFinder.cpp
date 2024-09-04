#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

void add_edge(std::unordered_map<std::string, std::vector<std::string>>& graph,
    std::unordered_map<std::string, int>& in_degree,
    const std::string& from, const std::string& to) {
    graph[from].push_back(to);

    // Increment in-degree for the 'to' node
    in_degree[to]++;

    // Ensure 'from' node is in the in-degree map (if it's not already there)
    if (in_degree.find(from) == in_degree.end()) {
        in_degree[from] = 0;
    }

    // Ensure 'to' node is in the graph (if it's not already there)
    if (graph.find(to) == graph.end()) {
        graph[to] = std::vector<std::string>();
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

void display_nodes_without_dependencies(const std::unordered_map<std::string, int>& in_degree) {
    std::cout << "Independent nodes:" << std::endl;
    std::cout << "1: ";
    for (const auto& node : in_degree) {
        if (node.second == 0) {
            std::cout << node.first << std::endl;
        }
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

    display_graph(graph);
    display_nodes_without_dependencies(in_degree);

    return 0;
}
