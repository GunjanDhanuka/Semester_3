#!/usr/bin/perl

open(MFILE, "dictionary.txt") ;

@lines = <MFILE>;
%hash = ();
@values = ();

for($i=0; $i < $#lines; $i++){
    chomp @lines[$i]; #remove \n
    $first_char = substr(@lines[$i],0,1); 
    if($i > 0){
	$step_back = substr(@lines[$i-1],0,1); #Take the starting letter of the first element
       	if(!($step_back eq $first_char)){ #Check if equal or unequal then add
	    $hash{$step_back} = [ @values ];
	    @values = ();
	} 
    }
    	push @values, @lines[$i];  
    
    if($i == ($#lines-1)){ #add z words
	$hash{$first_char} = [ @values ];
    } 
    
  }



print "Type a word or words:\n";
$sentence = <STDIN>;
chomp $sentence;
@splited = split(/\s+/, $sentence); 

%hash2=();
@list=();

BAHAR: foreach  $word (@splited){
    $word = lc $word; 
    $first_char = substr($word,0,1);  
    
INNERLOOP: foreach $y (@{$hash{$first_char}}){
   
    if($y eq $word){  
        @list=(); 
	next BAHAR; 
    }else{
	$test = leven($y,$word); 
	if($test==1){
	  push @list, $y;  
	}
    }
}
   $hash2{$word} = [ @list ]; 
   @list = (); 
}



if(%hash2){

 print "The incorrect words are:\n\n";
 foreach (keys %hash2){
     print "$_: \n\n";
     print "Suggestions are: \n";
     foreach $k (@{$hash2{$_}}){
	 print ">>>$k\n";
     }
     print "\n \n";
 }
}else{
    print "No misspelled words\n";
} 
close MFILE;


use List::Util 'min';
 
my %cache;
 
sub leven {
        my ($s, $t) = @_;
        return length($t) if !$s;
        return length($s) if !$t;
 
	$cache{$s}{$t} //= 
        do {
                my ($s1, $t1) = (substr($s, 1), substr($t, 1));
 
                (substr($s, 0, 1) eq substr($t, 0, 1))
                        ? leven($s1, $t1)
                        : 1 + min(leven($s1, $t1),
                                  leven($s,  $t1),
                                  leven($s1, $t ));
        };
}