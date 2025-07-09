#ifndef HEAP_H
#define HEAP_H

#include <iostream>

using std::vector;

class Heap
{
private:
    int *heapTree;
    int heapSize;

public:
    Heap(vector<int> &numbers)
    {

    }

    Heap(size_t size)
    {
        heapTree = new int[size + 5];
        heapSize = 0;
    }

    void insert(int element)
    {
        heapTree[heapSize++] = element;

        // TODO: call heapify to preserve the tree structure
        
    }

    int size() const { return heapSize; }

    int getMax() const
    {
        if (heapSize == 0)
            return -1;

        return heapTree[1];
    }

    void deleteKey()
    {
        // TODO: implement deletion of heap element, and then to preserve heap structure call heapify
    }

    friend void heapsort(vector<int> &numbers);
};

void heapsort(vector<int> &numbers)
{
    // TODO: implement heapsorting algorithms on a vector
    // requirements: returned vector must contain the numbers in descending order


}

#endif // HEAP_H