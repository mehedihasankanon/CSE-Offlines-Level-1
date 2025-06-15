CSE 106 - DSA I sessional
Offline assignment on stack

Files
1.  stack.h
    Contains the abstract class definition for stack, with two derived classs definitions we use for
    implementing our stack: one using dynamic array and another using a linked list.
2.  arraystack.cpp
    The implementation of all methods defined in ArrayStack class e.g. PUSH, POP, TOP, SIZE, IS_EMPTY, RESIZE
    The array is resized to double of its current max size once it's half full, and resized ot half of its max size when it's 1/4th full
3.  liststack.cpp
    implementation of all methods defined in ListStack class
    a helper class `Node` is used to implement the linkedlist in the data structure.
4.  test.cpp
    main() function with testing functions for both implementations, including edge cases check, for example: popping an empty stack, etc.


Build and Run:
Run the `build.bat` or `build.ps1` file in the directory

*** Runtime Complexity of the method implementations ***
    PUSH        --- O(1)
    POP         --- O(1) amortized
    CLEAR       --- O(1) for ArrayStack
                    O(n) for ListStack
    TOP         --- O(1)
    IS_EMPTY    --- O(1)
    RESIZE      --- O(n) for ArrayStack
                    not defined for ListStack