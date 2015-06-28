use Time ;
use Random ;

/* ======== START CONFIG VARIABLES ======== */
config const n = 100000000 ;
/* ======== END CONFIG VARIABLES ======== */

var timer : Timer ;

var A : [ 0..n-1 , 0..n-1 ] real ;
var B : [ 0..n-1 , 0..n-1 ] real ;
var C : [ 0..n-1 , 0..n-1 ] real ;

var randomStream = new RandomStream( SeedGenerator.currentTime ) ;
randomStream.fillRandom( A ) ;
randomStream.fillRandom( B ) ;

timer.clear() ;
timer.start() ;
C = A + B ;
timer.stop() ;
var timeT = timer.elapsed() ;
writeln( "TIME: " , timeT , " seconds." ) ;
