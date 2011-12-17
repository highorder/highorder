import numpy as np
from basic_usage import doublify

A = np.array([1.1, 2.2, 3.3])

print "Before", A
doublify(A)
print "After ", A
