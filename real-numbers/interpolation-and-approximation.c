#include "auxiliary-commands.c"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	1. AUXILIARY COMMANDS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	1.1. DIVIDED DIFFERENCE
//=================================================
// This function receives two real numbers x0 and x1 and the divided differences f[x0] and f[x1] (which are dd0 and dd1, respectively) and returns the divided difference f[x0,x1].
double div_diff( float x0, float x1, float dd0, float dd1 ) {
	return( ( dd1 - dd0 ) / ( x1 - x0 ) );
}
// This function receives a table-valued function F (a n-X-2 matrix) and return the divided difference F[x_i-1,x_i], i = 1, ..., n - 1, and returns each value in a (n - 1)-element vector V.
void pair_div_diff( int n, double **F, float *V ) {
	int i;
	double num, den;

	for( i = 1; i < n; i++ ) {
		num = F[i][1] - F[i-1][1];
		den = F[i][0] - F[i-1][0];
		V[i] = num / den;
	}
	return;
}
// This function receives an one-variable, table-valued function F (a n-X-2 matrix) and, for two given orders k1 and k2, 1 < k1 < k2 <= n, it will calculate and return the divided difference f[x_k1,x_k2].
double gen_div_diff( int n, float **F, int k1, int k2 ) {
	int i;
	double *AUX;			// It will have the divided difference values for each pair (x_i-1,x_i) in the table-valued function.
	alloc_fvec( n - 1, &AUX );
	pair_div_diff( n, F, AUX );

	// Write the rest here.

	free_fvec( &AUX );
}
// This function receives an one-variable, table-valued function F (a n-X-2 matrix) and returns the divided difference F[I], which I is the full F domain. According to Schwaiger (1994) and Andersen (1996), there some restrictions in the following algorithm if n is greater or equal to 3. (See the WolframMathWorld's PDF)
double full_div_diff( int n, float **F ) {
	int	i, j;
	double	dd, prod, *dpi;		// dpi: first-derivative of pi polynomial.

	alloc_fvec( n, &dpi );

	for( i = 0; i < n; i++ ) {	// Calculting dpi elements.
		prod = 1;
		for( j = 0; j < n; j++ ) {
			if( j != i ) {
				prod = prod * ( F[i][0] - F[j][0] );
			}
		}
		dpi[i] = prod;
	}

	dd = 0;
	for( i = 0; i < n; i++ ) {
		dd = dd + ( F[i][1] / dpi[i] );
		printf( "i = %d: %lf, %f, %f\n", i + 1, dpi[i], F[i][1], F[i][1] / dpi[i] );
	}

	free_fvec( &dpi );
	return( dd );
}
//=================================================
//	1.2. CHEBYSHEV NODES
//=================================================
// This function returns the Chebyshev node for an i-th element of a n-element data set, which is given in the interval [-1,1].
double chnode( int i, int n ) {
	return( cos( PI * ( i / n ) ) );
}
// This function returns the Chebyshev node for an i-th element of a n-element data set, which is given in the interval [a,b], b > a.
double arbint_chnode( int i, int n, float a, float b ) {
	double cn;
	cn = ( 0.5 * ( a + b ) ) + ( ( 0.5 * ( b - a ) ) * chnode( i, n ) );
	return( cn );
}
// This function calculates the n + 1 Chebyshev nodes for a data set in the interval [a,b], b > a. The node values are set in increasing order into a (n+1)-element list vector L.
void set_chnome( int n, double a, float b, float *L ) {
	int i;
	for( i = 0; i < n; i++ ) {
		L[n-1-i] = arbint_chnode( i, n, a, b );
	}
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	2. INTERPOLATION
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	2.1. LAGRANGE INTERPOLATING POLYNOMIAL
//=================================================
// This function receives an one-variable, table-valued function F (essentially, a n-X-2 matrix), and for a given interval [a,b] with steps of c, it will be calculated the values of the Lagrange interpolation polynomial. The polynomial domain [a,b] and image will be written in a table-valued function L, which will be a [(b - a)/c + 1]-X-2 matrix.
void lagr_interp( double n, float **F, float a, float b, float c, float **L ) {
	int i, j, k, r;
	double *AUX, prod, sum;

	alloc_fvec( n, &AUX );
	r = ( b - a ) / c;

	for( i = 0; i <= r; i++ ) {
		L[i][0] = a + ( i * c );	// Setting polynomial domain values.
	}

	for( i = 0; i < n; i++ ) {		// Setting the auxiliary vector values.
		prod = 1;
		for( j = 0; j < n; j++ ) {
			if( i != j ) {
				prod = prod * ( F[i][0] - F[j][0] );
			}
		}
		AUX[i] = prod;
	}

	for( k = 0; k <= r ; k++ ) {
		sum = 0;
		for( j = 0; j < n ; j++ ) {
			prod = 1;
			for( i = 0; i < n ; i++ ) {
				if( i != j ) {
					prod = prod * ( L[k][0] - F[i][0] );
				}
			}
			prod = ( prod * F[j][1] ) / AUX[j];
			sum = sum + prod;
		}
		L[k][1] = sum;
	}
	free_fvec( &AUX );
	return;
}
/* This version, which uses no "IFs", seems to my naked eye just a little bit faster. I may check it in the future.
void lagr_2interp( double n, float **F, float a, float b, float c, float **L ) {
	int i, j, k, r;
	double *AUX, prod, sum;

	alloc_fvec( n, &AUX );
	r = ( b - a ) / c;

	for( i = 0; i <= r; i++ ) {
		L[i][0] = a + ( i * c );	// Setting polynomial domain values.
	}

	prod = 1;				// First elements of the auxiliary vector.
	for( j = 1; j < n; j++ ) {
		prod = prod * ( F[0][0] - F[j][0] );
	}
	AUX[0] = prod;

	for( i = 1; i < n; i++ ) {		// Setting the auxiliary vector values.
		prod = 1;
		for( j = 0; j < i; j++ ) {
			prod = prod * ( F[i][0] - F[j][0] );
		}
		for( j = i + 1; j < n; j++ ) {
			prod = prod * ( F[i][0] - F[j][0] );
		}
		AUX[i] = prod;
	}

	for( k = 0; k <= r ; k++ ) {
		sum = 0;
		prod = 1;
		for( i = 1; i < n; i++ ) {
			prod = prod * ( L[k][0] - F[i][0] );
		}
		prod = ( prod * F[0][1] ) / AUX[0];
		sum = sum + prod;

		for( j = 1; j < n ; j++ ) {
			prod = 1;
			for( i = 0; i < j; i++ ) {
				prod = prod * ( L[k][0] - F[i][0] );
			}
			for( i = j + 1; i < n; i++ ) {
				prod = prod * ( L[k][0] - F[i][0] );
			}
			prod = ( prod * F[j][1] ) / AUX[j];
			sum = sum + prod;
		}
		L[k][1] = sum;
	}
	free_fvec( &AUX );
	return;
}

int main() {
}

