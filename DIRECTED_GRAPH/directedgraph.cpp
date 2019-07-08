#include "directedgraph.hpp"

template<typename T>
DirectedGraph<T>::Vertices DirectedGraph<T>::CGetSuccessors(DirectedGraph<T>::Vertex vertex){
    Vertices successors;
    auto range = graph.equal_range(vertex);
    for (auto it = range.first; it != range.second; ++it){
        successors.insert(it -> second);
    }
    return successors;
};

template<typename T>
DirectedGraph<T>::Vertices DirectedGraph<T>::CGetPredecessors(DirectedGraph<T>::Vertex vertex){
    Vertices predecessors;
    for (auto it = graph.cbegin(); it != graph.cend(); ++it){
        if (it->second == vertex)
            predecessors.insert(it->first)
    }
    return predecessors;
}

template<typename T>
DirectedGraph<T>::Vertices DirectedGraph<T>::CGetNeighbour(Vertex vertex){
    Vertices neighbour;
    for (auto it = graph.cbegin(); it != graph.cend(); ++it){
        if (it->first == vertex)
            predecessors.insert(it->second)
        elif (it->second == vertex)
            predecessors.insert(it->first)
    }
    return neighbour;
}

template<typename T>
T DirectedGraph<T>::CGetContent(DirectedGraph<T>::Vertex vertex){
    return contents.at(vertex);
}

template<typename T>
void DirectedGraph<T>::AddVertex(DirectedGraph<T>::Vertex vertex, T content, DirectedGraph<T>::Vertices successors, DirectedGraph<T>::Vertices predecessors){
    content.insert({vertex, content});
    for (auto it_succ = successors.cbegin(); it_succ != successors.cend(); ++it_succ){
        graph.insert({vertex, *it_succ});
    }
    for (auto it_pred = predecessors.cbegin(); it_pred != predecessors.cend(); ++it_pred){
        graph.inset({*it_pred, vertex});
    }
}