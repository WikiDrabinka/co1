#include <iostream>
#include <vector>

struct Arc {
  int weight;
  int dest;
};
std::vector<Arc>* read_nodes(int* num_rows, int* num_cols, int* num_arcs) {
  // Return type: list of lists of arcs
  int rows, columns, arcs;
  std::vector<Arc>* res;
  std::cin >> rows >> columns >> arcs;
  int nodes = rows * columns;

  /*
    * M -> column
    * N -> row
    * A -> number of arcs
    */

  *num_rows = rows;
  *num_cols = columns;
  *num_arcs = arcs;

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
    std::cout << from << "\n";
  }

  return res;
}

std::pair<int, int> get_coordinates(int index, int rows, int columns) {
  std::pair<int, int> res;
  // Order doesn't matter as long as it's the same for all nodes
  res.second = index % columns;
  res.first = (index - (index % columns)) / columns;
  return res;
}
int get_distance_squared(int index1, int index2, int rows, int columns) {
  std::pair<int, int> p1, p2;
  p1 = get_coordinates(index1, rows, columns);
  p2 = get_coordinates(index2, rows, columns);
  return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

std::vector<int> astar(std::vector<Arc>* graph, int rows, int columns, int arcs, int from, int to) {
  std::vector<int> res;
  res.clear();

  bool* visited;
  visited = new bool[rows * columns];
  for(int i = 0; i < rows * columns; ++i) { visited[i] = false; }
}

int main() {

  int rows, columns, arcs;
  std::vector<Arc>* graph = read_nodes(&rows, &columns, &arcs);

  int start_point = 0;
  int middle_point = rows - 1;
  int end_point = middle_point * columns;

  for(int i = 0; i < arcs; ++i) {
    std::cout << get_coordinates(i, rows, columns).first << ", " << get_coordinates(i, rows, columns).second << "\n";
  }

  delete graph;
  return 0;
}
