#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI		3.14159265359
#define HALF_PI		1.57079632679
#define THREE_HALF_PI	4.57079632679
#define E 		2.71828182846

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	1. ALLOCATION OF MATRICES AND VECTORS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//=====================================================
//	1.1. ALLOCATING AND DELETING A 'float' VECTOR
//=====================================================
// This function allocates dynamically a n-dimensional vector.
int alloc_fvec( int n, float **V ) {
	*V = ( float* ) malloc( n * sizeof( float ) );

	if( *V == NULL ) {
		return( -1 );
	}
	return( 0 );
}
// This function sets free a real vector.
int free_fvec( float **V ) {
	free( *V );
	*V = NULL;

	return( 0 );
}
//=====================================================
//	1.2. ALLOCATING AND DELETING A 'float' MATRIX
//=====================================================
// This function allocates dynamically a real matrix of n rows and m collumns.
int alloc_fmat( int n, int m, float ***A ) {
	int i;
	
	*A = ( float** ) malloc( n * sizeof( float* ) );

	if( *A == NULL ) {
		return( -1 );
	}

	for( i = 0; i < n; i++ ) {
		( *A )[i] = ( float* ) malloc( m * sizeof( float ) );

		if( ( *A )[i] == NULL ) {
			return( -1 );
		}
	}
	return( 0 );
}
// This function sets free a n-row real matrix.
int free_fmat( int n, float ***A ) {
	int i;

	for( i = 0; i < n; i++ ) {
		free( ( *A )[i] );
		( *A )[i] = NULL;
	}
	free( *A );
	*A = NULL;

	return( 0 );
}
//=====================================================
//	1.3. ALLOCATING AND DELETING A 'char' VECTOR
//=====================================================
// This function allocates dynamically a n-dimensional 'char' vector.
int alloc_chvec( int n, char **V ) {
	*V = ( char* ) malloc( n * sizeof( char ) );

	if( *V == NULL ) {
		return( -1 );
	}
	return( 0 );
}
// This function sets free a 'char' vector.
int free_chvec( char **V ) {
	free( *V );
	*V = NULL;

	return( 0 );
}
//=====================================================
//	1.4. ALLOCATING AND DELETING A 'char' MATRIX
//=====================================================
// This function allocates dynamically a 'char' matrix of n rows and m collumns.
int alloc_chmat( int n, int m, char ***A ) {
	int i;
	
	*A = ( char** ) malloc( n * sizeof( char* ) );

	if( *A == NULL ) {
		return( -1 );
	}

	for( i = 0; i < n; i++ ) {
		( *A )[i] = ( char* ) malloc( m * sizeof( char ) );

		if( ( *A )[i] == NULL ) {
			return( -1 );
		}
	}
	return( 0 );
}
// This function sets free a n-row 'char' matrix.
int free_chmat( int n, char ***A ) {
	int i;

	for( i = 0; i < n; i++ ) {
		free( ( *A )[i] );
		( *A )[i] = NULL;
	}
	free( *A );
	*A = NULL;

	return( 0 );
}

//=============================================================
//	1.5. GETTING 'float' VECTOR COORDINATES FROM A FILE
//=============================================================
// This functions gets 'float' values from a file and commits them to a single n-dimensional vector V. That file must be inside a 'files' folder and its name with the format extension must not be longer than fourty characters.
int get_fvec( int n, float *V, char filename[] ) {
	FILE	*file;
	int 	i;
	char	*AUX;

	alloc_chvec( 46, &AUX );
	strcpy( AUX, "files/" );
	strcat( AUX, filename );

	file = fopen( AUX, "r" );
	if ( file == NULL ) {
		return( -1 );
	}
	else {
		for( i = 0; i < n; i++ ) {
			fscanf( file, "%f\n", &V[i] );
		}
	}
	fclose( file );
	free_chvec( &AUX );

	return( 0 );
}
//==============================================================
//	1.5. WRITING 'float' COORDINATES OF A VECTOR IN A FILE
//==============================================================
// This functions writes the coordinates of a n-dimensional 'float' vector in a file. That file will be inside a 'files' folder and its name with the format extension must not be longer than fourty characters.
int out_fvec( int n, float *V, char filename[] ) {
	FILE	*file;
	int 	i;
	char	*AUX;

	alloc_chvec( 46, &AUX );
	strcpy( AUX, "files/" );
	strcat( AUX, filename );

	file = fopen( AUX, "w" );
	if ( file == NULL ) {
		return( -1 );
	}
	else {
		for( i = 0; i < n; i++ ) {
			fprintf( file, "%f\n", V[i] );
		}
	}
	fclose( file );
	free_chvec( &AUX );

	return( 0 );
}
//========================================================
//	1.7. GETTING 'float' MATRIX ELEMENTS FROM A FILE
//========================================================
// This functions gets 'float' values from a file and commits them to a n-row, m-column matrix A. That file must be inside a 'files' folder and its name with the format extension must not be longer than fourty characters.
int get_fmat( int n, int m, float **A, char filename[] ) {
	FILE	*file;
	int 	i, j;
	char	*AUXC;

	alloc_chvec( 46, &AUXC );
	strcpy( AUXC, "files/" );
	strcat( AUXC, filename );

	file = fopen( AUXC, "r" );
	if ( file == NULL ) {
		return( -1 );
	}
	else {
		for( i = 0; i < n; i++ ) {
			for( j = 0; j < m; j++ ) {
				if( j > 0 && j < m - 1 ) {
					fscanf( file, "\t%f", &A[i][j] );
				}
				else {
					if( j == 0 ) {
						fscanf( file, "%f", &A[i][j] );
					}
					else {
						fscanf( file, "\t%f\n", &A[i][j] );
					}
				}
			}
		}
	}
	fclose( file );
	free_chvec( &AUXC );

	return( 0 );
}
//===========================================================
//	1.8. WRITING 'float' ELEMENTS OF A MATRIX IN A FILE
//===========================================================
// This functions writes the elements of a n-row, m-column 'float' matrix in a file. That file will be inside a 'files' folder and its name with the format extension must not be longer than fourty characters.
int out_fmat( int n, int m, float **A, char filename[] ) {
	FILE	*file;
	int 	i, j;
	char	*AUXC;

	alloc_chvec( 46, &AUXC );
	strcpy( AUXC, "files/" );
	strcat( AUXC, filename );

	file = fopen( AUXC, "w" );
	if ( file == NULL ) {
		return( -1 );
	}
	else {
		for( i = 0; i < n; i++ ) {
			for( j = 0; j < m; j++ ) {
				if( j > 0 && j < m - 1 ) {
					fprintf( file, "\t%f", A[i][j] );
				}
				else {
					if( j == 0 ) {
						fprintf( file, "%f", A[i][j] );
					}
					else {
						fprintf( file, "\t%f\n", A[i][j] );
					}
				}
			}
		}
	}
	fclose( file );
	free_chvec( &AUXC );

	return( 0 );
}


/*
int main() {
	return( 0 );
}
*/
