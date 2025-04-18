# Offline 1

Implement classes to represent basic geometric shapes (`Rectangle`, `Triangle`, and `Circle`) with:

- Computation of **area** and **perimeter**
- Support for a dynamically managed **color**

Using a `ShapeCollection` class to store some instances of the classes

---

## Classes Implemented

### `Rectangle`, `Triangle`, and `Circle`
- Basic attributes and color
- Area, Perimeter
- getter-setter method

### `ShapeCollection`
- Fixed-size storage for up to `100` objects of each class
- Methods (adding objects, finding how many objects are stored, printing all the objects stored)

---

## Constraints

- Use **manual dynamic memory management** 
- Avoid memory leaks and double frees
- Shape objects passed to `ShapeCollection` must be passed **by reference**
- No STL containers (`vector`, `string` etc.)
etc.

---

## Concepts Practiced

- Encapsulation
- Composition
- Pass-by-reference
- Avoiding common memory bugs (e.g., shallow copy, double-free)

