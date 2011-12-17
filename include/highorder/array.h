#ifndef HIGHORDER_ARRAY_H
#define HIGHORDER_ARRAY_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

namespace highorder {

typedef int dgSize;

template <typename T> class array {
 private:
  T *_data;
  int _ndim;
  dgSize _size;
  dgSize _dims[6];
  dgSize _strides[6]; // Omits first stride which is always 1.
  bool _alloc;
  void allocmem()
    { _data=new T[_size]; std::fill(_data, _data+_size, T(0)); _alloc=true; }
  void deallocmem()
    { if (_alloc) delete[] _data; _alloc=false; }
  void setstrides()
  {
    std::partial_sum(_dims, _dims+_ndim, _strides, std::multiplies<dgSize>());
    _size=_strides[_ndim-1];
  }

 public:
  typedef T value_type;

  //////////////////
  // Constructors

  // A NULL array.
  array() : _data(NULL), _ndim(0), _size(0), _alloc(false) {}

  // An array filled with zeros.
  array(int ndim, const dgSize *dims)
    { resize(ndim, dims); allocmem(); }
  array(dgSize s0)
    { resize(s0); allocmem(); }
  array(dgSize s0, dgSize s1)
    { resize(s0, s1); allocmem(); }
  array(dgSize s0, dgSize s1, dgSize s2)
    { resize(s0, s1, s2); allocmem(); }
  array(dgSize s0, dgSize s1, dgSize s2, dgSize s3)
    { resize(s0, s1, s2, s3); allocmem(); }
  array(dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4)
    { resize(s0, s1, s2, s3, s4); allocmem(); }
  array(dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4, dgSize s5)
    { resize(s0, s1, s2, s3, s4, s5); allocmem(); }

  // A view into the data.
  array(T *data, int ndim, const dgSize *dims) : _data(data), _alloc(false)
    { resize(ndim, dims); }
  array(T *data, dgSize s0) : _data(data), _alloc(false)
    { resize(s0); }
  array(T *data, dgSize s0, dgSize s1) : _data(data), _alloc(false)
    { resize(s0, s1); }
  array(T *data, dgSize s0, dgSize s1, dgSize s2) : _data(data), _alloc(false)
    { resize(s0, s1, s2); }
  array(T *data, dgSize s0, dgSize s1, dgSize s2, dgSize s3) : _data(data), _alloc(false)
    { resize(s0, s1, s2, s3); }
  array(T *data, dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4) : _data(data), _alloc(false)
    { resize(s0, s1, s2, s3, s4); }
  array(T *data, dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4, dgSize s5) : _data(data), _alloc(false)
    { resize(s0, s1, s2, s3, s4, s5); }

  // A view into the array a.
  array(const array<T>& a) : _data(a._data), _ndim(a._ndim), _size(a._size), _alloc(false)
  {
    std::copy(a._dims, a._dims+a._ndim, _dims);
    std::copy(a._strides, a._strides+a._ndim, _strides);
  }

  ////////////////
  // Destructor
  ~array() { deallocmem(); }

  /////////////
  // Methods

  // Resize (or reshape) the array. Does not reallocate the underlying data.
  // Use realloc if the array size will change.
  void resize(int ndim, const dgSize *dims)
  {
    _ndim=ndim;
    std::copy(dims, dims+ndim, _dims);
    setstrides();
  }
  void resize(dgSize s0)
    { dgSize dims[1] = {s0}; resize(1, dims); }
  void resize(dgSize s0, dgSize s1)
    { dgSize dims[2] = {s0, s1}; resize(2, dims); }
  void resize(dgSize s0, dgSize s1, dgSize s2)
    { dgSize dims[3] = {s0, s1, s2}; resize(3, dims); }
  void resize(dgSize s0, dgSize s1, dgSize s2, dgSize s3)
    { dgSize dims[4] = {s0, s1, s2, s3}; resize(4, dims); }
  void resize(dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4)
    { dgSize dims[5] = {s0, s1, s2, s3, s4}; resize(5, dims); }
  void resize(dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4, dgSize s5)
    { dgSize dims[6] = {s0, s1, s2, s3, s4, s5}; resize(6, dims); }

  // Update the data pointer.
  void setdata(T *data)
    { deallocmem(); _data = data; }

  // Refer to an existing array or data pointer.
  void setreference(array const& a)
    { deallocmem(); _data = (T*) a; resize(a.ndim(), a.dims()); }
  void setreference(T *data, int ndim, dgSize *dims)
    { deallocmem(); _data = data; resize(ndim, dims); }
  void setreference(T *data, dgSize s0)
    { deallocmem(); _data = data; resize(s0); }
  void setreference(T *data, dgSize s0, dgSize s1)
    { deallocmem(); _data = data; resize(s0, s1); }
  void setreference(T *data, dgSize s0, dgSize s1, dgSize s2)
    { deallocmem(); _data = data; resize(s0, s1, s2); }
  void setreference(T *data, dgSize s0, dgSize s1, dgSize s2, dgSize s3)
    { deallocmem(); _data = data; resize(s0, s1, s2, s3); }
  void setreference(T *data, dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4)
    { deallocmem(); _data = data; resize(s0, s1, s2, s3, s4); }
  void setreference(T *data, dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4, dgSize s5)
    { deallocmem(); _data = data; resize(s0, s1, s2, s3, s4, s5); }

  // Reallocate array.
  void realloc(int ndim, const dgSize *dims)
    { deallocmem(); resize(ndim, dims); allocmem(); }
  void realloc(dgSize s0)
    { deallocmem(); resize(s0); allocmem(); }
  void realloc(dgSize s0, dgSize s1)
    { deallocmem(); resize(s0,s1); allocmem(); }
  void realloc(dgSize s0, dgSize s1, dgSize s2)
    { deallocmem(); resize(s0, s1, s2); allocmem(); }
  void realloc(dgSize s0, dgSize s1, dgSize s2, dgSize s3)
    { deallocmem(); resize(s0, s1, s2, s3); allocmem(); }
  void realloc(dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4)
    { deallocmem(); resize(s0, s1, s2, s3, s4); allocmem(); }
  void realloc(dgSize s0, dgSize s1, dgSize s2, dgSize s3, dgSize s4, dgSize s5)
    { deallocmem(); resize(s0, s1, s2, s3, s4, s5); allocmem(); }

  // Information about the array.
  dgSize size() const { return _size; }
  dgSize size(int i) const { return i<_ndim ? _dims[i] : 1; }
  int ndim() const { return _ndim; }
  const dgSize* dims() const { return _dims; }

  // strides() omits the first stride which is always 1.
  const dgSize* strides() const { return _strides; }

  // Element access.
  T& operator[](dgSize ix) const
    { return _data[ix]; }
  T& operator()(dgSize i0) const
    { return _data[i0]; }
  T& operator()(dgSize i0, dgSize i1) const
    { return _data[i0+_strides[0]*i1]; }
  T& operator()(dgSize i0, dgSize i1, dgSize i2) const
    { return _data[i0+_strides[0]*i1+_strides[1]*i2]; }
  T& operator()(dgSize i0, dgSize i1, dgSize i2, dgSize i3) const
    { return _data[i0+_strides[0]*i1+_strides[1]*i2+_strides[2]*i3]; }
  T& operator()(dgSize i0, dgSize i1, dgSize i2, dgSize i3, dgSize i4) const
    { return _data[i0+_strides[0]*i1+_strides[1]*i2+_strides[2]*i3+_strides[3]*i4]; }
  T& operator()(dgSize i0, dgSize i1, dgSize i2, dgSize i3, dgSize i4, dgSize i5) const
    { return _data[i0+_strides[0]*i1+_strides[1]*i2+_strides[2]*i3+_strides[3]*i4+_strides[4]*i5]; }

  operator T*() const { return _data; }

  void fill(const T val) const { std::fill(_data, _data+_size, val); }
  bool owndata() const { return _alloc; }

  // Fill array with a value or data
  const array& operator=(const T x) const
    { std::fill(_data, _data+_size, x); return *this; }
  const array& operator=(const array& x) const
    { std::copy((const T*)x, (const T*)x+_size, _data); return *this; }
  const array& operator=(const T *x) const
    { std::copy(x, x+_size, _data); return *this; }

#define __ARRAY_OPERATOR(op)						\
  const array& operator op(const T x) const				\
    { for(dgSize i=0; i<_size; i++) _data[i] op x  ; return *this; }	\
  const array& operator op(const array& x) const			\
    { for(dgSize i=0; i<_size; i++) _data[i] op x[i]; return *this; }	\
  const array& operator op(const T* x) const				\
    { for(dgSize i=0; i<_size; i++) _data[i] op x[i]; return *this; }

  __ARRAY_OPERATOR(+=)
  __ARRAY_OPERATOR(-=)
  __ARRAY_OPERATOR(*=)
  __ARRAY_OPERATOR(/=)
#undef __ARRAY_OPERATOR

  void negate() const { for(dgSize i=0; i<_size; i++) _data[i] = -_data[i]; }
  void duplicate(const array& a) { realloc(a.ndim(), a.dims()); *this=a; }
};

template <typename T> inline void sort(const array<T> &a)
{ std::sort((T*)a, (T*)a+a.size()); }

template <typename T> inline T max(const array<T> &a)
{ return *std::max_element((const T*)a, (const T*)a+a.size()); }

template <typename T> inline T min(const array<T> &a)
{ return *std::min_element((const T*)a, (const T*)a+a.size()); }

template <typename T> inline T sum(const array<T> &a)
{ return std::accumulate((const T*)a, (const T*)a+a.size(),T(0)); }

template <typename T> inline T prod(const array<T> &a)
{ return std::accumulate((const T*)a, (const T*)a+a.size(), T(1), std::multiplies<T>()); }

template <typename T> inline T norm(const array<T> &a)
{ return std::sqrt(std::inner_product((const T*)a, (const T*)a+a.size(), (const T*)a, T(0))); }

template <typename T> inline T infnorm(const array<T> &a)
{
  T nrm=0.0;
  for (dgSize i=0; i<a.size(); i++) {
    T absa=std::abs(a[i]);
    if (absa>nrm)
      nrm=absa;
  }
  return nrm;
}

template <typename T> inline bool anynan(const array<T> &a)
{
  for (dgSize i=0; i<a.size(); i++)
    if (isnan(a[i]))
      return true;
  return false;
}


}
#endif
