#include "auxiliary-commands.c"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	1. VECTOR OPERATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	1.1. SUMMATION OF TWO VECTORS
//=================================================
/* This function sums two n-dimensional vectors, V and U, and the
   result is set into a vector W.
*/
void sum_rvec( int n, double *V, double *U, double *W ) {
	int i;

	for( i = 0; i < n; i++ ) {
	  W[i] = V[i] + U[i];
	}
	return;
}
//====================================================
//	1.2. MULTIPLICATION OF A VECTOR BY A SCALAR.
//====================================================
/* This function multiplies a n-dimensional vector V by a scalar k,
   and the result is set into a vector U.
*/
void smult_rvec( double k, int n, double *V, double *U ) {
	int i;

	for( i = 0; i < n; i++ ) {
	  U[i] = k * V[i];
	}
	return;
}
//==============================================================
//	1.3. INNER VECTOR PRODUCT (DOT PRODUCT OF TWO VECTORS)
//==============================================================
/* This function returns the dot product of two n-dimensional vectors,
   V and U.
*/
double dot_rvec( int n, double *V, double *U) {
	int i;
	double dot;

	dot = 0;
	for( i = 0; i < n; i++ ) {
	  dot = dot + V[i] * U[i];
	}
	return( dot );
}
//==============================================================
//	1.4. CROSS PRODUCT OF TWO 3-DIMENSIONAL VECTORS
//==============================================================
/* This function performs the cross product of two 3-dimensional
   vectors, V and U, and the result is set into a vector W.
*/
void cross3_rvec( double *V, double *U, double *W ) {
	W[0] = V[1] * U[2] + V[2] * U[1];
	W[1] = V[2] * U[0] + V[0] * U[2];
	W[2] = V[0] * U[1] + V[1] * U[0];

	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	2. TYPES OF MATRICES
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	2.1. TRANSPOSE OF A MATRIX
//=================================================
/* This function receives a n-X-m matrix A and finds its transpose,
   a m-X-n matrix T.
*/
void trans_rmat( int n, int m, double **A, double **T ) {
	int i, j;

	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < m; j++ ) {
	    T[j][i] = A[i][j];
	  }
	}
	return;
}
//=================================================
//	2.2. ZERO MATRIX
//=================================================
/* This function receives a n-X-m matrix A and makes all its elements
   equal to zero.
*/
void zero_rmat( int n, int m, double **A ) {
	int i, j;

	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < m; j++ ) {
	    A[i][j] = 0;
	  }
	}
	return;
}
//=================================================
//	2.3. IDENTITY MATRIX
//=================================================
/* This function makes a n-X-n square matrix A equal to an n-X-n
   identity matrix.
*/
void ident_rmat( int n, double **A ) {
	int i;

	zero_rmat( n, n, A );
	for( i = 0; i < n; i++ ) {
	  A[i][i] = 1;
	}
	return;
}
//=================================================
//	2.4. UPPER TRIANGULAR MATRIX
//=================================================
/* This function makes all the elements below the main diagonal of a
   n-X-n square matrix A equal to zero.
*/
void up_rmat( int n, double **A ) {
	int i, j;

	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < i; j++ ) {
	    A[i][j] = 0;
	  }
	}
	return;
}
//=================================================
//	2.5. LOWER TRIANGULAR MATRIX
//=================================================
/* This function makes all the elements above the main diagonal of a
   n-X-n square matrix A equal to zero.
*/
void low_rmat( int n, double **A ) {
	int i, j;

	for( i = 0; i < n; i++ ) {
	  for( j = i + 1; j < n; j++ ) {
	    A[i][j] = 0;
	  }
	}
	return;
}
//=================================================
//	2.6. DIAGONAL MATRIX
//=================================================
/* This function makes all the elements off the main diagonal of a
   n-X-n square matrix A equal to zero.
*/
void diag_rmat( int n, double **A ) {
	up_rmat( n, A );
	low_rmat( n, A );
	return;
}
//=================================================
//	2.7. VANDERMONDE MATRIX
//=================================================
/* This function receives a m-dimensional vector V and, from its
   elements, makes a n-X-m Vandermonde matrix M, which second line's
   elements are the m elements of the vector.
*/
void vand_rmat( int n, int m, double *V, double **M ) {
	int i, j;

	for( j = 0; j < m; j++ ) {
	  M[0][j] = 1;
	}
	for( i = 1; i < n; i++ ) {
	  for( j = 0; j < m; j++ ) {
	    M[i][j] = pow( V[j], i );
	  }
	}
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	3. MATRIX OPERATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	3.1. SUMMATION OF TWO MATRICES
//=================================================
/* This function sums two n-X-m real matrices, A and B, and the
   result is set into a n-X-m matrix C.
*/
void sum_rmat( int n, int m, double **A, double **B, double **C ) {
	int i, j;

	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < m; j++ ) {
	    C[i][j] = A[i][j] + B[i][j];
	  }
	}
	return;
}
//===================================================
//	3.2. MULTIPLICATION OF A MATRIX BY A SCALAR
//===================================================
/* This function multiplies a scalar k by a n-X-m real matrix A, and
   the result is set into a matrix B.
*/
void smult_rmat( double k, int n, int m, double **A, double **B ) {
	int i, j;

	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < m; j++ ) {
	    B[i][j] = k * A[i][j];
	  }
	}
	return;
}
//===================================================
//	3.3. MULTIPLICATION OF TWO MATRICES
//===================================================
/* This function multiplies a n-X-m real matrix A and m-X-p real
   matrix B, and the result is set into a n-X-p matrix C.
*/
void mult_rmat( int n, int m, int p, double **A, double **B,
                double **C ) {
	int i, j, k;

	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < p; j++ ) {
	    C[i][j] = 0;

	    for( k = 0; k < m; k++ ) {
	      C[i][j] = C[i][j] + A[i][k] * B[k][j];
	    }
	  }
	}	
	return;
}
//===================================================
//	3.4. DOUBLE-DOT MATRIX PRODUCT
//===================================================
/* This function returns the double dot product of two n-X-m matrices,
   A and B.
*/
double dbdot_rmat( int n, int m, double **A, double **B ) {
	int i, j;
	double dbdot;

	dbdot = 0;
	for( i = 0; i < n; i++ ) {
	  for( j = 0; j < m; j++ ) {
	    dbdot = dbdot + A[i][j] * B[i][j];
	  }
	}
	return( dbdot );
}
//===================================================
//	3.5. POWER OF A MATRIX
//===================================================
/* This function calculates the p-th power of a n-X-n square matrix A,
   and the result is set into a square matrix B.
*/
void pow_rmat( int p, int n, double **A, double **B ) {
	int i;

	mult_rmat( n, n, n, A, A, B );
	for( i = 2; i < p; i++ ) {
	  mult_rmat( n, n, n, B, A, B );
	}
	return;
}
//================================================================
//	3.6. INNER PRODUCT (DOT PRODUCT) OF TWO SLENDER MATRICES
//================================================================
/* Case 1. This function returns the dot product of two 1-X-n row
   matrices, A and B.
*/
double dotrow_rmat( int n, double **A, double **B ) {
	int j;
	double dot;

	dot = 0;
	for( j = 0; j < n; j++ ) {
	  dot = dot + A[0][j] * B[0][j];
	}
	return( dot );
}
/* Case 2. This function returns the dot product of two n-X-1 collumn
   matrices, A and B.
*/
double dotcol_rmat( int n, double **A, double **B ) {
	int j;
	double dot;

	dot = 0;
	for( j = 0; j < n; j++ ) {
	  dot = dot + A[0][j] * B[0][j];
	}
	return( dot );
}
//================================================================
//	3.7. LU DECOMPOSITION
//================================================================
/* This function receives three n-X-n square matrices, A, L and U. L
   and U are lower and upper triangular matrices, respectively, and
   their elements will be calculated to provide L * U = A. To
   simplify the calculations, all the elements of L's main diagonal
   will be equal to 1.
*/
void ludecomp_rmat( int n, double **A, double **L, double **U ) {
	int i, j, k;
	double sumlu;

	zero_rmat( n, n, U ); // U is set as a zero matrix.
	ident_rmat( n, L );   // L is set as a identity matrix.

	// Setting U's 0-X-i elements and L's i-X-0 elements.
	for( i = 0; i < n; i++ ) {
	  U[0][i] = A[0][i]; // A[0][0] must not be zero.
	  L[i][0] = A[i][0] / U[0][0];
	}
	L[0][0] = 1;

	for( i = 1; i < n; i++ ) { // Calculating L and U.
	  for( j = 1; j < n; j++ ) { // U's elements.
	    if( j >= i ) {
	      sumlu = 0;

	      for( k = 0; k < i; k++ ) {
	        sumlu = sumlu + L[i][k]*U[k][j];
	      }
	      U[i][j] = A[i][j] - sumlu;
	    }
	  }	
	  for( j = 1; j < n; j++ ) { // L's elements
	    if( j > i ) {
	      sumlu = 0;

	      for( k = 0; k < i; k++ ) {
	        sumlu = sumlu + L[j][k]*U[k][i];
	      }
	      L[j][i] = (A[j][i] - sumlu)/U[i][i];
	    }
	  }
	}
	return;
}
//================================================================
//	3.8. CHOLESKY DECOMPOSITION
//================================================================
/* This function receives a n-X-n square matrix U and finds a n-X-n
   upper triangular matrix U, which fits the relation
   A = U * transpose( U ), applied in Cholesky decomposition. The
   following algorithm performs decomposition by column.
*/
void choldecomp_rmat( int n, double **A, double **U ) {
	int i, j, k;
	double sum;

	// Setting U's first-row elements.
	U[0][0] = sqrt( A[0][0] ); // A[0][0] must not be zero.
	for( i = 1; i < n; i++ ) {
	  U[i][0] = A[i][0] / U[0][0];
	}

	for( j = 1; j < n; j++ ) { // Calculating U.
	  sum = 0;

	  for( k = 0; k < j; k++ ) {
	    sum = sum + U[j][k] * U[j][k];
	  }
	  U[j][j] = sqrt( A[j][j] - sum );

	  for( i = j + 1; i < n; i++ ) {
	    sum = 0;

	    for( k = 0; k < j; k++ ) {
	      sum = sum + U[i][k] * U[j][k];
	    }
	    U[i][j] = ( A[i][j] - sum ) / U[j][j];
	  }
	}
	return;
}

