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
    AdjacencyListGraph()
    {
        nodeExists = new bool[1];
        nodeExists[0] = false;

        adjList = new YourListType[1];
        init(&adjList[0]);
    }

    ~AdjacencyListGraph() override
    {
        for (int i = 0; i <= maxNodeIndex; ++i)
        {
            free_list(&adjList[i]);
        }
        delete[] adjList;
        delete[] nodeExists;
    }

    void print_g()
    {
        for (int i = 0; i <= maxNodeIndex; i++)
        {
            printf("%d:", i);
            print(&adjList[i]);
        }
        printf("\n");
    }

    void AddNode(int v) override
    {
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if (v < 0)
            return;

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

            maxNodeIndex = v;
        }
        else
        {
            nodeExists[v] = true;
        }
    }

    void AddEdge(int u, int v) override
    {
        // TODO: Add a new edge between the nodes u and v
        if (u < 0 || v < 0)
            return;

        AddNode(u);
        AddNode(v);

        if (u == v || is_present(u, &adjList[v]))
        {
            return;
        }

        append(u, &adjList[v]);
        append(v, &adjList[u]);

        // print_g();
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
            delete_item(v, &adjList[i]);
        }

        clear(&adjList[v]);
        // print_g();
    }

    void RemoveEdge(int u, int v) override
    {
        // TODO: remove an edge
        if (u < 0 || v < 0 || u > maxNodeIndex || v > maxNodeIndex || !nodeExists[u] || !nodeExists[v])
            return;

        delete_item(v, &adjList[u]);
        delete_item(u, &adjList[v]);
    }

    bool CheckPath(int u, int v) const override
    {
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
        if (u < 0 || v < 0 || u > maxNodeIndex || v > maxNodeIndex || !nodeExists[u] || !nodeExists[v])
        {
            return false;
        }

        bool *vis = new bool[maxNodeIndex + 1];
        for (int i = 0; i <= maxNodeIndex; i++)
            vis[i] = 0;

        Queue *q = new ListQueue();
        vis[u] = 1;
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
            node *it = get_head(&adjList[cur]);
            while (it)
            {
                int t = it->element;
                if (!vis[t])
                {
                    vis[t] = true;
                    q->enqueue(t);
                }
                it = it->next;
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

        if (u < 0 || v < 0 || u > maxNodeIndex || v > maxNodeIndex || !nodeExists[u] || !nodeExists[v])
        {
            std::cout << "Node does not exist in the graph\n";
            return;
        }
        if (!CheckPath(u, v))
        {
            std::cout << "No path found between nodes " << u << " and " << v << "\n";
            return;
        }

        int *parent = new int[maxNodeIndex + 1];
        for (int i = 0; i <= maxNodeIndex; i++)
            parent[i] = -1;

        Queue *q = new ListQueue();
        q->enqueue(u);

        while (!q->empty())
        {
            int cur = q->dequeue();

            node *it = get_head(&adjList[cur]);
            while (it)
            {
                int t = it->element;

                if(t == parent[cur]) 
                {
                    it = it->next;
                    continue;
                }

                if (parent[t] == -1)
                {
                    parent[t] = cur;
                    q->enqueue(t);
                }
                it = it->next;
            }
        }

        int path[maxNodeIndex] = {v};
        int sz = 1, cur = v;
        while(cur != u)
        {
            path[sz++] = parent[cur];
            cur = parent[cur];
        }
        
        std::cout << "Shortest path: ";
        for(int i = sz - 1; i >= 0; i--)
        {
            std::cout << path[i] << " ";
        }
        cout << endl;

        q->clear();
        delete q;
        delete[] parent;
    }

    int FindShortestPathLength(int u, int v) const override
    {
        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if (u < 0 || v < 0 || u > maxNodeIndex || v > maxNodeIndex || !nodeExists[u] || !nodeExists[v])
        {
            return -1;
        }
        if (!CheckPath(u, v))
        {
            return -1;
        }

        int *parent = new int[maxNodeIndex + 1];
        for (int i = 0; i <= maxNodeIndex; i++)
            parent[i] = -1;

        Queue *q = new ListQueue();
        q->enqueue(u);

        while (!q->empty())
        {
            int cur = q->dequeue();

            node *it = get_head(&adjList[cur]);
            while (it)
            {
                int t = it->element;

                if(t == parent[cur]) 
                {
                    it = it->next;
                    continue;
                }

                if (parent[t] == -1)
                {
                    parent[t] = cur;
                    q->enqueue(t);
                }
                it = it->next;
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
        // TODO: Return the list of neighbors.
        YourListType ans = YourListType();
        if (u < 0 || u > maxNodeIndex || !nodeExists[u])
            return ans;
        return adjList[u];
    }
};

#endif // ADJACENCY_LIST_GRAPH_H
