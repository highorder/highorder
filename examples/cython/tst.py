import numpy as np
from basic_usage import doublify

A = np.array([[1.1, 2.2], [3.3, 4.4]], order='F')

print "Before:\n", A
doublify(A)
print "After:\n", A

# Note order='F' is important, as `doublify(A.T)` will raise a ValueError
# because the array is not in Fortan order.
