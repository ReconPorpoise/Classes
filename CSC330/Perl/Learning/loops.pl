#!/usr/bin/perl
use warnings;

$i = 1;
while( $i <= 10 ) {
	print( "While: " . $i . "\n" );
	$i++;
}
print( "\n" );

$j = 1;
do {
	print( "Do-while: " . $j . "\n" );
	$j++;
} while( $j <= 10 );
print( "\n" );

$k = 1;
until( $k == 11 ) {
	print( "Until: " . $k . "\n" );
	$k++;
}
print( "\n" );

$l = 1;
do {
	print( "Do-until: " . $l . "\n" );
	$l++;
} until( $l == 11 );
print( "\n" );

@a = ( 1..10 );
for( @a ) {
	print("For: " . "$_", "\n" );
}

