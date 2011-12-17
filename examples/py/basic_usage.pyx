from highorder.arrays cimport *
from cython.operator cimport dereference as deref

# This line must be included to prevent segmentation faults.
import_array()

cdef extern from "doublify.h":
    void doublify_c "doublify" (array[double]&) # Rename doublify to doublify_c

def doublify(obj):
    doublify_c(deref(view_d(obj)))
