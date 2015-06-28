#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "omp.h"
#define MUL 5

int main( int argc , char ** argv ){
	double start , end ;
	int chunk = 10 ;
	long **a , **b , **c ;

	int N = 500 ;

	if( argc == 2 ){
		N = atoi( argv[ 1 ] ) ;
		assert( N > 0 ) ;
	}

	int i , j ;
	a = ( long ** ) malloc( N * sizeof( long * ) ) ;
	b = ( long ** ) malloc( N * sizeof( long * ) ) ;
	c = ( long ** ) malloc( N * sizeof( long * ) ) ;

	for( i = 0 ; i < N ; i++){
		a[ i ] = ( long * ) malloc( N * sizeof( long ) ) ;
		b[ i ] = ( long * ) malloc( N * sizeof( long ) ) ;
		c[ i ] = ( long * ) malloc( N * sizeof( long ) ) ;
	}
	for( i = 0 ; i < N ; i++){
		for( j = 0 ; j < N ; j++){
			a[ i ][ j ] = i * MUL ;
			b[ i ][ j ] = i ;
			c[ i ][ j ] = 0 ;
		}
	}

	start = omp_get_wtime();
	#pragma omp parallel shared( a , b , c , chunk ) private ( i , j )
	{
		#pragma omp for schedule( static , chunk )
		for( i = 0 ; i < N ; i++){
			for( j = 0 ; j < N ; j++){
				c[ i ][ j ] = a[ i ][ j ] + b[ i ][ j ] ;
			}
		}
	}

	end = omp_get_wtime() ;
	printf( "TIME: %.6lf\n" , end - start ) ;
}
