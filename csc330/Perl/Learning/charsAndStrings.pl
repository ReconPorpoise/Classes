#!/usr/bin/perl
use warnings;

$x = 'a';
$string = "Hello World!";

print($x . "\n");
print($string . "\n");
print("The letter at index 1 of '" . $string . "' is " . substr($string, 1, 1) . ".\n");

