### Offline assignment on stack

## Files
1.  `queue.h`: Contains the abstract class definition for queue, with two derived classs definitions we use for implementing our stack: one using dynamic array and another using a linked list.
2.  `arrayqueue.cpp`: The implementation of all methods defined in ArrayQueue class e.g. ENQUEUE, DEQUEUE, FRONT, IS_EMPTY, SIZE. This project implements the (**circular queue**)[https://en.wikipedia.org/wiki/Circular_buffer] structure. The array is resized to double of its current max size once it's full, and resized ot half of its max size when it's 1/4th full
3.  `listqueue.cpp`: implementation of all methods defined in ListQueue class. a helper class `Node` is used to implement the linkedlist in the data structure.
4.  `randomtester.cpp`: `main()` function with testing functions for both implementations, including edge cases check, for example: popping an empty stack, etc. by using random operations.
5.  `main.cpp`: Implementation of the hospital queue problem in task 3




# Build and Run:
Run the `test.ps1` file in the directory

## Runtime Complexity of the method implementations
- `ENQUEUE`: O(1)
- `DEQUEUE`: O(1) amortized
- `CLEAR`: O(1) for ArrayStack, O(n) for ListStack
- `FRONT`, `BACK`: O(1)
- `IS_EMPTY`: O(1)
- `RESIZE`: O(n) for ArrayStack, not defined for ListStack