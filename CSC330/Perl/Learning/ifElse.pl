#!/usr/bin/perl
use warnings;

print( "Enter a number: " );
$x = <>;
chomp($x);

if( $x < -1000 || $x > 5000) {
	print( $x . " is really big.\n" );
}
elsif( $x > 20 ) {
	print( $x . " is greater than 20.\n" );
}
elsif( $x > 30 ) {
	print( $x . " is greater than 30.\n" );
}
elsif( $x > 40 ) {
	print( $x . " is greater than 40.\n" );
}
elsif( $x > 50 ) {
	print( $x . " is greater than 50.\n" );
}
else {
	print( $x . " is less than 10.\n" );
}
