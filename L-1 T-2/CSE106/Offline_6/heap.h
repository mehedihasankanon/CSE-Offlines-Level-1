#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <algorithm>

using std::min;
using std::swap;
using std::vector;

/**
 * `Heap` class implements a basic max-heap data structure for non-negative integer values.
 * 
 */
class Heap
{
private:
    int *heapTree;
    int heapSize, capacity;

    /**
     * Resizes the heap tree to a new capacity.
     * 
     * @param newCapacity The new capacity for the heap tree.
     */
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

    /**
     * Maintains the max-heap property by moving the element at index `idx` up the heap.
     * 
     * @param idx The index of the element to heapify up.
     */
    void heapifyUp(int idx)
    {
        while (idx > 1 && heapTree[idx] > heapTree[idx / 2])
        {
            swap(heapTree[idx], heapTree[idx / 2]);
            idx /= 2;
        }
    }

    /**
     * Maintains the max-heap property by moving the element at index `idx` down the heap.
     * 
     * @param idx The index of the element to heapify down.
     */
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
    /**
     * Initialize a heap from an array of integers
     */
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

    /**
     * Initialize an empty heap with a specified size.
     * 
     * @param size The initial size of the heap.
     */
    Heap(size_t size)
    {
        heapTree = new int[size + 5];
        heapSize = 0;
        capacity = size + 5;
        heapTree[0] = -1;
    }

    /**
     * Destructor to clean up the heap tree.
     */
    ~Heap()
    {
        delete[] heapTree;
    }

    /**
     * Inserts an element into the heap and maintains the max-heap property.
     * 
     * @param element The element to be inserted into the heap.
     */
    void insert(int element)
    {

        if (heapSize >= capacity)
        {
            treeResize(capacity * 2 + 5);
        }

        heapTree[++heapSize] = element;

        heapifyUp(heapSize);
    }

    /**
     * @return The number of elements in the heap.
     */
    int size() const { return heapSize; }

    /**
     * @return The maximum element in the heap. If empty tree, returns -1
     */
    int getMax() const
    {
        if (heapSize == 0)
            return -1;

        return heapTree[1];
    }

    /**
     * Deletes the maximum element from the heap.
     */
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

/**
 * This function uses the `Heap` class to sort the numbers in ascending order.
 * @param numbers The vector of integers to be sorted.
 */
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