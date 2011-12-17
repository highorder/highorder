#ifndef HIGHORDER_PYBRIDGE_HPP
#define HIGHORDER_PYBRIDGE_HPP

#include <stdexcept>
#include <memory>

#include <numpy/arrayobject.h>
#include <highorder/array.h>

namespace highorder { namespace pybridge {
  using std::unique_ptr;
  using std::invalid_argument;

  /**
   * A lookup table between C types and NumPy typenums / Python format codes.
   */
  template <typename T>
  struct npy {
    static int typenum();
    static char format();
  };

#define NP_TYPENUM(type, tval, fval)					\
  template <> inline int npy<type>::typenum() { return tval; }		\
  template <> inline char npy<type>::format() { return fval; }

  NP_TYPENUM(bool,       NPY_BOOL,   'c')
  NP_TYPENUM(npy_float,  NPY_FLOAT,  'f')
  NP_TYPENUM(npy_double, NPY_DOUBLE, 'd')
  NP_TYPENUM(npy_int,    NPY_INT,    'i')
  NP_TYPENUM(npy_long,   NPY_LONG,   'l')
  NP_TYPENUM(npy_ulong,  NPY_ULONG,  'L')
#undef NP_TYPENUM

  /**
   * Create a NumPy view of the array.
   */
  template <typename T>
  inline PyObject *npy_view(array<T>& a, PyObject *subtype = &PyArray_Type) {
    // Ensure that subtype is a valid subtype of ndarray.
    if (!PyType_Check(subtype) ||
	!PyType_IsSubtype((PyTypeObject*) subtype, &PyArray_Type)) {
      PyErr_SetString(PyExc_ValueError, "Type must be a sub-type of ndarray type");
      return NULL;
    }

    int ndim = a.ndim();
    npy_intp dims[6];
    for (int i=0; i<ndim; i++)
      dims[i] = a.size(i);

    int typenum = npy<T>::typenum();
    return PyArray_New((PyTypeObject*)subtype, ndim, dims, typenum, NULL,
		       (T*) a, 0, NPY_FARRAY, NULL);
  }

  /**
   * Create a NumPy copy of the array.
   *
   * Equivalent to npy_view(A, subtype).copy().
   */
  template <typename T>
  inline PyObject *npy_copy(array<T>& a, PyObject *subtype = &PyArray_Type) {
    PyObject *view = npy_view(a, subtype);
    if (view == NULL) return NULL;
    PyObject *copy = PyObject_CallMethod(view, (char*) "copy", (char*) "()");
    Py_DECREF(view);
    return copy;
  }

  /**
   * Access a NumPy array though the highorder::array<T> interface.
   */
  template <typename T>
  unique_ptr< array<T> > view(PyObject *obj) {
    if (obj == Py_None || obj == NULL)
      return unique_ptr< array<T> >(new array<T>());

    if (!PyArray_Check(obj))
      throw invalid_argument("Object not of type ndarray.");
    if (npy<T>::typenum() != PyArray_TYPE(obj))
      throw invalid_argument("Array has incorrect dtype."); // @todo: make this more descriptive
    if (PyArray_NDIM(obj) > 6)
      throw invalid_argument("Array has too many dimensions.");
    if (!PyArray_CHKFLAGS(obj, NPY_FARRAY))
      throw invalid_argument("Array not Fortran contiguous. Try .copy('F')?");

    int ndim = PyArray_NDIM(obj);
    dgSize dims[6];
    for (int i=0; i<ndim; i++)
      dims[i] = PyArray_DIM(obj,i);
    T* data = (T*) PyArray_DATA(obj);

    return unique_ptr< array<T> >(new array<T>(data, ndim, dims));
  }


  /**
   * Wrappers for view<T>.
   *
   * Necessary, since Cython does not support currently templated functions.
   * The names correspond to Python format character.
   * @see http://docs.python.org/library/struct.html#format-characters
   */
  inline unique_ptr< array<bool  > > view_c(PyObject *obj) { return view<bool  >(obj); }
  inline unique_ptr< array<float > > view_f(PyObject *obj) { return view<float >(obj); }
  inline unique_ptr< array<double> > view_d(PyObject *obj) { return view<double>(obj); }
  inline unique_ptr< array<int   > > view_i(PyObject *obj) { return view<int   >(obj); }
  inline unique_ptr< array<long  > > view_l(PyObject *obj) { return view<long  >(obj); }
  inline unique_ptr< array<ulong > > view_L(PyObject *obj) { return view<ulong >(obj); }

}}  // namespace highorder::pybridge

#endif
