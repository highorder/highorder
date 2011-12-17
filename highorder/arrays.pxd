# Intefaces of "highorder/array.h" and "highorder/pybridge.hpp".

# pybridge.hpp uses the NumPy C-API.
from numpy cimport import_array

from libcpp cimport bool as cbool

cdef extern from "highorder/array.h" namespace "highorder":
    ctypedef int dgSize
    ctypedef dgSize* const_dgSize_ptr "const dgSize*"
    cdef cppclass array[T]:
        array()
        array(int, const_dgSize_ptr)
        array(dgSize)
        array(dgSize, dgSize)
        array(dgSize, dgSize, dgSize)
        array(dgSize, dgSize, dgSize, dgSize)
        array(dgSize, dgSize, dgSize, dgSize, dgSize)
        array(dgSize, dgSize, dgSize, dgSize, dgSize, dgSize)

        void resize(int, const_dgSize_ptr)
        void resize(dgSize)
        void resize(dgSize, dgSize)
        void resize(dgSize, dgSize, dgSize)
        void resize(dgSize, dgSize, dgSize, dgSize)
        void resize(dgSize, dgSize, dgSize, dgSize, dgSize)
        void resize(dgSize, dgSize, dgSize, dgSize, dgSize, dgSize)

        void setdata(T*)

        void setreference(T*, int, const_dgSize_ptr)
        void setreference(T*, dgSize)
        void setreference(T*, dgSize, dgSize)
        void setreference(T*, dgSize, dgSize, dgSize)
        void setreference(T*, dgSize, dgSize, dgSize, dgSize)
        void setreference(T*, dgSize, dgSize, dgSize, dgSize, dgSize)
        void setreference(T*, dgSize, dgSize, dgSize, dgSize, dgSize, dgSize)

        void realloc(int, const_dgSize_ptr)
        void realloc(dgSize)
        void realloc(dgSize, dgSize)
        void realloc(dgSize, dgSize, dgSize)
        void realloc(dgSize, dgSize, dgSize, dgSize)
        void realloc(dgSize, dgSize, dgSize, dgSize, dgSize)
        void realloc(dgSize, dgSize, dgSize, dgSize, dgSize, dgSize)

        dgSize size()
        dgSize size(int)
        int ndim()
        const_dgSize_ptr dims()
        const_dgSize_ptr strides()

        T& operator[](dgSize)
        T& operator()(dgSize)
        T& operator()(dgSize, dgSize)
        T& operator()(dgSize, dgSize, dgSize)
        T& operator()(dgSize, dgSize, dgSize, dgSize)
        T& operator()(dgSize, dgSize, dgSize, dgSize, dgSize)
        T& operator()(dgSize, dgSize, dgSize, dgSize, dgSize, dgSize)

        # operator T*()

        # operator+=
        # operator-=
        # operator*=
        # operator/=

        void negate()
        # void duplicate(const array[T]&)

    # void sort(const array[T]&)
    # T max(const array[T]&)
    # T min(const array[T]&)
    # T sum(const array[T]&)
    # T prod(const array[T]&)
    # T norm(const array[T]&)
    # T infnorm(const array[T]&)
    # bool anynan(const array<T>&)

cdef extern from "<memory>" namespace "std":
    cdef cppclass unique_ptr[T]:
        unique_ptr()
        unique_ptr(T*)
        unique_ptr(T&)

        T& operator*()
        # T* operator->()
        T* get()
        T* release()
        void reset()
        void reset(T*)

cdef extern from "highorder/pybridge.hpp" namespace "highorder::pybridge":
    # Return a NumPy view of the array.
    cdef object npy_view(array[cbool ]&, type)
    cdef object npy_view(array[float ]&, type)
    cdef object npy_view(array[double]&, type)
    cdef object npy_view(array[int   ]&, type)
    cdef object npy_view(array[long  ]&, type)
    cdef object npy_view(array[ulong ]&, type)

    # Return a NumPy copy of the array.
    cdef object npy_copy(array[cbool ]&, type)
    cdef object npy_copy(array[float ]&, type)
    cdef object npy_copy(array[double]&, type)
    cdef object npy_copy(array[int   ]&, type)
    cdef object npy_copy(array[long  ]&, type)
    cdef object npy_copy(array[ulong ]&, type)

    cdef unique_ptr[array[cbool ]] view_c(object) except +
    cdef unique_ptr[array[float ]] view_f(object) except +
    cdef unique_ptr[array[double]] view_d(object) except +
    cdef unique_ptr[array[int   ]] view_i(object) except +
    cdef unique_ptr[array[long  ]] view_l(object) except +
    cdef unique_ptr[array[ulong ]] view_L(object) except +
