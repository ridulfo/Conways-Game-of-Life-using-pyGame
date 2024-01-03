# Conways Game of Life using pyGame with a FPS counter!


The current performance using a 100 x 100 grid is appalling. Coming in at a measly 11 FPS. This is due to all the for-loops and the use of numpy ndarrays to represent the grid.
An optimization would be to either vectorize the computation (using strides) or using numba's jit.


## Progress

### Update 2020-06-02 Part 1
After adding Numba's jit decorator the performance för a 200x200 grid at 24 FPS (100x100 90+ FPS).

#### UPDATE 2020-06-02 Part 2
During the drawing phase: instead of reading the values from the ndArray, the values are now read from a python list of lists. This almost tripled the performance. 200x200 grid at 60 FPS (100x100 170+ FPS).

### UPDATE 2020-06-02 Part 3
By suggestion from @SeraphWedd the drawing is now done without looping. Instead the pixels are taken directly from the data model. 200x200 grid at 125 FPS (100x100 170+ FPS).

### UPDATE 2024-01-03
Playing around with C and SDL I recreated this project and made it run at 500 FPS without optimizations.
