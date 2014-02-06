Program inputs 2 matrices (representing adjacency matrices) from an input file, in6.dat. 
Then it runs Warshall's and Depth First Search on each matrix while showing the user
how the algorithm works.  The result of the two matrices will be the transitive closure
of the original adjacency matrices

@pre program must be run in the command line
@pre in6.dat must be filled with matrice values separated by spaces 
     each new row separated by newline characters.  Furthermore, the first line of the
     matrix MUST BE THE INTEGER VALUE OF THE SIZE OF ONE DIMENSION OF THE MATRIX.
     for example:
@    3
@    0 1 1
@    1 0 0
@    0 0 0
@post prints out the guided two algorithms and their respective transitive closures
@file prog6.cpp
@author Nathaniel Wendt (nwendt)
@date 4/15/2013
