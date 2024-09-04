#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

void add_edge(std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& from, const std::string& to) {
    graph[from].push_back(to);

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

int main() {
    std::unordered_map<std::string, std::vector<std::string>> graph;

    std::cout << "Enter edges (format: from to), end with an empty line:" << std::endl;

    std::string line;

    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string from, to;
        if (iss >> from >> to) {
            add_edge(graph, from, to);
        }
        else {
            std::cerr << "Invalid input format. Use 'from to' format." << std::endl;
        }
    }

    display_graph(graph);

    return 0;
}
