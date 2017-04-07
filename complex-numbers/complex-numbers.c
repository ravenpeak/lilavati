#include "auxiliary-commands.c"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	1. COMPLEX NUMBERS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	1.1. COMPLEX-NUMBER STRUCT
//=================================================
// This struct shows a complex number in its cartesian and polar representations.
typedef struct {
	float 	real,	// Cartesian coordinates' real part.
		imag,	// Cartesian coordinates' imaginary part.
		mod,	// Polar coordinates' modulus.
		arg;	// Polar coordinates' argument.
} Complex;
//===========================================================================
//	1.2. SETTING COMPLEX-NUMBER VALUES FROM ITS CARTESIAN COORDINATES
//===========================================================================
// This function receives the cartesian coordinates (a,b) of a complex number and sets its polar coordinates.
void cart_cpx( Complex *Z, float a, float b ) {

	( *Z ).real = a;				// Real part of the cartesian coordinates.
	( *Z ).imag = b;				// Imaginary part of the cartesian coordinates.

	( *Z ).mod = sqrt( a * a + b * b );		// Modulus of the polar coordinates.
	
	if( a == 0 && b == 0 ) {			// Argument of the polar coordinates. It will be within [0, 2*pi).
		( *Z ).arg = 0;
	}
	else{
		if( a > 0 && b == 0 ) {
			( *Z ).arg = 0;
		}
		else {
			if( a < 0 && b == 0 ) {
				( *Z ).arg = PI;
			}
			else {
				if( a == 0 && b > 0 ) {
					( *Z ).arg = HALF_PI;
				}
				else {
					if( a == 0 && b < 0 ) {
						( *Z ).arg = THREE_HALF_PI;
					}
					else {
						if( a > 0 && b > 0 ) {
							( *Z ).arg = atan( b / a );
						}
						else {
							if( a < 0 && b > 0 ) {
								( *Z ).arg = atan( b / -a ) + HALF_PI;
							}
							else {
								if( a < 0 && b < 0 ) {
									( *Z ).arg = atan( b / a ) + PI;
								}
								else {
									( *Z ).arg = atan( -b / a ) + THREE_HALF_PI;
								}
							}
						}
					}
				}
			}
		}
	}
	return;
}
//===========================================================================
//	1.3. SETTING COMPLEX-NUMBER VALUES FROM ITS POLAR COORDINATES
//===========================================================================
// This function receives the polar coordinates (p,F) of a complex number and sets its cartesian coordinates.
void pol_cpx( Complex *Z, float p, float F ) {
	( *Z ).mod = p;
	( *Z ).arg = F;
	( *Z ).real = p * cos( F );
	( *Z ).imag = p * sin( F );

	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	2. ALLOCATION OF COMPLEX MATRICES AND VECTORS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=================================================
//	2.1. ALLOCATING AND DELETING A VECTOR
//=================================================
// This function allocates dynamically a n-dimensional complex vector V.
int alloc_cvec( int n, Complex **V ) {
	*V = ( Complex* ) malloc( n * sizeof( Complex ) );

	if( *V == NULL ) {
		return( -1 );
	}
	return( 0 );
}
// This function sets free a complex vector.
int free_cvec( Complex **V ) {
	free( *V );
	*V = NULL;

	return( 0 );
}
//=================================================
//	2.2. ALLOCATING AND DELETING A MATRIX
//=================================================
// This function allocates dynamically a n-X-m complex matrix A.
int alloc_cmat( int n, int m, Complex ***A ) {
	int i;
	
	*A = ( Complex** ) malloc( n * sizeof( Complex* ) );

	if( *A == NULL ) {
		return( -1 );
	}

	for( i = 0; i < n; i++ ) {
		( *A )[i] = ( Complex* ) malloc( m * sizeof( Complex ) );

		if( ( *A )[i] == NULL ) {
			return( -1 );
		}
	}
	return( 0 );
}
// This function sets free a n-row complex matrix.
int free_cmat( int n, Complex ***A ) {
	int i;

	for( i = 0; i < n; i++ ) {
		free( ( *A )[i] );
		( *A )[i] = NULL;
	}
	free( *A );
	*A = NULL;

	return( 0 );
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	3. COMPLEX-NUMBER OPERATIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NOTE: The Complex-struct numbers must be set with cart_cpx() or pol_cpx() functions before any operation be performed.
//=================================================
//	3.1. SUMMATION OF COMPLEX NUMBERS
//=================================================
// This function sums two complex numbers, Z and W, and the result is a number U.
void sum_cpx( Complex Z, Complex W, Complex *U ) {
	cart_cpx( U, Z.real + W.real, Z.imag + Z.imag );

	return;
}
//===========================================================
//	3.2. MULTIPLICATION OF A COMPLEX NUMBER BY A SCALAR
//===========================================================
// This function multiplies a complex numbers Z by a scalar k, and the result is a number W.
void smult_cpx( float k, Complex Z, Complex *W ) {
	pol_cpx( W, k * Z.mod, Z.arg );

	return;
}
//===========================================================
//	3.3. MULTIPLICATION OF COMPLEX NUMBERS
//===========================================================
// This function multiplies two complex numbers, Z and W, and the result is a number U.
void mult_cpx( Complex Z, Complex W, Complex *U ) {
	pol_cpx( U, Z.mod * W.mod, Z.arg + W.arg );

	return;
}
//===========================================================
//	3.4. POWER OF COMPLEX NUMBERS
//===========================================================
// This function calculates the p-th power of a complex numbers Z, and the result is a number W.
void pow_cpx( int p, Complex Z, Complex *W ) {
	int i;

	mult_cpx( Z, Z, W );
	for( i = 2; i < p; i++ ) {
		mult_cpx( *W, Z, W );
	}
	return;
}
//=======================================================================
//	3.5. EXPONENTIATION OF A COMPLEX NUMBER TO OTHER COMPLEX NUMBER
//=======================================================================
// This functions calculates a complex number Z raised to a complex number W, and the result is a number U.
void cpow_cpx( Complex Z, Complex W, Complex *U ) {
	pol_cpx( U, exp( W.real * log( Z.mod ) - Z.arg * W.imag ), W.real * Z.arg + W.imag * log( Z.mod ) );

	return;
}
//=================================
//	3.6. COMPLEX CONJUGATION
//=================================
// This function calculates the complex conjugate of a complex number Z, and the result is a number W.
void conj_cpx( Complex Z, Complex *W ) {
	cart_cpx( W, Z.real, -Z.imag );

	return;
}

int main() {
}
