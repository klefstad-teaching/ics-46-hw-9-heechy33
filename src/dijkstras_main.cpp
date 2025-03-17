#include "dijkstras.h"

string get_arg(int argc, char *argv[], string def) {
    if (argc > 1) {
        return string(argv[1]);
    }
    return def;
}

int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "src/large.txt");
    Graph G;
    file_to_graph(filename, G);
    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (size_t i = 0; i < distances.size(); ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

}