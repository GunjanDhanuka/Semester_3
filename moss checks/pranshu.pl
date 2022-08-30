#!/usr/bin/perl

if(open(NEW, "wordlist.txt")) #|| die "File Not Found\n";
{
my $inputi;
my @arr=split(' ', $inputi);
foreach my $var (@arr)
{
	$var=join(':',$var) . "\n";
}

use Cwd 'abs_path';			#obtains current absolute path
my @path=split( $0 , abs_path($0));
push(@path, 'wordlist.txt');
my $dicpath=join( '', @path);		#stores dictionary path

@string = <NEW>;
%x = ();
@a = ();

$count=0;
while( $count < $#string ){
    chomp @string[$count]; #remove \n
    $first_character = substr(@string[$count],0,1); #first char
    if($count > 0){
	$prev_character = substr(@string[$count-1],0,1); #first char of previous element
	unless($prev_character eq $first_character){ #if not equal, add the values to hash
	    $x{$prev_character} = [ @a ];#and empty array;
	    @a = ();
	} 
    }
    	push(@a, @string[$count]);  #if equal, keep on pushing to array
    
    if($count == ($#string-1)){ #add z words
	$x{$first_character} = [ @a ];
    } 
    $count++;
  }



print "Enter a sentence:\n";
$input = <STDIN>;
chomp $input;
@chinput = split(/\s+/, $input); #split on 1 or more spaces



#-----Iterate through every input word and check with %hash if exist or not----

%y=();
@n=();

OUTERLOOP: foreach  $word (@chinput){
    $word = lc $word; #convert to lower case
    $first_character = substr($word,0,1);  #first letter (key)
    
INNERLOOP: foreach $y (@{$x{$first_character}}){
    $y =~ s/[^\w]//g;  #remove any non alphanumeric
    if($y eq $word){  #if equal:
        @n=(); #empty list
	next OUTERLOOP; #exit this iteration
    }else{
	$test = mindist($y,$word); #short distance should return 1.
	if($test==1){
	  push(@n, $y);  #add to list
	}
    }
}
   $y{$word} = [ @n ]; #add all words with differences to hash
   @n = (); #empty the list, and iterate
}

my $inputi;
my @arr=split(' ', $inputi);
foreach my $var (@arr)
{
	$var=join(':',$var) . "\n";
}

use Cwd 'abs_path';			#obtains current absolute path
my @path=split( $0 , abs_path($0));
push(@path, 'wordlist.txt');
my $dicpath=join( '', @path);		#stores dictionary path


#when done, print results.
@counter=%y;				#counting elements in y
$counternow=@counter;
if(%y){

 print "Suggestions for misspelled words are:\n\n";
 foreach (keys %y){
     print "$_: \n";
     print "Suggestions : \n";
     $suggestionsize=@{$y{$_}};
     if($suggestionsize==0)
     {
      $suggestion==1
     }
     foreach $k (@{$y{$_}}){ 
	print "$k\n";
     }
     print "\n";
 }
}else{
    print "No misspelled words\n";
} 
close NEW;


use List::Util 'min';
 
my %cache;
 
sub mindist {				#getting the minimum edit distance
        my ($s, $t) = @_;
        return length($t) if !$s;	
        return length($s) if !$t;
 
	$cache{$s}{$t} //= 		#storing the intermediate data
        do {
                my ($s1, $t1) = (substr($s, 1), substr($t, 1));
 
                (substr($s, 0, 1) eq substr($t, 0, 1))	#recursively calling this function again
                        ? mindist($s1, $t1)		#recursively calling this function again
                        : 1 + min(mindist($s1, $t1),	#recursively calling this function again
                                  mindist($s,  $t1),	#recursively calling this function again
                                  mindist($s1, $t ));	#recursively calling this function again
        };
}

}
else
{
        print "Wordlist file not found" . "\n" ;	#error if wordlist file doesnt open
}
