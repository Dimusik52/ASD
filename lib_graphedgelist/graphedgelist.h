// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_GRAPHEDGELIST_GRAPHEDGELIST_H_
#define LIB_GRAPHEDGELIST_GRAPHEDGELIST_H_

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

template <class T>
class GraphEdgeList {
  struct Edge {
    T from;
    T to;
    int weight;

    Edge(const T& f, const T& t, int w = 1) : from(f), to(t), weight(w) {}

    bool operator==(const Edge& other) const {
      return from == other.from && to == other.to && weight == other.weight;
    }

    bool operator==(const std::pair<T, T>& edge) const {
      return from == edge.first && to == edge.second;
    }
  };

  std::vector<Edge> _edges;
  std::vector<T> _vertices;
  bool _isOriented;
  bool _isWeighted;

 public:
  GraphEdgeList();
  GraphEdgeList(bool isOriented, bool isWeighted = true);
  GraphEdgeList(std::vector<std::tuple<T, T, int>> edges,
                bool isOriented = false);
  GraphEdgeList(std::vector<std::pair<T, T>> edges, bool isOriented = false,
                bool isWeighted = false);

  bool vertexExists(const T& name) const;
  void addVertex(const T& name);
  void deleteVertex(const T& name);

  void addEdge(const T& from, const T& to, int weight = 1);
  void addEdge(const std::pair<T, T>& edge, int weight = 1);
  void deleteEdge(const T& from, const T& to);
  void updateWeight(const T& from, const T& to, int newWeight);

  size_t vertexCount() const { return _vertices.size(); }
  size_t edgeCount() const { return _edges.size(); }

  int getWeight(const T& from, const T& to) const;
  std::vector<T> getAllVertices() const { return _vertices; }
  std::vector<std::pair<T, int>> getNeighbors(const T& vertex) const;

  bool edgeExists(const T& from, const T& to) const;
  bool isOriented() const { return _isOriented; }
  bool isWeighted() const { return _isWeighted; }

  void setOriented(bool oriented) { _isOriented = oriented; }
  void setWeighted(bool weighted) { _isWeighted = weighted; }

  void printGraph() const;
};

template <class T>
GraphEdgeList<T>::GraphEdgeList() : _isOriented(false), _isWeighted(true) {}

template <class T>
GraphEdgeList<T>::GraphEdgeList(bool isOriented, bool isWeighted)
    : _isOriented(isOriented), _isWeighted(isWeighted) {}

template <class T>
GraphEdgeList<T>::GraphEdgeList(std::vector<std::tuple<T, T, int>> edges,
                                bool isOriented)
    : _isOriented(isOriented), _isWeighted(true) {
  for (size_t i = 0; i < edges.size(); i++) {
    const T& from = std::get<0>(edges[i]);
    const T& to = std::get<1>(edges[i]);
    int weight = std::get<2>(edges[i]);
    addEdge(from, to, weight);
  }
}

template <class T>
GraphEdgeList<T>::GraphEdgeList(std::vector<std::pair<T, T>> edges,
                                bool isOriented, bool isWeighted)
    : _isOriented(isOriented), _isWeighted(isWeighted) {
  for (size_t i = 0; i < edges.size(); i++) {
    addEdge(edges[i].first, edges[i].second, 1);
  }
}

template <class T>
bool GraphEdgeList<T>::vertexExists(const T& name) const {
  for (size_t i = 0; i < _vertices.size(); i++) {
    if (_vertices[i] == name) {
      return true;
    }
  }
  return false;
}

template <class T>
void GraphEdgeList<T>::addVertex(const T& name) {
  if (!vertexExists(name)) {
    _vertices.push_back(name);
  }
}

template <class T>
void GraphEdgeList<T>::deleteVertex(const T& name) {
  for (size_t i = 0; i < _edges.size();) {
    if (_edges[i].from == name || _edges[i].to == name) {
      for (size_t j = i; j < _edges.size() - 1; j++) {
        _edges[j] = _edges[j + 1];
      }
      _edges.pop_back();
    } else {
      i++;
    }
  }

  for (size_t i = 0; i < _vertices.size();) {
    if (_vertices[i] == name) {
      for (size_t j = i; j < _vertices.size() - 1; j++) {
        _vertices[j] = _vertices[j + 1];
      }
      _vertices.pop_back();
    } else {
      i++;
    }
  }
}

