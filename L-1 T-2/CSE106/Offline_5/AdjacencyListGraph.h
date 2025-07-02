#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"

class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members

    int maxNodeIndex = 0;
    bool *nodeExists = nullptr;

    YourListType *adjList = nullptr;

public:
    void AddNode(int v) override
    {
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if (v > maxNodeIndex)
        {
            bool *newArr = new bool[v + 1];

            for (int i = 0; i <= maxNodeIndex; i++)
                newArr[i] = nodeExists[i];
            for (int i = maxNodeIndex + 1; i <= v; i++)
                newArr[i] = false;

            delete[] nodeExists;
            nodeExists = newArr;
            nodeExists[v] = true;

            YourListType *newAdjList = new linkedList[v + 1];
            for (int i = 0; i <= maxNodeIndex; i++)
            {
                init(&newAdjList[i]);
                copy(&adjList[i], &newAdjList[i]);
                free_list(&adjList[i]);
            }

            for (int i = maxNodeIndex + 1; i <= v; i++)
            {
                init(&newAdjList[i]);
            }

            delete[] adjList;
            adjList = newAdjList;
        }
        else
        {
            nodeExists[v] = true;
        }
    }

    void AddEdge(int u, int v) override
    {
        // TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);

        append(u, &adjList[v]);
        append(v, &adjList[u]);
    }

    bool CheckEdge(int u, int v) const override
    {
        // TODO: Check whether there is an edge between two nodes u and v
        if (u < 0 || v < 0 || u > maxNodeIndex || v > maxNodeIndex || !nodeExists[u] || !nodeExists[v])
        {
            return false;
        }
        return is_present(u, &adjList[v]) && is_present(v, &adjList[u]);
    }

    void RemoveNode(int v) override
    {
        // TODO: Remove a node.
        if (v < 0 || v > maxNodeIndex || !nodeExists[v])
            return;

        nodeExists[v] = false;

        for (int i = 0; i <= maxNodeIndex; i++)
        {
            delete (v, &adjList[i]);
        }

        free_list(&adjList[v]);
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        if (u < 0 || v < 0 || u > maxNodeIndex || v > maxNodeIndex || !nodeExists[u] || !nodeExists[v])
            return;

        delete (v, &adjList[u]);
        delete (u, &adjList[v]);
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
    }

    void FindShortestPath(int u, int v) const override
    {
        // TODO: Find the shortest path between the nodes u and v and print it.
    }

    int FindShortestPathLength(int u, int v) const override
    {
        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
    }

    YourListType GetNeighbors(int u) const override
    {
        // TODO: Return the list of neighbors.
        YourListType ans = YourListType();
        if (u < 0 || u > maxNodeIndex || !nodeExists[u])
            return ans;
        copy(&ans, &adjList[u]);
        return ans;
    }
};

#endif // ADJACENCY_LIST_GRAPH_H
