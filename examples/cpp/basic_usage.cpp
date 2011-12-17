#include <cassert>

#include <highorder/array.h>

typedef highorder::array<int> iarray;

int main() {

  iarray A(3,4);

  // Basic size and shape matters:

  // Check array size
  assert(A.size(0) == 3);
  assert(A.size(1) == 4);
  assert(A.size() == 12);

  // Check that the array is initialized to zero.
  for (int i=0; i<A.size(); i++)
    assert(A[i] == 0);

  // Check element set and get.
  A(2,3) = 10;
  assert(A(2,3) == 10);

  // Check Fortran ordering.
  A[5] = 1;
  assert(A(2,1) == 1);


  // Views:

  iarray B(A); // B is a view into A
  B(0) = -1;
  assert(A(0) == -1);

  iarray C(&A(0,2), 3); // C is a view into the 3rd column of A:
  C(1) = -2;
  assert(A(1,2) == -2);


  // Reallocate:
  A.realloc(100,200);
  assert(A.size() == 100*200);

  // Get the data pointer from A.
  int *Aptr = A;

  // Resizing the array does not change the underlying
  // data pointer.
  A.resize(200,100);
  assert(Aptr == A);

  // Uninitalized arrays act like NULL.
  iarray E;
  assert(E == NULL);
}
