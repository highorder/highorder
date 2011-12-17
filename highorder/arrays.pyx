"""
Python & C++ Array Library
"""

import numpy as _np
cimport numpy as _np
_np.import_array()

class fndarray(_np.ndarray):
    """
    Subclass of numpy.ndarray which prefers Fortran ordered
    arrays when doing basic arithmetic.

    Parameters
    ----------
    shape : tuple of ints
        Shape of the created array
    dtype : data-type
        Any object which can be interpreted as a numpy data type.
    """
    def __new__(cls, shape, dtype=None):
        return _np.ndarray.__new__(cls, shape, dtype, order='F')

    def _out(self, obj):
        """
        Prepares a matrix to store the result of a binary operation
        between self and other.
        """
        if not _np.isscalar(obj) and self.dtype != obj.dtype:
            raise ValueError('arrays have different type')
        return fndarray(self.shape, dtype=self.dtype)

    def __add__(self, other):
        return _np.add(self,other,self._out(other))
    __radd__ = __add__

    def __sub__(self, other):
        return _np.subtract(self,other,self._out(other))
    def __rsub__(self, other):
        return _np.subtract(other,self,self._out(other))

    def __mul__(self, other):
        return _np.multiply(self,other,self._out(other))
    __rmul__ = __mul__

    def __div__(self, other):
        return _np.divide(self,other,self._out(other))
    def __rdiv__(self, other):
        return _np.divide(other,self,self._out(other))

    def sum(self, axis=None, dtype=None, out=None):
        if out is None and axis is not None:
            # Return a Fortran ordered array.
            return _np.ndarray.sum(self.T, self.ndim-1-axis, dtype, out).T
        else:
            # Nothing to transpose.
            return _np.ndarray.sum(self, axis, dtype, out)

    @property
    def fflat(self):
        """Returns a Fortran ordered flattening of the array."""
        return self.T.flat

    def copy(self, order='F'):
        """Return a copy of the array."""
        return _np.ndarray.copy(self, order)

####################
# Temporary testing

# Load the interfaces from arrays.pxd:
from highorder.arrays cimport *
from cython.operator cimport dereference as deref

cdef array[int]* A = new array[int](5,10)
cdef int i
for i in range(50):
    deref(A)[i] = i

def tst_view(type=fndarray):
    return npy_view(deref(A), type)

def tst_copy(type=fndarray):
    return npy_copy(deref(A), type)

cdef void print_array_c(array[int] A):
    cdef int ndim = A.ndim()
    print ndim
    shape = [A.size(i) for i in range(ndim)]
    print shape

cdef array[int] iv(object):
    return deref(view_i(object))

def print_array(object):
    print_array_c(deref(view_i(object)))
    print_array_c(iv(object))