template <class T>
bool GraphEdgeList<T>::edgeExists(const T& from, const T& to) const {
  for (size_t i = 0; i < _edges.size(); i++) {
    if (_edges[i].from == from && _edges[i].to == to) {
      return true;
    }
  }
  return false;
}

template <class T>
void GraphEdgeList<T>::addEdge(const T& from, const T& to, int weight) {
  if (!_isWeighted && weight != 1) {
    throw std::runtime_error("Graph is not weighted, weight must be 1");
  }

  addVertex(from);
  addVertex(to);

  if (edgeExists(from, to)) {
    throw std::runtime_error("Edge already exists");
  }

  _edges.push_back(Edge(from, to, weight));

  if (!_isOriented) {
    _edges.push_back(Edge(to, from, weight));
  }
}

template <class T>
void GraphEdgeList<T>::addEdge(const std::pair<T, T>& edge, int weight) {
  addEdge(edge.first, edge.second, weight);
}

template <class T>
void GraphEdgeList<T>::deleteEdge(const T& from, const T& to) {
  for (size_t i = 0; i < _edges.size(); i++) {
    if (_edges[i].from == from && _edges[i].to == to) {
      for (size_t j = i; j < _edges.size() - 1; j++) {
        _edges[j] = _edges[j + 1];
      }
      _edges.pop_back();
      break;
    }
  }

  if (!_isOriented) {
    for (size_t i = 0; i < _edges.size(); i++) {
      if (_edges[i].from == to && _edges[i].to == from) {
        for (size_t j = i; j < _edges.size() - 1; j++) {
          _edges[j] = _edges[j + 1];
        }
        _edges.pop_back();
        break;
      }
    }
  }
}

template <class T>
void GraphEdgeList<T>::updateWeight(const T& from, const T& to, int newWeight) {
  if (!_isWeighted) {
    throw std::runtime_error("Graph is not weighted");
  }

  for (size_t i = 0; i < _edges.size(); i++) {
    if (_edges[i].from == from && _edges[i].to == to) {
      _edges[i].weight = newWeight;
      break;
    }
  }

  if (!_isOriented) {
    for (size_t i = 0; i < _edges.size(); i++) {
      if (_edges[i].from == to && _edges[i].to == from) {
        _edges[i].weight = newWeight;
        break;
      }
    }
  }
}

template <class T>
int GraphEdgeList<T>::getWeight(const T& from, const T& to) const {
  if (!_isWeighted) return 1;

  for (size_t i = 0; i < _edges.size(); i++) {
    if (_edges[i].from == from && _edges[i].to == to) {
      return _edges[i].weight;
    }
  }

  throw std::runtime_error("Edge not found");
}

template <class T>
std::vector<std::pair<T, int>> GraphEdgeList<T>::getNeighbors(
    const T& vertex) const {
  std::vector<std::pair<T, int>> neighbors;

  for (size_t i = 0; i < _edges.size(); i++) {
    if (_edges[i].from == vertex) {
      neighbors.push_back({_edges[i].to, _edges[i].weight});
    }
  }

  return neighbors;
}

template <class T>
void GraphEdgeList<T>::printGraph() const {
  std::cout << "Vertices: ";
  for (size_t i = 0; i < _vertices.size(); i++) {
    std::cout << _vertices[i];
    if (i != _vertices.size() - 1) std::cout << ", ";
  }
  std::cout << std::endl;

  std::cout << "Edges: ";
  for (size_t i = 0; i < _edges.size(); i++) {
    std::cout << "(" << _edges[i].from << ", " << _edges[i].to;
    if (_isWeighted) {
      std::cout << ", " << _edges[i].weight;
    }
    std::cout << ")";
    if (i != _edges.size() - 1) std::cout << " -> ";
  }
  std::cout << std::endl;
}

#endif  // LIB_GRAPHEDGELIST_GRAPHEDGELIST_H_