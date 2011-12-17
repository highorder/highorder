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

    darray A(10,20);  // Allocate a 10x20 matrix.

    A(2,3) = 2.0; // Element access is with parentheses.
    A(4) = 1.0;  // It's up to you to use the right number of indices.

    void doublify(double *x, int n) {
      for (int i=0; i<n; i++) x[i] *= 2;
    }
    doublify(A, A.size()); // automatic casts to the data pointer.

    A *= 2.0; // Double every element.
    A += 3.0; // etc.

    darray B(10,20);
    B = 1.0; // Initialize every element of B to 1.0.

    A += B; // It's up to you to ensure B has the same dimensions as A.
    A *= B; // This is element wise multiplication (NOT matrix multiplication).

    B = A; // Copy the data from A into the data from B.

    darray C(B); // C holds a view into the data of B.
    darray D(&B(0,4), 10); // D holds a view into the 5th column of B!

    A.resize(10,10); // This does not reallocate the underlying memory,
                     // so be sure that you don't make the matrix any bigger!

    A.realloc(100,100); // This frees the old memory allocated by A. Any views
                        // which refer to this memory are no longer valid.
                        // Your program may crash if you attempt to access them.
