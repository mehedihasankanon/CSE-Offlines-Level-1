# Offline Assignment 5 on Graphs

## Task

Implementation of an undirected, unweighted graph using two representations: an adjacency list (`AdjacencyListGraph.h`) and an adjacency matrix (`AdjacencyMatrixGraph.h`). As per assignment requirements, custom implementation of a linked list (`linkedList.h`) and queue (`queue.h` and `listqueue.h`) has been used.

## Files

- **AdjacencyListGraph.h**: Implements the graph using an adjacency list with a custom doubly-linked list (`linkedList`).
- **AdjacencyMatrixGraph.h**: Implements the graph using an adjacency matrix.
- **linkedList.h**: Custom doubly-linked list for adjacency lists and path storage.
- **queue.h**: The parent queue class
- **listqueue.h**: Custom queue for BFS algorithm.
- **GraphADT.h**: Abstract base class defining the graph interface.
- **GraphTest.cpp**: Test harness (assumed) to verify functionality.

## Features

Both graph implementations support:

- **AddNode(int v)**: Adds a node with ID `v` (positive).
- **AddEdge(int u, int v)**: Adds an undirected edge between nodes `u` and `v`, preventing self-loops and duplicates (in adjacency list).
- **CheckEdge(int u, int v)**: Returns `true` if an edge exists between `u` and `v`.
- **RemoveNode(int v)**: Removes node `v` and its edges.
- **RemoveEdge(int u, int v)**: Removes the edge between `u` and `v`.
- **CheckPath(int u, int v)**: Returns `true` if a path exists from `u` to `v` using BFS.
- **FindShortestPath(int u, int v)**: Prints the shortest path from `u` to `v` (e.g., `1 2 3`) or an error message if no path exists.
- **FindShortestPathLength(int u, int v)**: Returns the number of edges in the shortest path or `-1` if no path exists.
- **GetNeighbors(int u)**: Returns a `linkedList` of node `u`’s neighbors.

## Implementation Details

- **AdjacencyListGraph**:
  - Uses a dynamic array of `linkedList`s for adjacency lists.
  - Resizes dynamically when adding nodes beyond current capacity.
- **AdjacencyMatrixGraph**:
  - Uses a 2D dynamic array for the adjacency matrix.
  - Resizes to accommodate large node IDs.
  - Tracks node existence with a boolean array.
- **BFS Algorithms**:
  - `CheckPath`, `FindShortestPath`, and `FindShortestPathLength` use BFS with a custom `listqueue` for pathfinding.

## Usage

Run the `GraphTest.cpp` file.
