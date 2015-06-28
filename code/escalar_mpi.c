#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#define ROOT 0
#define MUL 5
#define TAM 32268

int main( int argc , char * argv[] ){
	int myrank , npes ;
	double start , end ;
	MPI_Init( &argc , &argv ) ;
	MPI_Comm_size( MPI_COMM_WORLD , &npes ) ;
	MPI_Comm_rank( MPI_COMM_WORLD , &myrank ) ;
	int nElemPerProcess = TAM / npes ;
	int product[ TAM ] , sender ;
	int myA[ nElemPerProcess ] , myB[ nElemPerProcess ] , myV[ nElemPerProcess ] , i ;
	// Every process generate vectors A and B
	for( i = 0 ; i < nElemPerProcess ; i++){
		myA[ i ] = ( i + 1 ) * ( myrank + 1 ) ;
		myB[ i ] = ( i + 1 ) * ( myrank + 1 ) * MUL ;
	}
	if( myrank == ROOT ) start = MPI_Wtime() ;
	// Every process calculate their scalar product
	for( i = 0 ; i < nElemPerProcess ; i++){
		myV[ i ] = myA[ i ] * myB[ i ] ;
	}
	// Send scalar product to ROOT
	MPI_Send( myV , nElemPerProcess , MPI_INT , ROOT , 0 , MPI_COMM_WORLD ) ;
	if( myrank == ROOT ){
		MPI_Status status ;
		for( sender = 0 ; sender < npes ; sender++){
			MPI_Recv( product + nElemPerProcess * sender , nElemPerProcess , MPI_INT , sender , 0 , MPI_COMM_WORLD , &status ) ;
		}
		end = MPI_Wtime() ;
//		for( i = 0 ; i < TAM ; i++) printf("%d " , product[ i ] ) ; printf("\n" ) ;
		printf("TIME = %.6lf\n" , end - start ) ;
	}
	MPI_Finalize() ;
	return 0 ;
}
