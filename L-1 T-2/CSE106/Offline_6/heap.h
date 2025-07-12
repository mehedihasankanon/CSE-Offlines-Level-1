#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <algorithm>

using std::min;
using std::swap;
using std::vector;

class Heap
{
private:
    int *heapTree;
    int heapSize, capacity;

    void treeResize(int newCapacity)
    {

        int *newHeapTree = new int[newCapacity];
        for (int i = 0; i < min(newCapacity, capacity); i++)
        {
            newHeapTree[i] = heapTree[i];
        }

        delete[] heapTree;
        heapTree = newHeapTree;
        capacity = newCapacity;
    }

    void heapifyUp(int idx)
    {
        while (idx > 1 && heapTree[idx] > heapTree[idx / 2])
        {
            swap(heapTree[idx], heapTree[idx / 2]);
            idx /= 2;
        }
    }

    void heapifyDown(int idx)
    {
        int largest = idx;
        int left = idx * 2, right = idx * 2 + 1;

        if (left <= heapSize && heapTree[left] > heapTree[largest])
        {
            largest = left;
        }

        if (right <= heapSize && heapTree[right] > heapTree[largest])
        {
            largest = right;
        }

        if (largest != idx)
        {
            swap(heapTree[largest], heapTree[idx]);
            heapifyDown(largest);
        }
    }

public:
    Heap(vector<int> &numbers)
    {
        heapTree = new int[numbers.size() + 5];
        capacity = numbers.size() + 5;
        heapSize = 0;
        heapTree[0] = -1;

        for (auto item : numbers)
        {
            insert(item);
        }
    }

    Heap(size_t size)
    {
        heapTree = new int[size + 5];
        heapSize = 0;
        capacity = size + 5;
        heapTree[0] = -1;
    }

    ~Heap()
    {
        delete[] heapTree;
    }

    void insert(int element)
    {

        if (heapSize >= capacity)
        {
            treeResize(capacity * 2 + 5);
        }

        heapTree[++heapSize] = element;

        heapifyUp(heapSize);
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
        if (heapSize == 0)
            return;
        if (heapSize == 1)
        {
            heapSize--;
            return;
        }

        swap(heapTree[1], heapTree[heapSize]);
        heapSize--;

        heapifyDown(1);

        if (heapSize * 4 < capacity)
        {
            treeResize(capacity / 2);
        }
    }
};

void heapsort(vector<int> &numbers)
{

    Heap sortHeap(numbers);
    numbers.clear();

    while (sortHeap.size())
    {
        numbers.push_back(sortHeap.getMax());
        sortHeap.deleteKey();
    }
}

#endif // HEAP_H