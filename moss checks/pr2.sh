#! /bin/bash

##random number generator
RANDOM=$$;

###taking input from the command line arguments###
count=$1;
length=$2;
alphabet_set="";
read alphabet_set;
###X###


###defining various variables used further in the code###
maxindex=${#alphabet_set};
current_length=0;
current_string="";
current_index=1;
temp=-1;
random=$RANDOM;
alphabet_counter=1;
no_of_rep=0;
expected_length=0;
k=0;
###X###



###Validation checks for the given input### 


##checking if the given alphabet string has a length greater than one
if [ $maxindex -le 1 ]
then
	echo "ERROR: Please provide a string of atleast 2 characters!!";
	exit 1;
fi

##counting the no of distinct alphabet_set in the input string
while [ $current_index -lt $maxindex ]
do
   next=`expr $current_index + 1`;
   if [ "${alphabet_set:current_index:1}" != "${alphabet_set:next:1}" ]
   then 
       alphabet_counter=$(($alphabet_counter + 1));
      
       
       break;
    fi
    current_index=$(($current_index + 1));
done

##checking if the string has more than 1 distinct alphabet_set
if [ $alphabet_counter -eq 1 ]
then
	echo "ERROR: the alphabet string should have more than one alphabet!!";
	exit 1;
fi

##checking if the count is more than 1
if [ $count -le 1 ]
then
	echo "ERROR: Please provide a count of more than one !!"
	exit 1;
fi

##checking if the length of the count is proper or not
if [ $count -gt $(( $length + 1)) ]
then
	echo "ERROR: Please keep the count less than the length + 2 !!";
	exit 1;
fi

###if the input is fine we can proceed further

###X###


###loop for the creation of a randomised string till the length is less than the given length###
while [ $current_length -lt $length ]
do
    ##geneRATING a random no to select an alphabet from the input file 
    random=$RANDOM;
    index=`expr $random % $maxindex`;
    current_alpha=${alphabet_set:index:1};
    temp_alpha=${alphabet_set:temp:1}
    
    ##checking if the alphabet at the new index is same as the previous one
    if [ $current_alpha != $temp_alpha ]
    then
        ##updating the temporary index for the future comparisons
        temp=$index;

        ##generating a random number for finding the length of the new substring to be added
        random=$RANDOM;
        no_of_rep=`expr $random % $count`;
        if [ $no_of_rep == 0 ]
        then
            no_of_rep=`expr $no_of_rep + 1`;
        fi
            

        ##reducing the length of the new substring if length exceeds the given length
        expected_length=`expr $current_length + $no_of_rep`;
        if [ $expected_length -gt $length ]
        then
            k=1;	
            break;
        fi
        
        ##adding the new substring to the current substring
        i=0;
        while [ $i -lt $no_of_rep ]
        do
            current_string="$current_string${alphabet_set:index:1}";
            i=`expr $i + 1`;
            
        done
        
        ##updating the current length for future iterations of the loop
        current_length=`expr $current_length + $no_of_rep`;

        echo $current_string;
    fi
    
done

###dealing with the case when the no of repetitions makes the string longer than the given length 
if [ $k -eq 1 ]
then
    no_of_rep=`expr $length - $current_length`;
    i=0;
        while [ $i -lt $no_of_rep ]
        do
            current_string="$current_string${alphabet_set:index:1}";
            i=`expr $i + 1`;
        done
    echo $current_string;
fi

###XXXX###