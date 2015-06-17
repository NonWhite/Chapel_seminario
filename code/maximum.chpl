use Time ;
use Random ;

proc hybridFindMaxInRange( array , lower , upper , numThreads ) : real {
	if( lower == upper ){ return array[ lower ] ; }
	if( numThreads == 1 ){ return findMaxInRange( array , lower , upper ) ; }
	var middle = ( lower + upper ) / 2 ;
	var lowerThreads = numThreads / 2 ;
	var upperThreads = numThreads - lowerThreads ;
	var lowerMax , upperMax : real ;
	cobegin with( ref lowerMax , ref upperMax ){
		lowerMax = hybridFindMaxInRange( array , lower , middle , lowerThreads ) ;
		upperMax = hybridFindMaxInRange( array , middle + 1 , upper , upperThreads ) ;
	}
	return max( lowerMax , upperMax ) ;
}

proc fastFindMaxInRange( array , lower = 0 , upper = array.numElements-1 ) : real {
	if( lower == upper ){ return array[ lower ] ; }
	var middle = ( lower + upper ) / 2 ;
	var lowerMax , upperMax : real ;
	cobegin with( ref lowerMax , ref upperMax ){
		lowerMax = fastFindMaxInRange( array , lower , middle ) ;
		upperMax = fastFindMaxInRange( array , middle + 1 , upper ) ;
	}
	return max( lowerMax , upperMax ) ;
}

proc findMaxInRange( array , lower = 0 , upper = array.numElements-1 ) : real {
	var i = lower ;
	var arrayMax = array[ i ] ;
	while( i <= upper ){
		if( array[ i ] > arrayMax ){
			arrayMax = array[ i ] ;
		}
		i += 1 ;
	}
	return arrayMax ;
}

proc findMax( array ){
	var middle = array.numElements / 2 ;
	var lowerMax , upperMax : real ;
	cobegin with( ref lowerMax , ref upperMax ){
		lowerMax = findMaxInRange( array , 0 , middle ) ;
		upperMax = findMaxInRange( array , middle + 1 , array.numElements - 1 ) ;
	}
	return max( lowerMax , upperMax ) ;
}

proc serialFindMax( array ){
	return findMaxInRange( array ) ;
}

proc parallelFindMax( array ){
	return fastFindMaxInRange( array ) ;
}

proc hybridFindMax( array , numThreads ){
	return hybridFindMaxInRange( array , 0 , array.numElements-1 , numThreads ) ;
}

/* ======== START CONFIG VARIABLES ======== */
config const n = 5000 ;
config const threads = 8 ;
/* ======== END CONFIG VARIABLES ======== */

var timer : Timer ;
//timer.start() ;

var realArray: [ 0..n-1 ] real ;
var randomStream = new RandomStream( SeedGenerator.currentTime ) ;
randomStream.fillRandom( realArray ) ;

// Test for findMax
//writeln( "realArray: " , realArray ) ;
//writeln( "Max of realArray is: " , findMax( realArray ) ) ;
//timer.stop() ;
//writeln( "That took " , timer.elapsed() , " seconds." ) ;

timer.clear() ;
timer.start() ;
var serialMax = serialFindMax( realArray ) ;
timer.stop() ;
var serialSeconds = timer.elapsed() ;
writeln( "SERIAL test: " , serialMax , " in " , serialSeconds , " seconds." ) ;

timer.clear() ;
timer.start() ;
//var parallelMax = parallelFindMax( realArray ) ;
timer.stop() ;
var parallelSeconds = timer.elapsed() ;
//writeln( "PARALLEL test: " , parallelMax , " in " , parallelSeconds , " seconds." ) ;

timer.clear() ;
timer.start() ;
var hybridMax = hybridFindMax( realArray , threads ) ;
timer.stop() ;
var hybridSeconds = timer.elapsed() ;
writeln( "HYBRID test: " , hybridMax , " in " , hybridSeconds , " seconds." ) ;

timer.clear() ;
timer.start() ;
var reduceMax = max reduce realArray ;
timer.stop() ;
var reduceSeconds = timer.elapsed() ;
writeln( "REDUCE test: " , reduceMax , " in " , reduceSeconds , " seconds." ) ;

