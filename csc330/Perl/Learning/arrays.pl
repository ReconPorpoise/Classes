#!/usr/bin/perl
use warnings;

@ages = ( 25, 30, 40 );
@names = ( "John", "Ronald", "Bailey" );
# perl arrays can take any data type
@array = ( 1, 2, 'Hello' );

print( "\$ages[ 0 ] = $ages[ 0 ]\n" );
print( "\$ages[ 1 ] = $ages[ 1 ]\n" );
print( "\$ages[ 2 ] = $ages[ 2 ]\n\n" );

print( "\$names[ 0 ] = $names[ 0 ]\n" );
print( "\$names[ 1 ] = $names[ 1 ]\n" );
print( "\$names[ 2 ] = $names[ 2 ]\n\n" );

print( "\$array[ 0 ] = $array[ 0 ]\n" );
print( "\$array[ 1 ] = $array[ 1 ]\n" );
print( "\$array[ 2 ] = $array[ 2 ]\n\n" );

# this creates an array of strings separated by white space
@stringArray = qw/Hello World/;
print( "\$stringArray[ 0 ] = $stringArray[ 0 ]\n" );
print( "\$stringArray[ 1 ] = $stringArray[ 1 ]\n" );
