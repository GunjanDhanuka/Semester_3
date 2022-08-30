alphas=(`cat $3`)
count=$1
length=$2
currentlength=0
previousalphabet=0
loopcounts=0

while [ $currentlength -lt $length ]
do
    flag=0
    loopcounts=$(($loopcounts + 1))

    randalphanum=$(( $RANDOM%((${#alphas[@]}))))
    randalpha=${alphas[$randalphanum]}
    randnum=$(( $RANDOM%$count ))
    if [ $randnum == 0 ]
    then
    randnum=$(($randnum+1))
    fi
    
    if [ $((currentlength + $randnum)) -le $length ]
    then
        if [ $randalphanum = $previousalphabet ]
        then
            maxsublen=$(($maxsublen + $randnum))
        else
            maxsublen=$(($randnum))
        fi
    if [ $maxsublen -lt $count ]
    then
        currentlength=$(($currentlength + $randnum))
        flag=1
    else
        maxsublen=$(($maxsublen - randnum))
        flag=0
    fi
    previousalphabet=$randalphanum
fi
if [ $flag == 1 ]
then
for (( i=0; i<$randnum; i++))
do
W[$loopcounts]=${W[$loopcounts]}${randalpha}
done
X=${X}${W[$loopcounts]}
echo $X
fi
done
