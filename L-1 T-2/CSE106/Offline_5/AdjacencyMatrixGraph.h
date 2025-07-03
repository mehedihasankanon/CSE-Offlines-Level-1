#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"

class AdjacencyMatrixGraph : public GraphADT
{
private:
    // TODO: Consider necessary private members as per your discretion

    int capacity;
    bool *nodeExists = nullptr;

    int **adjMatrix = nullptr;

    void resizeMatrix(int newCapacity)
    {
        // TODO: you need to resize your matrix when you will less data or more data

        int **newAdjMatrix = new int *[newCapacity + 1];
        for (int i = 0; i < newCapacity; i++)
        {
            newAdjMatrix[i] = new int[newCapacity + 1];
            for (int j = 0; j <= newCapacity; j++)
            {
                newAdjMatrix[i][j] = 0;
            }
        }
        for (int i = 0; i <= min(capacity, newCapacity); i++)
        {
            for (int j = 0; j <= min(capacity, newCapacity); j++)
            {
                newAdjMatrix[i][j] = adjMatrix[i][j];
            }
        }

        for (int i = 0; i <= capacity; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;

        adjMatrix = newAdjMatrix;

        bool *newNodeExists = new bool[newCapacity + 1];
        for (int i = 0; i <= newCapacity; i++)
            newNodeExists[i] = 0;
        for (int i = 0; i <= min(capacity, newCapacity); i++)
            newNodeExists[i] = nodeExists[i];

        delete[] nodeExists;
        nodeExists = newNodeExists;

        capacity = newCapacity;
    }

public:
    AdjacencyMatrixGraph()
    {
        capacity = 2;
        adjMatrix = new int *[capacity + 1];
        for (int i = 0; i <= capacity; i++)
        {
            adjMatrix[i] = new int[capacity + 1];
            for (int j = 0; j <= capacity; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
        nodeExists = new bool[capacity + 1];
        for (int i = 0; i <= capacity; i++)
            nodeExists[i] = 0;
    }

    ~AdjacencyMatrixGraph() override
    {
        for (int i = 0; i <= capacity; i++)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        delete[] nodeExists;
    }

    void AddNode(int v) override
    {
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.

        if (v < 0)
            return;

        if (v > capacity)
        {
            resizeMatrix(v * 2 + 5);
        }

        nodeExists[v] = 1;
    }

    void AddEdge(int u, int v) override
    {
        // TODO: Add a new edge between the nodes u and v
        if (u < 0 || v < 0 || u == v)
            return;

        AddNode(u);
        AddNode(v);

        adjMatrix[u][v] = adjMatrix[v][u] = 1;
    }

    bool CheckEdge(int u, int v) const override
    {
        // TODO: Check whether there is an edge between two nodes u and v

        if (u < 0 || v < 0 || u > capacity || v > capacity || !nodeExists[u] || !nodeExists[v])
            return false;

        return adjMatrix[u][v];
    }

    void RemoveNode(int v) override
    {
        // TODO: Remove a node.
        if (v < 0 || v > capacity || !nodeExists[v])
            return;

        nodeExists[v] = 0;
        for (int i = 0; i <= capacity; i++)
        {
            adjMatrix[i][v] = adjMatrix[v][i] = 0;
        }
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        if (u < 0 || v < 0 || u > capacity || v > capacity || !nodeExists[u] || !nodeExists[v])
            return;

        adjMatrix[u][v] = adjMatrix[v][u] = 0;
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        if (u < 0 || v < 0 || u > capacity || v > capacity || !nodeExists[u] || !nodeExists[v])
            return false;

        bool *vis = new bool[capacity + 1];
        for (int i = 0; i <= capacity; i++)
            vis[i] = 0;

        Queue *q = new ListQueue();
        vis[u] = true;
        q->enqueue(u);

        while (!q->empty())
        {
            int cur = q->dequeue();

            if (cur == v)
            {
                q->clear();
                delete q;
                delete[] vis;
                return true;
            }
            for (int i = 0; i <= capacity; i++)
            {
                if (adjMatrix[cur][i] && !vis[i] && nodeExists[i])
                {
                    vis[i] = true;
                    q->enqueue(i);
                }
            }
        }

        q->clear();
        delete q;
        delete[] vis;
        return false;
    }

    void FindShortestPath(int u, int v) const override
    {
        // TODO: Find the shortest path between the nodes u and v and print it.
        if (!CheckPath(u, v))
            return;

        int *parent = new int[capacity + 1];
        for (int i = 0; i <= capacity; i++)
            parent[i] = -1;

        Queue *q = new ListQueue();
        q->enqueue(u);

        while (!q->empty())
        {
            int cur = q->dequeue();

            if (cur == v)
            {
                break;
            }
            for (int i = 0; i <= capacity; i++)
            {
                if (i == parent[cur])
                    continue;
                if (adjMatrix[cur][i] && parent[i] == -1 && nodeExists[i])
                {
                    parent[i] = cur;
                    q->enqueue(i);
                }
            }
        }

        int path[capacity] = {v};
        int sz = 1, cur = v;
        while (cur != u)
        {
            path[sz++] = parent[cur];
            cur = parent[cur];
        }

        std::cout << "Shortest Path: ";
        for (int i = sz - 1; i >= 0; i--)
        {
            std::cout << path[i] << " ";
        }
        cout << endl;

        q->clear();
        delete q;
        delete[] parent;
        return;
    }

    int FindShortestPathLength(int u, int v) const override
    {
        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if (!CheckPath(u, v))
            return -1;

        int *parent = new int[capacity + 1];
        for (int i = 0; i <= capacity; i++)
            parent[i] = -1;

        Queue *q = new ListQueue();
        q->enqueue(u);

        while (!q->empty())
        {
            int cur = q->dequeue();

            if (cur == v)
            {
                break;
            }
            for (int i = 0; i <= capacity; i++)
            {
                if (i == parent[cur])
                    continue;
                if (adjMatrix[cur][i] && parent[i] == -1 && nodeExists[i])
                {
                    parent[i] = cur;
                    q->enqueue(i);
                }
            }
        }

        int ans = 0;
        int cur = v;
        while (cur != u)
        {
            ans++;
            cur = parent[cur];
        }

        q->clear();
        delete q;
        delete[] parent;
        return ans;
    }
    YourListType GetNeighbors(int u) const override
    {
        // TODO return a list of neighbors of node u
        linkedList ans;
        if (u < 0 || u > capacity || !nodeExists[u])
            return ans;
        init(&ans);

        for (int i = 0; i <= capacity; i++)
        {
            if (adjMatrix[u][i])
                append(i, &ans);
        }

        return ans;
    }
};

#endif // ADJACENCY_MATRIX_GRAPH_H
