use Time ;
use Random ;

/* ======== START CONFIG VARIABLES ======== */
config const n = 100000000 ;
/* ======== END CONFIG VARIABLES ======== */

var timer : Timer ;

var A : [ 0..n-1 ] real ;
var B : [ 0..n-1 ] real ;
var C : [ 0..n-1 ] real ;

var randomStream = new RandomStream( SeedGenerator.currentTime ) ;
randomStream.fillRandom( A ) ;
randomStream.fillRandom( B ) ;

timer.clear() ;
timer.start() ;
for i in 0..n-1 {
	C[ i ] = A[ i ] + B[ i ] ;
}
timer.stop() ;
var serialSeconds = timer.elapsed() ;
writeln( "SERIAL product: " , serialSeconds , " seconds." ) ;

timer.clear() ;
timer.start() ;
forall i in 0..n-1 {
	C[ i ] = A[ i ] + B[ i ] ;
}
timer.stop() ;
var forallSeconds = timer.elapsed() ;
writeln( "FORALL product: " , forallSeconds , " seconds." ) ;

timer.clear() ;
timer.start() ;
C = A + B ;
timer.stop() ;
var parallelSeconds = timer.elapsed() ;
writeln( "PARALLEL product: " , parallelSeconds , " seconds." ) ;