//ON GOING!
//====================================================================
//	3.9. TRIANGULAR MATRIX FACTORIZATION WITH COLUMN PIVOT SEARCH
//====================================================================
/* This function receives a nonsingular (n,n) matrix A and searchs for
   an appropriate column pivot and
*/
int cpivot_rmat( int n, double **A, double *P ) {
	int i, j, k, m;

	for( i = 0; i < n; i++ ) { // Singularity check.
	  if( A[i][i] == 0 ) {
	    printf( "Input matrix is numerically singular.\n" );
	    return( -1 );
	  }
	}

	m = n - 1;
	for( j = 0; i < m; j++ ) {
	  for( i = j + 1; i <= m; i++ ) {
	    A[i][j] = A[i][j]/A[j][j];
	    for( k = j + 1; k <= m; k++ ) {
	      A[i][k] = A[i][k] - A[j][k]*A[i][j];
	    }
	  }
	}
	return(0);
}
// ON GOING!

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	4. MATRIX DETERMINANTS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	4.1. (1,1) MATRIX DETERMINANT
//=================================================
/* This function returns the determinant of a 1-X-1 square matrix A.
*/
double det1_rmat( double **A ) {
	return( A[0][0] );
}
//=================================================
//	4.2. (2,2) MATRIX DETERMINANT
//=================================================
/* This function returns the determinant of a 2-X-2 square matrix A.
*/
double det2_rmat( double **A ) {
	double det;

	det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
	return( det );
}
//=================================================
//	4.3. (3,3) MATRIX DETERMINANT
//=================================================
/* This function returns the determinant of a 3-X-3 square matrix A.
*/
double det3_rmat( double **A ) {
	double det;

	det = A[0][1] * A[1][2] * A[2][0];
	det = det - A[0][0] * A[1][2] * A[2][1];
	det = det + A[0][2] * A[1][0] * A[2][1];
	det = det - A[0][1] * A[1][0] * A[2][2]; 
	return( det );
}
//========================================================
//	4.4. DIAGONAL AND TRIANGULAR MATRIX DETERMINANT
//========================================================
// This function returns the determinant of a n-X-n triangular or diagonal matrix A.
double ditridet_rmat( int n, double **A ) {
	int i;
	double det = A[0][0];

	for( i = 1; i < n; i++ ) {
	  det = det * A[i][i];
	}
	return( det );
}
//========================================================
//	4.5. DETERMINANT CALCULATION BY LU DECOMPOSITION
//========================================================
// This functions uses LU decomposition to calculate the determinant of a n-X-n square matrix A. The function returns the determinant value.
double ludet_rmat( int n, double **A ) {
	double det, **L, **U;

	alloc_rmat( n, n, &L );      // L matrix.
	alloc_rmat( n, n, &U );      // U matrix.
	ludecomp_rmat( n, A, L, U ); // L's and U's elements.
	det = ditridet_rmat( n, U ); // det(L) = 1. (^-^)

	free_rmat( n, &L );
	free_rmat( n, &U );
	return( det );
}
//================================================================
//	4.6. DETERMINAT CALCULATION BY CHOLESKY DECOMPOSITION
//================================================================
// This functions uses Cholesky decomposition by column to calculate and return the determinant of a n-X-n square matrix A.
double choldet_rmat( int n, double **A ) {
	int i, j;
	double det, **U;

	alloc_rmat( n, n, &U );     // Upper triangular matrix.
	choldecomp_rmat( n, A, U ); // U's elements.

	det = ditridet_rmat( n, U );
	// The matrix and its tranpose determinants.
	det = det * det;

	free_rmat( n, &U );
	return( det );
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	5. SYSTEMS OF LINEAR ALGEBRAIC EQUATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//============================================================
//	5.1. SOLVING OF A LINEAR SYSTEM BY LU DECOMPOSITION
//============================================================
/* This function employs LU decomposition to solve a linear system
   A * X = B, which A is a n-X-n square matrix, b is a n-X-1
   slender matrix and X is the solution of the system.
*/
void lusolve_rmat( int n, double **A, double **X, double **B ) {
	int i, j;
	double sum, **L, **U, **Y; // Auxiliary matrices.
	
	alloc_rmat( n, n, &L );
	alloc_rmat( n, n, &U );
	alloc_rmat( n, 1, &Y );
	ludecomp_rmat( n, A, L, U ); // A*X=L*(U*X)=L*Y=B.

	Y[0][0] = B[0][0]; // Y's calculation (L*Y=B).
	for( i = 1; i < n; i++ ) {
	  sum = 0;
	  for( j = 0; j < i; j++ ) {
	    sum = sum + L[i][j] * Y[j][0];
	  }
	  Y[i][0] = B[i][0] - sum;
	}

	// X's calculation (U*X=Y)
	X[n - 1][0] = Y[n - 1][0] / U[n - 1][n - 1];
	for( i = n - 2; i >= 0; i-- ) {
	  sum = 0;
	  for( j = n - 1; j >= 0; j-- ) {
	    sum = sum + U[i][j] * X[j][0];
	  }		
	  X[i][0] = ( Y[i][0] - sum ) / U[i][i];
	}

	free_rmat( n, &L );
	free_rmat( n, &U );
	free_rmat( n, &Y );
	return;
}

// Main function.
int main() {
	double **mA, *vA;

	alloc_rmat( 3, 3, &mA );
	alloc_rvec( 3, &vA );

	get_rmat( 3, 3, mA, "mat.in" );
	//get_rvec( 3, vA, "vec.in" );

	cpivot_rmat( 3, mA, vA );
	out_rmat( 3, 3, mA, "mat.out" );
	out_rvec( 3, vA, "vec.out" );

	free_rmat( 3, &mA );
	free_rvec( &vA );
	return( 0 );
}
