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
//	1.1. ALLOCATING AND DELETING A 'double' VECTOR
//=====================================================
/* This function allocates dynamically a n-dimensional 'double'
   vector.
*/
int alloc_rvec( int n, double **V ) {
	*V = ( double* ) malloc( n * sizeof( float ) );

	if( *V == NULL ) {
	  return( -1 );
	}
	return( 0 );
}
/* This function sets free a 'double' vector.
*/
int free_rvec( double **V ) {
	free( *V );
	*V = NULL;

	return( 0 );
}
//=====================================================
//	1.2. ALLOCATING AND DELETING A 'double' MATRIX
//=====================================================
/* This function allocates dynamically a 'double' matrix of n rows
   and m collumns.
*/
int alloc_rmat( int n, int m, double ***A ) {
	int i;
	
	*A = ( double** ) malloc( n * sizeof( float* ) );

	if( *A == NULL ) {
	  return( -1 );
	}

	for( i = 0; i < n; i++ ) {
	  ( *A )[i] = ( double* ) malloc( m * sizeof( float ) );

	  if( ( *A )[i] == NULL ) {
	    return( -1 );
	  }
	}
	return( 0 );
}
/* This function sets free a n-row 'double' matrix.
*/
int free_rmat( int n, double ***A ) {
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
/* This function allocates dynamically a n-dimensional 'char' vector.
*/
int alloc_chvec( int n, char **V ) {
	*V = ( char* ) malloc( n * sizeof( char ) );

	if( *V == NULL ) {
	  return( -1 );
	}
	return( 0 );
}
/* This function sets free a 'char' vector.
*/
int free_chvec( char **V ) {
	free( *V );
	*V = NULL;

	return( 0 );
}
//=====================================================
//	1.4. ALLOCATING AND DELETING A 'char' MATRIX
//=====================================================
/* This function allocates dynamically a 'char' matrix of n rows and
   m collumns.
*/
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
/* This function sets free a n-row 'char' matrix.
*/
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
//	1.5. GETTING 'double' VECTOR COORDINATES FROM A FILE
//=============================================================
/* This functions gets 'double' values from a file and commits them
   to a single n-dimensional vector V. That file must be inside a
   folder named "files" and its name with the format extension must
   not be longer than fourty characters.
*/
int get_rvec( int n, double *V, char filename[] ) {
	FILE *file;
	int  i;
	char *AUX;

	alloc_chvec( 46, &AUX );
	strcpy( AUX, "files/" );
	strcat( AUX, filename );

	file = fopen( AUX, "r" );
	if ( file == NULL ) {
	  return( -1 );
	}
	else {
	  for( i = 0; i < n; i++ ) {
	    fscanf( file, "%lf\n", &V[i] );
	  }
	}
	fclose( file );
	free_chvec( &AUX );

	return( 0 );
}
/* This functions gets 'double' values in scientific notation from
   a file and commits them to a single n-dimensional vector V. That
   file must be inside a folder named "files" and its name with the
   format extension must not be longer than fourty characters.
*/
int sci_get_rvec( int n, double *V, char filename[] ) {
	FILE *file;
	int  i;
	char *AUX;

	alloc_chvec( 46, &AUX );
	strcpy( AUX, "files/" );
	strcat( AUX, filename );

	file = fopen( AUX, "r" );
	if ( file == NULL ) {
	  return( -1 );
	}
	else {
	  for( i = 0; i < n; i++ ) {
	    fscanf( file, "%e\n", &V[i] );
	  }
	}
	fclose( file );
	free_chvec( &AUX );

	return( 0 );
}
//==============================================================
//	1.5. WRITING 'double' COORDINATES OF A VECTOR IN A FILE
//==============================================================
/* This functions writes the coordinates of a n-dimensional 'double'
   vector in a file. That file will be created inside a folder named
   "files" and its name with the format extension must not be longer
   than fourty characters.
*/
int out_rvec( int n, double *V, char filename[] ) {
	FILE *file;
	int  i;
	char *AUX;

	alloc_chvec( 46, &AUX );
	strcpy( AUX, "files/" );
	strcat( AUX, filename );

	file = fopen( AUX, "w" );
	if ( file == NULL ) {
	  return( -1 );
	}
	else {
	  for( i = 0; i < n; i++ ) {
	    fprintf( file, "%.16lf\n", V[i] );
	  }
	}
	fclose( file );
	free_chvec( &AUX );

	return( 0 );
}
/* This functions writes the coordinates of a n-dimensional 'double'
   vector in a file. The 'double' elements will be expressed in
   scientific notation. That file will be created inside a folder
   named "files" and its name with the format extension must not be
   longer than fourty characters.
*/
int sci_out_rvec( int n, double *V, char filename[] ) {
	FILE *file;
	int  i;
	char *AUX;

	alloc_chvec( 46, &AUX );
	strcpy( AUX, "files/" );
	strcat( AUX, filename );

	file = fopen( AUX, "w" );
	if ( file == NULL ) {
	  return( -1 );
	}
	else {
	  for( i = 0; i < n; i++ ) {
	    fprintf( file, "%.16lf\n", V[i] );
	  }
	}
	fclose( file );
	free_chvec( &AUX );

	return( 0 );
}
//========================================================
//	1.7. GETTING 'double' MATRIX ELEMENTS FROM A FILE
//========================================================
/* This functions gets 'double' values from a file and commits them
   to a n-row, m-column matrix A. That file must be inside a folder
   named "files" and its name with the format extension must not be
   longer than fourty characters.
*/
int get_rmat( int n, int m, double **A, char filename[] ) {
	FILE *file;
	int  i, j;
	char *AUXC;

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
	        fscanf( file, "\t%lf", &A[i][j] );
	      }
	      else {
	        if( j == 0 ) {
	          fscanf( file, "%lf", &A[i][j] );
	        }
	        else {
	          fscanf( file, "\t%lf\n", &A[i][j] );
	        }
	      }
	    }
	  }
	}
	fclose( file );
	free_chvec( &AUXC );

	return( 0 );
}
/* This functions gets 'double' values in scientif notation from a
   file and commits them to a n-row, m-column matrix A. That file
   must be inside a folder named "files" and its name with the format
   extension must not be longer than fourty characters. Watch out the
   numbers' size!
*/
int sci_get_rmat( int n, int m, double **A, char filename[] ) {
	FILE *file;
	int  i, j;
	char *AUXC;

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
	        fscanf( file, "\t%e", &A[i][j] );
	      }
	      else {
	        if( j == 0 ) {
	          fscanf( file, "%e", &A[i][j] );
	        }
	        else {
	          fscanf( file, "\t%e\n", &A[i][j] );
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
//	1.8. WRITING 'double' ELEMENTS OF A MATRIX IN A FILE
//===========================================================
/* This functions writes the elements of a n-row, m-column 'double'
   matrix into a file. That file will be inside a folder named "files"
   and its name with the format extension must not be longer than
   fourty characters.
*/
int out_rmat( int n, int m, double **A, char filename[] ) {
	FILE *file;
	int  i, j;
	char *AUXC;

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
	        fprintf( file, "\t%.16lf", A[i][j] );
	      }
	      else {
	        if( j == 0 ) {
	          fprintf( file, "%.16lf", A[i][j] );
		}
	        else {
	          fprintf( file, "\t%.16lf\n", A[i][j] );
		}
	      }
	    }
	  }
	}
	fclose( file );
	free_chvec( &AUXC );

	return( 0 );
}
/* This functions writes the elements of a n-row, m-column 'double'
   matrix into a file. The 'double' elements will be expressed in
   scientific notation. That file will be created inside a folder
   named "files" and its name with the format extension must not be
   longer than fourty characters. Watch out the numbers' size!
*/
int sci_out_rmat( int n, int m, double **A, char filename[] ) {
	FILE *file;
	int  i, j;
	char *AUXC;

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
	        fprintf( file, "\t%.16e", A[i][j] );
	      }
	      else {
	        if( j == 0 ) {
	          fprintf( file, "%.16e", A[i][j] );
	        }
	        else {
	          fprintf( file, "\t%.16e\n", A[i][j] );
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
