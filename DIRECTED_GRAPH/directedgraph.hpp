#ifndef DIRECTEDGRAPH_HPP
#define DIRECTEDGRAPH_HPP

#include <unordered_map>
#include <unordered_set>

template<typename T> 
class DirectedGraph{
    public:
    typedef std::size_t Vertex;
    typedef Vertices std::unordered_set<Vertex>;

    DirectedGraph() = default;

    Vertices CGetSuccessors(Vertex vertex);
    Vertices CGetPredecessors(Vertex vertex);
    Vertices CGetNeighbour(Vertex vertex);
    T CGetContent(Vertex vertex);
    void AddVertex(Vertex vertex, T content, Vertices successors, Vertices predecessors);

    private:
    /* Recommend to use"
    std::vector<T> content;
    std::vector<std::unordered_set<Vertex> > successors; */ 
    std::unordered_multimap<Vertex, Vertex> graph;
    std::unordered_map<Vertex, T> contents;
};

#endif