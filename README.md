# Conways Game of Life using pyGame with a FPS counter!

[UPDATE 2020-06-02]
After adding Numba's jit decorator the performance för a 200x200 grid is 24 FPS (100x100 90+ FPS).

The current performance using a 100 x 100 grid is appalling. Coming in at a measly 11 FPS. This is due to all the for-loops and the use of numpy ndarrays to represent the grid.
An optimization would be to either vectorize the computation (using strides) or using numba's jit.

