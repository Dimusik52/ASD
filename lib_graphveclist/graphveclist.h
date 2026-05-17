// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_GRAPHVECLIST_GRAPHVECLIST_H_
#define LIB_GRAPHVECLIST_GRAPHVECLIST_H_

#include <utility>
#include <vector>

#include "../lib_list/list.h"

template <class T>
class GraphVecList {
  struct Edge {
    const T* to;
    int weight;

    Edge(const T& to, int w = 1) : to(&to), weight(w) {}

    /*bool operator==(const Edge& other) const {
      return to == other.to && weight == other.weight;
    }

    bool operator==(const T& vertexName) const { return to == vertexName; }*/
  };

  struct Vertex {
    T name;
    List<Edge> edges;

    Vertex(const T& name) : name(name) {}

    bool operator==(const Vertex& other) const { return name == other.name; }

    bool operator==(const T& vertexName) const { return name == vertexName; }
  };
  std::vector<Vertex> _data;
  bool _isOriented;
  bool _isWeighted;

 public:
  GraphVecList();
  GraphVecList(bool isOriented, bool isWeighted = true);
  GraphVecList(std::vector<std::tuple<T, T, int>> edges,
               bool isOriented = false);
  GraphVecList(std::vector<std::pair<T, T>> edges, bool isOriented = false,
               bool isWeighted = false);

  int findVertexPosition(const T& name) const;
  bool vertexExists(const T& name) const {
    return findVertexPosition(name) != -1;
  }

  void addVertex(const T& name);
  void deleteVertex(const T& name);

  void addEdge(const T& from, const T& to, int weight = 1);
  void addEdge(const std::pair<T, T>& edge, int weight = 1);
  void deleteEdge(const T& from, const T& to);
  void updateWeight(const T& from, const T& to, int newWeight);

  size_t vertexCount() const { return _data.size(); }
  size_t edgeCount() const;
  int getWeight(const T& from, const T& to) const;
  std::vector<T> getAllVertices() const;
  std::vector<std::pair<T, int>> getNeighbors(const T& vertex) const;

  bool edgeExists(const T& from, const T& to) const;
  bool isOriented() const { return _isOriented; }
  bool isWeighted() const { return _isWeighted; }

  void setOriented(bool oriented) { _isOriented = oriented; }
  void setWeighted(bool weighted) { _isWeighted = weighted; }

  void printGraph() const;
};

template <class T>
GraphVecList<T>::GraphVecList() : _isOriented(false), _isWeighted(true) {
  _data.reserve(100000);
}

template <class T>
GraphVecList<T>::GraphVecList(bool isOriented, bool isWeighted)
    : _isOriented(isOriented), _isWeighted(isWeighted) {
  _data.reserve(100000);
}

template <class T>
GraphVecList<T>::GraphVecList(std::vector<std::tuple<T, T, int>> edges,
                              bool isOriented)
    : _isOriented(isOriented), _isWeighted(true) {
  _data.reserve(100000);
  for (const auto& edge : edges) {
    const T& from = std::get<0>(edge);
    const T& to = std::get<1>(edge);

    if (!vertexExists(from)) {
      _data.emplace_back(from);
    }
    if (!vertexExists(to)) {
      _data.emplace_back(to);
    }
  }

  for (const auto& edge : edges) {
    const T& from = std::get<0>(edge);
    const T& to = std::get<1>(edge);
    int weight = std::get<2>(edge);
    addEdge(from, to, weight);
  }
}

template <class T>
GraphVecList<T>::GraphVecList(std::vector<std::pair<T, T>> edges,
                              bool isOriented, bool isWeighted)
    : _isOriented(isOriented), _isWeighted(isWeighted) {
  _data.reserve(100000);
  for (const auto& edge : edges) {
    if (!vertexExists(edge.first)) {
      _data.emplace_back(edge.first);
    }
    if (!vertexExists(edge.second)) {
      _data.emplace_back(edge.second);
    }
  }

  for (const auto& edge : edges) {
    addEdge(edge.first, edge.second, 1);
  }
}

template <class T>
int GraphVecList<T>::findVertexPosition(const T& name) const {
  for (size_t i = 0; i < _data.size(); i++) {
    if (_data[i].name == name) {
      return i;
    }
  }
  return -1;
}

template <class T>
void GraphVecList<T>::addVertex(const T& name) {
  if (!vertexExists(name)) {
    _data.push_back(name);
  }
}

template <class T>
void GraphVecList<T>::deleteVertex(const T& name) {
  int pos = findVertexPosition(name);
  if (pos == -1) return;
  for (auto& vertex : _data) {
    for (auto it = vertex.edges.begin(); it != vertex.edges.end(); ++it) {
      if (*((*it).to) == name) {
        vertex.edges.erase(it.get_node());
        break;
      }
    }
  }
  _data.erase(_data.begin() + pos);
}

