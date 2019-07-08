# DIRECTED GRAPH

You have to develop the template class `template <typename T> DirectedGraph` for storing data organized as a directed graph. The template `T` identifies the type of the object associated with each vertex, i.e., each vertex stores
a `T` object. The aim is to use the `template <typename T> DirectedGraph` to store data of Twitter or Instagram.

In particular you have to:

1. Provide the definition of the data structures to store vertices, the associated `vertex_content` (of type T) and edges. The data structure must be selected so that the worst case complexity of `DirectedGraph::CGetSuccessor` and of `DirectedGraph::CGetContent` is constant.

2. Provide the implementation of `DirectedGraph::CGetSuccessors(Vertex vertex)`: it returns the successors of vertex. Its worst case complexity must be constant.

3. Provide the implementation of `DirectedGraph::CGetPredecessors(Vertex vertex)`: it returns the predecessors of vertex.

4. Provide the implementation of `DirectedGraph::CGetNeighbour(Vertex vertex)`: it returns the union of predecessors and of successors of vertex.

5. Provide the implementation of `DirectedGraph::CGetContent(Vertex vertex)1`: it returns the object associated with vertex.

6. Provide the implementation of: `DirectedGraph::AddVertex(vertex_content content, ... successors, ... predecessors)` which adds a new vertex to the graph.

7. Provide the worst case complexity of `DirectedGraph::CGetNeighbour` and of `DirectedGraph::AddVertex`.

Suggestions:
+ You can use non-negative integers to identify the vertices (i.e., `typedef std::size_t Vertex`).
+ You can assume that vertices and edges are never removed from the graph.
+ Member functions can call other member functions to avoid code duplication.
+ Avoid storing duplicated information.