import numpy as np

x = np.array([1, 2, 3])
h = np.array([1, 1, 1])
y_ref = np.convolve(x, h, mode="full")[:len(x)]
print(y_ref)