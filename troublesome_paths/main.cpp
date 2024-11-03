#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

const bool is_debug = false;

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
  }

  return res;
}
std::pair<int, int> to_pair(int first, int second) {
  std::pair<int, int> res;
  res.first = first;
  res.second = second;
  return res;
}
std::pair<int, int> get_coordinates(int index, int rows, int columns) {
  std::pair<int, int> res;
  // Order doesn't matter as long as it's the same for all nodes
  res.second = index % columns;
  res.first = (index - (index % columns)) / columns;
  return res;
}
int get_distance(int index1, int index2, int rows, int columns) {
  std::pair<int, int> p1, p2;
  p1 = get_coordinates(index1, rows, columns);
  p2 = get_coordinates(index2, rows, columns);
  return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}


// For the priority queue
struct DistanceComparator {
  bool operator()(std::pair<int, int> p1, std::pair<int, int> p2) { return p1.first < p2.first; }
};
std::vector<int> astar(std::vector<Arc>* graph, int rows, int columns, int arcs, int from, int to) {
  bool* visited = new bool[rows * columns];

  int* distances_heuristic = new int[rows * columns];

  int* distances = new int[rows * columns];

  // Used for getting the path after finding the solution
  int* came_from = new int[rows * columns];

  for(int i = 0; i < rows * columns; ++i) {
    visited[i] = false; 
    distances_heuristic[i] = get_distance(to, i, rows, columns);
    distances[i] = -1;
    came_from[i] = -1;
  }
  
  // PrioQ has pairs containing two values:
  // 1. Sum of distance and expected distance
  // 2. Node index
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, DistanceComparator> q;
  visited[from] = true;
  distances[from] = 0;
  q.push(to_pair(distances_heuristic[from] + 0, from));
  while(!q.empty()) {
    std::pair<int, int> current_pair = q.top();
    int current = current_pair.second;
    int current_dist = current_pair.first;
    for(auto i : graph[current]) {
      int destination = i.dest, weight = i.weight;
      if(!visited[destination]) {
        visited[destination] = true;
        came_from[destination] = current;
        distances[destination] = distances[current] + weight;
        q.push(to_pair(distances_heuristic[destination] + distances[destination], destination));
      }
    }
    q.pop();
  }

  // Generating the solution
  std::vector<int> res;
  res.clear();
  int current = to;
  while(current != -1) {
    res.push_back(current);
    current = came_from[current];
  }

  if(is_debug) {
    std::cout << "Camefrom:\n";
    for(int i = 0; i < rows * columns; ++i) {
      std::cout << "\t" << i << ": " << came_from[i] << "\n";
    }
  }

  delete visited;
  delete distances_heuristic;
  delete distances;
  delete came_from;

  return res;
}

void display_elements(std::vector<int> v, bool skip_last = false) {
  // It is important to skip the last element from the first path, as it'd be an overlap otherwise
  while(!v.empty()) {
    if(!skip_last || v.size() != 1)
      std::cout << v.back() << " ";
    v.pop_back();
  }
}

int main() {

  int rows, columns, arcs;
  std::vector<Arc>* graph = read_nodes(&rows, &columns, &arcs);

  int start_point = 0;
  int middle_point = rows - 1;
  int end_point = middle_point * columns;
  if(is_debug) std::cout << "Start: " << start_point
            << "\nVia: " << middle_point
            << "\nTo: " << end_point << "\n";

  std::vector<int> path1 = astar(graph, rows, columns, arcs, start_point, middle_point);
  std::vector<int> path2 = astar(graph, rows, columns, arcs, middle_point, end_point);

  // -1 because the middle element is doubled
  int total_length = path1.size() + path2.size() - 1;

  std::cout << total_length << "\n";
  if(is_debug) std::cout<< "Path 1: ";
  display_elements(path1, true);
  if(is_debug) std::cout << "\nPath 2: ";
  display_elements(path2);

  delete graph;
  return 0;
}