template <class T>
void GraphVecList<T>::addEdge(const T& from, const T& to, int weight) {
  if (!_isWeighted && weight != 1) {
    throw std::runtime_error("Graph is not weighted, weight must be 1");
  }

  addVertex(from);
  addVertex(to);

  int fromPos = findVertexPosition(from);
  int toPos = findVertexPosition(to);

  if (fromPos == -1 || toPos == -1) {
    throw std::runtime_error("Vertex not found");
  }

  if (edgeExists(from, to)) {
    throw std::runtime_error("Edge already exists");
  }

  _data[fromPos].edges.push_back(Edge(_data[toPos].name, weight));

  if (!_isOriented) {
    _data[toPos].edges.push_back(Edge(_data[fromPos].name, weight));
  }
}

template <class T>
void GraphVecList<T>::addEdge(const std::pair<T, T>& edge, int weight) {
  addEdge(edge.first, edge.second, weight);
}

template <class T>
void GraphVecList<T>::deleteEdge(const T& from, const T& to) {
  int fromPos = findVertexPosition(from);
  if (fromPos == -1) return;

  for (auto it = _data[fromPos].edges.begin(); it != _data[fromPos].edges.end();
       ++it) {
    if ((*it).to == to) {
      _data[fromPos].edges.erase(it.get_node());
      break;
    }
  }

  if (!_isOriented) {
    int toPos = findVertexPosition(to);
    if (toPos != -1) {
      for (auto it = _data[toPos].edges.begin(); it != _data[toPos].edges.end();
           ++it) {
        if ((*it).to == from) {
          _data[toPos].edges.erase(it.get_node());
          break;
        }
      }
    }
  }
}

template <class T>
void GraphVecList<T>::updateWeight(const T& from, const T& to, int newWeight) {
  if (!_isWeighted) {
    throw std::runtime_error("Graph is not weighted");
  }

  int fromPos = findVertexPosition(from);
  if (fromPos == -1) return;

  auto& fromEdges = _data[fromPos].edges;
  for (auto it = fromEdges.begin(); it != fromEdges.end(); ++it) {
    if ((*it).to == to) {
      (*it).weight = newWeight;
      break;
    }
  }

  if (!_isOriented) {
    int toPos = findVertexPosition(to);
    if (toPos != -1) {
      auto& toEdges = _data[toPos].edges;
      for (auto it = toEdges.begin(); it != toEdges.end(); ++it) {
        if (*((*it).to) == from) {
          (*it).weight = newWeight;
          break;
        }
      }
    }
  }
}

template <class T>
bool GraphVecList<T>::edgeExists(const T& from, const T& to) const {
  int fromPos = findVertexPosition(from);
  if (fromPos == -1) return false;

  const auto& edges = _data[fromPos].edges;
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    if (*((*it).to)== to) {
      return true;
    }
  }
  return false;
}

template <class T>
int GraphVecList<T>::getWeight(const T& from, const T& to) const {
  if (!_isWeighted) return 1;

  int fromPos = findVertexPosition(from);
  if (fromPos == -1) {
    throw std::runtime_error("Vertex not found");
  }

  const auto& edges = _data[fromPos].edges;
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    if ((*it).to == to) {
      return (*it).weight;
    }
  }

  throw std::runtime_error("Edge not found");
}

template <class T>
std::vector<T> GraphVecList<T>::getAllVertices() const {
  std::vector<T> result;
  for (const auto& vertex : _data) {
    result.push_back(vertex.name);
  }
  return result;
}

template <class T>
std::vector<std::pair<T, int>> GraphVecList<T>::getNeighbors(
    const T& vertex) const {
  std::vector<std::pair<T, int>> neighbors;
  int pos = findVertexPosition(vertex);
  if (pos == -1) return neighbors;

  const auto& edges = _data[pos].edges;
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    neighbors.push_back({*(it->to), (*it).weight});
  }
  return neighbors;
}

template <class T>
size_t GraphVecList<T>::edgeCount() const {
  size_t count = 0;
  for (const auto& vertex : _data) {
    for (auto it = vertex.edges.begin(); it != vertex.edges.end(); ++it) {
      count++;
    }
  }

  if (!_isOriented) {
    count /= 2;
  }
  return count;
}

template <class T>
void GraphVecList<T>::printGraph() const {
  for (const auto& vertex : _data) {
    std::cout << vertex.name << " -> ";
    bool first = true;
    for (auto it = vertex.edges.begin(); it != vertex.edges.end(); ++it) {
      if (!first) std::cout << ", ";
      std::cout << *((*it).to);
      if (_isWeighted) {
        std::cout << "(" << (*it).weight << ")";
      }
      first = false;
    }
    std::cout << std::endl;
  }
}

#endif