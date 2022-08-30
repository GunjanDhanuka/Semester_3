#Taking inputs as arguments and creating the required variables
alphabets=(`cat $1`)
count=$2 
length=$3
alpha_count="${#alphabets[@]}"
curr_len=0
prev_alpha=a
loop_count=0

#Starting the Process
while [ "$curr_len" -lt "$length" ]
do

loop_count=$(($loop_count + 1))

#Generating random numbers and alphabets from the given input file
a=$(( $RANDOM%$alpha_count))
rand_alpha=${alphabets[$a]}
rand_numb=$(( $RANDOM%$count ))


if [ "$((curr_len + $rand_numb))" -le "$length" ]
then

#Making individual substrings
for (( i=0; i<$rand_numb; i++))
do
W[$loop_count]="${W[$loop_count]}${rand_alpha}"
done

#Effectively concatenating substrings based on existing constraints
if [ "$rand_numb" != 0 ]
then

#Checking if substring of previous and current same alphabet does not exceed count
if [ "$rand_alpha" = "$prev_alpha" ]
then
max_sub_len=$(($max_sub_len + $rand_numb))
else
max_sub_len=$(($rand_numb))
fi

if [ "$max_sub_len" -lt "$count" ]
then
X="${X}${W[$loop_count]}"
curr_len=$(($curr_len + $rand_numb))
echo "$X"
else
max_sub_len=$(($max_sub_len - rand_numb))
fi

prev_alpha=$rand_alpha
fi

fi

done
