===========
 Highorder
===========

Overview
========

Highorder is a collection of useful tools for scientific computing. Most
notably, it is:

* A C++ templated array class with:

  - FORTRAN ordering.
  - Header only compilation.
  - Useful semantics.
  - Automatic memory allocation for new arrays.
  - Initialized to zero by default.
  - Allows up to 6 dimensions, but more can be easily added.

* A Python interface:

  - Cython interface. See examples/cython.
  - Boost.Python interface (coming soon!)
  - Still mostly a work in progress.

* MATLAB wrappers:

  - Coming soon!

Organization
============

* `include`: header files
* `highorder`: Python library
* `examples`: example implementations

  - `cpp`: C++
  - `cython`: Cython

C++ Usage
=========

General C++ usage begins by including the header and creating a
typedef for your data type::

    #include <highorder/array.h>
    typedef highorder::array<double> darray;

Creating an array is as simple as specifying it's dimensions::

    darray A(10,20);  // Allocate a 10x20 matrix.

Element access is with parentheses::

    A(2,3) = 2.0;
    A(4) = 1.0;  // It's up to you to use the right number of indices.

Automatic casts to the data pointer::

    void doublify(double *x, int n) {
      for (int i=0; i<n; i++) x[i] *= 2;
    }
    doublify(A, A.size());

But simple arithmetic operations are built in::

    A *= 2.0; // Double every element.
    A += 3.0; // etc.

Easily fill an array by using the equals sign::

    darray B(10,20);
    B = 1.0; // Initialize every element of B to 1.0.

Operations between two arrays are done element wise::

    A += B; // It's up to you to ensure B has the same dimensions as A.
    A *= B; // This is element wise multiplication (NOT matrix multiplication).

Easily copy data from one array to another::

    B = A; // Copy the data from A into the data from B.

Create a view into an array::

    darray C(B); // C holds a view into the data of B.

Clever indexing allow more complicated views::

    darray D(&B(0,4), 10); // D holds a view into the 5th column of B!

Arrays can be resized::

    A.resize(10,10); // This does not reallocate the underlying memory,
                     // so be sure that you don't make the matrix any bigger!

The underlying memory can be reallocated to a large size if need be::

    A.realloc(100,100); // This frees the old memory allocated by A. Any views
                        // which refer to this memory are no longer valid.
                        // Your program may crash if you attempt to access them.
