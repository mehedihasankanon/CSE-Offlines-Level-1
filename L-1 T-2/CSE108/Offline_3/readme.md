# Offline Assignment 2: Operator Overloading in C++

## Overview

This assignment focuses on implementing operator overloading in C++ to create a system for handling fractions, fraction vectors, and fraction matrices.  The goal is to build three classes (`Fraction`, `FractionVector`, and `FractionMatrix`) that model mathematical operations commonly performed on these data structures.  The assignment emphasizes object-oriented programming principles and dynamic memory management.

## Task Breakdown

The assignment is divided into four tasks:

**Task 1: `Fraction` Class**

Implement a `Fraction` class with the following features:

* **Attributes:** `numerator` and `denominator` (integers).
* **Simplification:** Fractions are always stored in simplified form (reduced to lowest terms).
* **Error Handling:**  The denominator must never be zero.  Handle invalid input appropriately.
* **Operator Overloading:** Overload the following operators:
    * Arithmetic operators: `+`, `-`, `*`, `/` (for operations between two `Fraction` objects and between a `Fraction` and a `float`).
    * Compound assignment operators: `+=`, `-=`, `*=`, `/=`.
    * Stream insertion operator: `<<` (to display a fraction in the form `numerator/denominator`).

**Task 2: `FractionVector` Class**

Implement a `FractionVector` class with the following features:

* **Internal Storage:** Dynamically allocated array of `Fraction` objects.
* **Subscript Operator:** Overload the `[]` operator for accessing and modifying individual elements.
* **Vector Operations:** Overload `+` and `-` for element-wise addition and subtraction.  Ensure vectors are of the same size before performing operations.
* **Scalar Operations:** Overload `*` and `/` for scalar multiplication and division with a `Fraction`.
* **Dot Product:** Overload `*` to compute the dot product of two `FractionVector` objects.
* **Magnitude:** Implement a `value()` method to compute the magnitude (L2 norm) of the vector.
* **Stream Insertion:** Overload `<<` to print vector elements in a readable format.

**Task 3: `FractionMatrix` Class**

Implement a `FractionMatrix` class with the following features:

* **Internal Storage:**  Use dynamically allocated arrays of `FractionVector` objects to represent rows and columns.
* **Subscript Operator:** Overload `[]` to access rows as `FractionVector` objects.
* **`getColumn()` Method:** Implement a method to safely access columns.
* **Matrix Operations:** Overload `+` and `-` for element-wise matrix addition and subtraction.  Ensure matrices have matching dimensions.
* **Scalar Operations:** Overload `*` and `/` for scalar multiplication and division.
* **Matrix Multiplication:** Overload `*` to perform standard matrix multiplication.
* **Hadamard Product:** Overload `%` to perform element-wise (Hadamard) multiplication.
* **Transpose:** Implement a `transpose()` method.
* **Stream Insertion:** Overload `<<` to display the matrix in a readable format.

**Task 4: Test Cases and Demonstration (10 Marks)**

Write a `main()` function to demonstrate all arithmetic operations on `Fraction`, vector operations (`FractionVector`), and matrix operations (`FractionMatrix`).  This includes testing addition, subtraction, multiplication, division, dot product, magnitude, and Hadamard product.

**Additional Requirements:**

For all classes requiring them, implement:

* Copy constructor
* Destructor
* Overload the assignment operator
