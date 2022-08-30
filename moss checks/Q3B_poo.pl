#!/bin/perl



use strict;
use warnings;

# Module used to compute minimum number out of a set
use List::Util qw(min);


# a subroutine which returns the distance between 2 input strings
sub distance {
    my ($str1, $str2) = @_;
    my @ar1 = split( //, $str1);
    my @ar2 = split( //, $str2);

    my @dist;
    $dist[$_][0] = $_ for (0 .. @ar1);
    $dist[0][$_] = $_ for (0 .. @ar2);

    for my $i (1 .. @ar1){
        for my $j (1 .. @ar2){
            my $cost = $ar1[$i - 1] eq $ar2[$j - 1] ? 0 : 1;
    	    $dist[$i][$j] = min(
                            $dist[$i - 1][$j] + 1,
                            $dist[$i][$j - 1] + 1,
                            $dist[$i - 1][$j - 1] + $cost );
        }
    }

    return $dist[@ar1][@ar2];
}

# Open dictionary file
open(my $in,  "<",  "dictionary.txt")  or die "Can't open dictionary.txt: $!";

# Initialize dictionary hash table
my %dict;

while (<$in>) {     
	chomp;
	# assigns each line in turn to $_ and add it to the Hash
	$dict{"$_"}= $_;
}

# Close the buffer when it's done
close $in or die "$in: $!";


print "Please enter your text: \n";

# Read Text from the keyboard
my $text=<STDIN>;
chomp $text;

# Transform the text to lower case
$text = lc $text;

# Split text scalar into an array delimited by a space or .
my @text=split(/[ ]+/,$text);
my @spellings;
print "Scanning... \n \n";

# Loop on each word
my $counter = 0; #counts the index of the words in the entered sentence
foreach (@text){

    # Check if word exists in the dictionary hash
    #if the word doesn't exist proceed with finding the closest words in the dictionary
	if (!(exists $dict{$_})){
        # Get and store the word and its length
        my $spell = $_;
		my $spell_len = length $spell;
        #print 
        print $spell . ":\n";
        print "0: no change\n";
        my @options = ();

        # Searching for similar words 
        my $count = 1; #keeps a count of the number of similar words found
        #a loop which matches each word of the dictionary with the input word for the minimum distance
        foreach(%dict){

            # Compute the difference in length
            my $this_len = length $_;
			my $diff = $spell_len - $this_len;

            # Compute the distances of close length words 
            if(abs($diff) <= 1){
                #first find words with edit distance as 1 or less
                if(distance($_, $spell) <= 1)
                { 
                    
                    print $count,": ", $_ ."\n";
                    #add the suggestion to the array containing all options
                    push(@options, $_);
                    $count++;
                    #if we have found 5 suggestions then ask the user for his choice and terminate
                    if($count==6)
                    {
                        print "Enter the index of the option you want to choose\n";
                        #read the choice of the user
                        my $opt = <STDIN>;
                        if($opt!=0)
                        {   my $ch = $opt-1;
                            #change the word in the original input
                            $text[$counter] = $options[$ch];
                        }
                        #exit the loop
                        last;
                    }
                }
            }

                        
        }
        #if there aren't enough suggestion with edit distance 1 look for words with edit distance 2
        if($count<6)
        {
           foreach(%dict){

            # Compute the difference in length
            my $this_len = length $_;
			my $diff = $spell_len - $this_len;

            # Compute the distances of close length words 
            if(abs($diff) <= 1){
                #first find words with edit distance as 2
                if(distance($_, $spell) == 2)
                { 
                    
                    print $count,": ", $_ ."\n";
                    #add the suggestion to the array containing all options
                    push(@options, $_);
                    $count++;
                    #if we have found 5 suggestions then ask the user for his choice and terminate
                    if($count==6)
                    {
                        print "Enter the index of the option you want to choose\n";
                        #read the choice of the user
                        my $opt = <STDIN>;
                        if($opt!=0)
                        {   my $ch = $opt-1;
                            #change the word in the original input
                            $text[$counter] = $options[$ch];
                        }
                        #exit the loop
                        last;
                    }
                }
            }

                        
          }
        }
        #if there aren't enough suggestion with edit distance 2 or less look for words with edit distance 3
        if($count<6)
        {
           foreach(%dict){

            # Compute the difference in length
            my $this_len = length $_;
			my $diff = $spell_len - $this_len;

            # Compute the distances of close length words 
            if(abs($diff) <= 1){
                #first find words with edit distance as 3
                if(distance($_, $spell) ==3)
                { 
                    
                    print $count,": ", $_ ."\n";
                    #add the suggestion to the array containing all options
                    push(@options, $_);
                    $count++;
                    #if we have found 5 suggestions then ask the user for his choice and terminate
                    if($count==6)
                    {
                        print "Enter the index of the option you want to choose\n";
                        #read the choice of the user
                        my $opt = <STDIN>;
                        if($opt!=0)
                        {   my $ch = $opt-1;
                            #change the word in the original input
                            $text[$counter] = $options[$ch];
                        }
                        #exit the loop
                        last;
                    }
                }
            }

                        
          }
        }
        #if there aren't enough suggestion with edit distance 3 or less look for words with edit distance 4

        if($count<6)
        {
           foreach(%dict){

            # Compute the difference in length
            my $this_len = length $_;
			my $diff = $spell_len - $this_len;

            # Compute the distances of close length words 
            if(abs($diff) <= 1){
                #first find words with edit distance as 4
                if(distance($_, $spell) == 4)
                { 
                    
                    print $count,": ", $_ ."\n";
                    #add the suggestion to the array containing all options
                    push(@options, $_);
                    $count++;
                    #if we have found 5 suggestions then ask the user for his choice and terminate
                    if($count==6)
                    {
                        print "Enter the index of the option you want to choose\n";
                        #read the choice of the user
                        my $opt = <STDIN>;
                        if($opt!=0)
                        {   my $ch = $opt-1;
                            #change the word in the original input
                            $text[$counter] = $options[$ch];
                        }
                        #exit the loop
                        last;
                    }
                }
            }

                        
          }
        }
        #if there aren't enough suggestion with edit distance 4 or less look for words with edit distance 5

        if($count<6)
        {
           foreach(%dict){

            # Compute the difference in length
            my $this_len = length $_;
			my $diff = $spell_len - $this_len;

            # Compute the distances of close length words 
            if(abs($diff) <= 1){
                #first find words with edit distance as 1 or less
                if(distance($_, $spell) == 5)
                { 
                    
                    print $count,": ", $_ ."\n";
                    #add the suggestion to the array containing all options
                    push(@options, $_);
                    $count++;
                    #if we have found 5 suggestions then ask the user for his choice and terminate
                    if($count==6)
                    {
                        print "Enter the index of the option you want to choose\n";
                        #read the choice of the user
                        my $opt = <STDIN>;
                        if($opt!=0)
                        {   my $ch = $opt-1;
                            #change the word in the original input
                            $text[$counter] = $options[$ch];
                        }
                        #exit the loop
                        last;
                    }
                }
            }

                        
          }
        }

        

        #enter newline
        print " \n";
	}
#increase the index of words
$counter++;
}

#print the final sentence 
print "The final sentence is:\n";
foreach my $t (@text)
{
    print "$t ";
}
print "\n\nDone. \n"