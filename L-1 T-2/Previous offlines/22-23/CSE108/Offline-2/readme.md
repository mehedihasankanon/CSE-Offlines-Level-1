# Offline 2

Further development of classes to represent basic geometric shapes (`Rectangle`, `Triangle`, and `Circle`) with:

- Computation of **area** and **perimeter**
- Support for a dynamically managed **color**
- Improved **ShapeCollection** with **dynamic resizing**

---

- **Dynamic resizing** of storage arrays (doubles capacity when full)
- **Cloning** of objects when adding to `ShapeCollection`
- **Proper destruction** of all dynamically allocated objects
- **Improved memory safety** (no shallow copies when adding shapes)

---

## Some Constraints

- Strict **manual dynamic memory management** 
- No usage of STL containers 
- Shape objects passed **by reference**, but stored as deep copies
- Ensure no memory leaks or invalid frees

---

## Concepts Practiced

- Deep Copy and the **Rule of Three** (constructor, copy constructor, destructor)
- Dynamic resizing of arrays (similar to how `std::vector` works internally)
- Heap memory management (`malloc/free` manually)
- Encapsulation
- Managing heterogeneous collections without inheritance/polymorphism
- Avoiding memory bugs (e.g., dangling pointers, shallow copies)

---
