# lilavati
Some numerical analysis codes written in `C`.

I have been writing those codes since the beginning of 2017. I am quite interested in numerical analysis to simulate physical systems and to analyze data. Since I dedicate only my free time to develop this project, there is not many stuff to see here yet. Currently, one can found here:
- Dynamical allocation of `double` vectors and matrices (see `auxiliary-commands.c` file for this item and the next one);
- Usage of files to import and to export data (e.g. to import or to export a matrix elements from or to a file);
- Matrix and vector operations (see `matrices-and-vectors.c` file):
  - Addition, multiplication and other elementary operations;
  - LU and Cholesky decompositions (Gauss elimination function on going);
  - Determinant calculation for simple matrices and by LU and Cholesky decomposition;
  - Linear system solving by LU decomposition.
- Divided differences, Chebysev nodes, Lagrange interpolating polynomials (see `interpolation-and-approximation` file);
- Complex numbers (see `complex-numbers.c`):
  - Cartesian and polar coordinates of a complex number gathered into a `struct`;
  - Addition, multiplication, exponentiation and complex conjugate calculations;
  - Setting of complex vectors and matrices.
  
I am writing those functions to apply what I have learned in numerical analysis classes and also to assist my research project activities. I expect they may assist you too! :jack_o_lantern:
  

M. Miotti (@ravenpeak). April 7th, 2017.
