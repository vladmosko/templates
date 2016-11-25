// NOT TESTED YET

struct DSU {
  int n;
  vector<int> parent;
  vector<int> sz;
  
  inline void init(int nValue) {
    n = nValue;
    parent.resize(static_cast<unsigned int>(n) + 2);
    sz.assign(static_cast<unsigned int>(n) + 2, 0);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  
  int findSet(int vertex) {
    return vertex == parent[vertex] ? vertex : parent[vertex] = findSet(parent[vertex]);
  }
  
  void mergeSets(int vertex1, int vertex2) {
    vertex1 = findSet(vertex1);
    vertex2 = findSet(vertex2);
    if (vertex1 != vertex2) {
      if (sz[vertex1] < sz[vertex2]) {
        swap(vertex1, vertex2);
      }
      parent[vertex2] = vertex1;
      sz[vertex1] += sz[vertex2];
    }
  }
  
  DSU() {
  
  }
};
