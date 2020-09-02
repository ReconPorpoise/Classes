#include <iostream>
#include "time.h"
using namespace std;

int main() 
{
	// assign myTime to 09:30:00 AM
	Time myTime( 9, 30, 0 );
	// will not print AM/PM
	myTime.Write();
	
	// prints AM PM because we created the function in time.cpp
	myTime.WriteAmPm();

	// reassigns time to 08:00:00 AM
	myTime.Set( 8, 0, 0 );
	myTime.WriteAmPm();
	// will print 'Breakfast' because we had 08:00:00 AM be breakfast time
	myTime.Mealtime();

	Time Schedules [ 10 ];
	for( int i = 0; i < 10; i++ ){
		Schedules[ i ].Set( 11, 0, 0 );
		Schedules[ i ].WriteAmPm();
	}
	// 11 deconstructors called... 1 for myTime, and 10 for Schedules -> one for each index

	return 0;
}
