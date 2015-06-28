#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#define ROOT 0
#define MUL 5
#define TAM 32
#define TMAT TAM * TAM

int main( int argc , char * argv[] ){
	int myrank , npes ;
	double start , end ;
	MPI_Init( &argc , &argv ) ;
	MPI_Comm_size( MPI_COMM_WORLD , &npes ) ;
	MPI_Comm_rank( MPI_COMM_WORLD , &myrank ) ;
	int nRowsPerProcess = TAM / npes ;
	int a[ TMAT ] , b[ TMAT ] , sum[ TMAT ] , sender , target ;
	int myA[ nRowsPerProcess * TAM ] , i , k ;
	if( myrank == ROOT ){
		for( i = 0 ; i < TAM ; i++){
			for( j = 0 ; j < TAM ; j++){
				a[ i * TAM + j ] = ( i + j ) ;
				b[ i * TAM + j ] = ( i + j ) * MUL ;
				sum[ i * TAM + j ] = 0 ;
			}
		}
		// ROOT send part of matrix a to other process
		for( target = 0 ; target < npes ; target++ )
			MPI_Send( a + target * TAM * nRowsPerProcess , TAM * nRowsPerProcess , MPI_INT , target , target , MPI_COMM_WORLD ) ;
	}
	if( myrank == ROOT ) start = MPI_Wtime() ;
	MPI_Bcast( b , TMAT , MPI_INT , 0 , MPI_COMM_WORLD ) ;
	MPI_Status status ;
	MPI_Recv( myA , TAM * nRowsPerProcess , MPI_INT , ROOT , myrank , MPI_COMM_WORLD , &status ) ;
	int frow = myrank * nRowsPerProcess ;
	for( k = 0 ; k < nRowsPerProcess ; k++)
		for( i = 0 ; i < TAM ; i++)
			sum[ ( k + frow ) * TAM + i ] = myA[ ( k + frow ) * TAM + i ] + b[ ( k + frow ) * TAM + i ] ;
	MPI_Send( sum + TAM * frow , TAM * nRowsPerProcess , MPI_INT , ROOT , myrank , MPI_COMM_WORLD ) ;
	if( myrank == ROOT ){
		// ROOT receives calculations of all process and combines in matrix sum
		for( sender = 0 ; sender < npes ; sender++ )
			MPI_Recv( sum + TAM * nRowsPerProcess * sender , TAM * nRowsPerProcess , MPI_INT , sender , sender , MPI_COMM_WORLD , &status ) ;
		printf("MATRIX PRODUCT\n" ) ;
		for( i = 0 ; i < TAM ; i++){ for( j = 0 ; j < TAM ; j++) printf("%d " , sum[ i * TAM + j ] ) ; printf("\n" ) ; } printf("\n" ) ;
		end = MPI_Wtime() ;
		printf("TIME = %.6lf\n" , end - start ) ;
	}
	MPI_Finalize() ;
	return 0 ;
}
