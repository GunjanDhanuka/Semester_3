#!/usr/bin/perl

use strict;
use warnings;

use List::Util qw(min);

my $dfile     = 'dictionary.txt';
my $edit_dist = 3;
my %dict;

sub create_dict {
    open( my $file, "<", $dfile )
      or die "Could not open dictionary file: '$dfile' $!";
    while (<$file>) {
        chomp;
        $dict{"$_"} = $_;
    }
    close $file or die "Could not close dictionary file: '$dfile' $!";
}

sub get_edit_distance {
    my ($word1, $word2) = @_;
    my $len1 = length($word1);
    my $len2 = length($word2);
    my @dp;
    for ( my $i = 0 ; $i <= $len1 ; $i++ ) {
        for ( my $j = 0 ; $j <= $len2 ; $j++ ) {
            if ( $i == 0 ) {
                $dp[$i][$j] = $j;
            }
            elsif ( $j == 0 ) {
                $dp[$i][$j] = $i;
            }
            elsif ( substr( $word1, $i - 1, 1 ) eq substr( $word2, $j - 1, 1 ) )
            {
                $dp[$i][$j] = $dp[ $i - 1 ][ $j - 1 ];
            }
            else {
                $dp[$i][$j] = 1 + min(
                    $dp[$i][ $j - 1 ],
                    $dp[ $i - 1 ][$j],
                    $dp[ $i - 1 ][ $j - 1 ]
                );
            }
        }
    }

    return $dp[$len1][$len2];
}

sub similar_words {
    my ($word) = @_;
    my @close_words = ();

    if (!(exists $dict{$word})) {
        my $wordlen = length($word);
        foreach my $key (keys %dict) {
            my $compare = $dict{$key};
            my $compare_len = length($compare);
            my $difference = $wordlen - $compare_len;
            if ( abs($difference) le 3 ) {
                my $edit = get_edit_distance($word, $compare);
                if ( $edit le 1 ) {
                    push( @close_words, $compare );
                }
            }

            my $size = @close_words;
            if ( $size eq 5 ) {
                return @close_words;
            }
        }
        foreach my $key (keys %dict) {
            my $compare = $dict{$key};
            my $compare_len = length($compare);
            my $difference = $wordlen - $compare_len;
            if ( abs($difference) le 3 ) {
                my $edit = get_edit_distance($word, $compare);
                if ( $edit > 1 && $edit <= 2 ) {
                    push( @close_words, $compare );
                }
            }

            my $size = @close_words;
            if ( $size eq 5 ) {
                return @close_words;
            }
        }
        foreach my $key (keys %dict) {
            my $compare = $dict{$key};
            my $compare_len = length($compare);
            my $difference = $wordlen - $compare_len;
            if ( abs($difference) le 1 ) {
                my $edit = get_edit_distance($word, $compare);
                if ( $edit > 2 && $edit <= 3 ) {
                    push( @close_words, $compare );
                }
            }

            my $size = @close_words;
            if ( $size eq 5 ) {
                return @close_words;
            }
        }
    }
    return @close_words;
}

print "Enter your text: \n";

my $input = <STDIN>;
chomp $input;
create_dict();
print "You will now receive suggestions for possible typos!\n";
print
"Press 0 if do not want changes to the word or else, press number corresponding to your choice\n";
print "--------------------------------------------------------------------\n";
my @words       = split (/\s+/, $input);
my $sentencelen = @words;
my @final       = ();


foreach my $word (@words) {

    my @suggestions   = similar_words($word);

    my $suggestionlen = @suggestions;

    if (exists $dict{$word}) {
        push(@final, $word);
        next;
    }
    else {
        print "$word : \n";
        my $menu = 1;
        print "0. Retain original.\n";
        foreach (@suggestions) {
            print "$menu : $_\n";
            $menu++;
        }
        print "Enter your choice: ";
        my $choice = <STDIN>;
        print "\n---------------------------\n";
        chomp $choice;
        if ( $choice == 0 ) {
            push( @final, $word );
        }
        else {
            push( @final, $suggestions[$choice-1] );
        }
    }
}

print "Final string after typo-correction:\n";
foreach (@final) {
    print "$_ ";
}

print "\n\nCompleted spell check!\n\n";
