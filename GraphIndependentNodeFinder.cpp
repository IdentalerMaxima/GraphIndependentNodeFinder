    #include <iostream>
    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <queue>
    #include <unordered_set>
    #include <fstream>

    void add_edge(std::unordered_map<std::string, std::unordered_set<std::string>>& graph,
        std::unordered_map<std::string, int>& in_degree,
        const std::string& from, const std::string& to) {
        graph[from].insert(to);
        in_degree[to]++;

        if (in_degree.find(from) == in_degree.end()) {
            in_degree[from] = 0;
        }
    }

    void display_graph(const std::unordered_map<std::string, std::unordered_set<std::string>>& graph) {
        for (const auto& node : graph) {
            std::cout << "Node " << node.first << " has edges to: ";
            for (const auto& edge : node.second) {
                std::cout << edge << " ";
            }
            std::cout << std::endl;
        }
    }

    void remove_independent_nodes(std::unordered_map<std::string, std::unordered_set<std::string>>& graph,
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

    void read_edges_from_console(std::unordered_map<std::string, std::unordered_set<std::string>>& graph,
        std::unordered_map<std::string, int>& in_degree) {
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
    }

    void read_edges_from_file(const std::string& filename,
        std::unordered_map<std::string, std::unordered_set<std::string>>& graph,
        std::unordered_map<std::string, int>& in_degree) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string from, to;
            if (iss >> from >> to) {
                add_edge(graph, in_degree, from, to);
            }
            else {
                std::cerr << "Invalid input format in file. Use 'from to' format." << std::endl;
            }
        }

        infile.close();
    }

    int main() {
        std::unordered_map<std::string, std::unordered_set<std::string>> graph;
        std::unordered_map<std::string, int> in_degree;

        int input_method;
        std::cout << "Select input method (1 = Console, 2 = File): ";
        std::cin >> input_method;
        std::cin.ignore();  //Ignore the newline left by std::cin

        if (input_method == 1) {
            read_edges_from_console(graph, in_degree);
        }
        else if (input_method == 2) {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            read_edges_from_file(filename, graph, in_degree);
        }
        else {
            std::cerr << "Invalid input method selected." << std::endl;
            return 1;
        }

        //std::cout << "Original graph:" << std::endl;
        //display_graph(graph);

        remove_independent_nodes(graph, in_degree);

        return 0;
    }
