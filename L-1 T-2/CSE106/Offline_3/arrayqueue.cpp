#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity

    data = new int[initial_capacity];
    capacity = initial_capacity;
    front_idx = -1;
    rear_idx = -1;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue

    if (size() == capacity)
    {
        resize(capacity * 2);
    }

    rear_idx = (rear_idx + 1) % capacity;
    data[rear_idx % capacity] = item;
    if (front_idx == -1)
        front_idx = 0;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element

    if (size() == 0)
    {
        // cout << "Error: Empty Queue" << endl;
        return -1;
    }

    int item = data[front_idx];

    if (size() == 1)
    {
        front_idx = rear_idx = -1;
        resize(2);
        return item;
    }

    front_idx = (front_idx + 1) % capacity;
    if (size() == 0)
    {
        front_idx = rear_idx = -1;
    }

    if (size() * 4 < capacity)
    {
        resize(capacity / 2);
    }

    return item;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)

    delete[] data;
    data = new int[2];
    capacity = 2;
    front_idx = rear_idx = -1;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    if (front_idx == -1)
        return 0;
    if (rear_idx >= front_idx)
        return rear_idx - front_idx + 1;
    else
        return capacity - front_idx + rear_idx + 1;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    if (empty())
    {
        // cout << "Error: Empty Queue" << endl;
        return -1;
    }
    return data[front_idx % capacity];
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    if (empty())
    {
        // cout << "Error: Empty Queue" << endl;
        return -1;
    }
    return data[rear_idx % capacity];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    return !size();
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    if (size() == 0)
        return "<|";

    string s = "<";
    for (int i = 0; i < size(); i++)
    {
        s += to_string(data[(front_idx + i) % capacity]);
        if (i != size() - 1)
            s += ", ";
    }
    s += "|";
    return s;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices

    if (rear_idx == front_idx && front_idx == -1)
    {
        // Empty queue resizing
        new_capacity = max(new_capacity, 2);
        int *new_data = new int[new_capacity];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        return;
    }

    int old_size = size();
    new_capacity = max(new_capacity, 2);
    int *new_data = new int[new_capacity];
    for (int i = 0; i < size(); i++)
    {
        new_data[i] = data[(front_idx + i) % capacity];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    front_idx = 0;
    rear_idx = old_size - 1;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}