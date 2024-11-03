#include <iostream>
#include <vector>

struct Arc {
  int weight;
  int dest;
};

std::vector<Arc>* read_nodes(int* number_of_nodes) {
  // Return type: list of lists of arcs
  int rows, columns, arcs;
  std::vector<Arc>* res;
  std::cin >> rows >> columns >> arcs;
  int nodes = rows * columns;
  *number_of_nodes = nodes;
  res = new std::vector<Arc>[nodes];
  for(int i = 0; i < nodes; ++i) {
    res[i].clear();
  }
  for(int i = 0; i < arcs; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;

    // Arc creation
    Arc tmp;
    tmp.weight = weight;
    tmp.dest = to;

    res[from].push_back(tmp);
  }

  return res;
}

int main() {

  int number_of_nodes = 0;
  std::vector<Arc>* graph = read_nodes(&number_of_nodes);

  delete graph;
  return 0;
}
