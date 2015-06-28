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

	long *a , *b , *c ;
	int N = 500 ;

	if( argc == 2 ){
		N = atoi( argv[ 1 ] ) ;
		assert( N > 0 ) ;
	}

	int i , j ;
	a = ( long * ) malloc( N * sizeof( long ) ) ;
	b = ( long * ) malloc( N * sizeof( long ) ) ;
	c = ( long * ) malloc( N * sizeof( long ) ) ;

	for( i = 0 ; i < N  ; i++){
		a[ i ] = i * mul ;
		b[ i ] = i ;
		c[ i ] = 0 ;
	}

	start = omp_get_wtime() ;
	#pragma omp parallel shared( a , b , c , chunk ) private( i , j )
	{
		#pragma omp for schedule( static , chunk )
		for( i = 0 ; i < N ; i++){
			c[ i ] = a[ i ] * b[ i ] ;
		}
	}
	end = omp_get_wtime();
	printf("TIME: %.6lf\n" , end - start ) ;
}
