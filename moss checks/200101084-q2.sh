#!/bin/bash

#assign the option chosen by user to options variable
options=$1;
#assign the address of the tar file to destination variable
destadd=$2
#create an array containing all arguments of user input
myargs=("$@")
#following are the various keys used as delimiters in the archive file

#key marking the start of a filename
akey="sdcsdc{}{}|}|*&#BGH545fvdfd@#";
#key marking the start of content
bkey="#%^%^&^tgj,,jkhjytb//[][]/]145free51445";
#key marking the end of content
ckey="wvle^%%#@*&:|<}<5454545094461371###";
#key marking the start of details for tvf
dkey="REGFERGeg,eorrergmre*&&*!#@((:L>?L>L?21515";
#key marking the end of details for tvf
ekey="df5151dsfw4564ds1326sd3}?:>:/'']'']']1312243@@@@@@@@!76";


#cvf implementation
if [ "$options" == "cvf" -o "$options" == "-cvf" ]; then 
        #create a new file for archiving       
        touch $destadd;
        rm -r $destadd;
        touch $destadd;
        ind=2;
        j=$#;
        j=$((j-1));
        
        echo $dkey>>$destadd;
        #enter the details which will be printed if the user uses tvf commands afterwards
        while [ $ind -le $j ]
        do
            if test -f "${myargs[$ind]}"; then
                ls -l ${myargs[$ind]}>>$destadd;
                
                ind=$((ind+1));
            else 
                ind=$((ind+1));
            fi
        done
        echo $ekey>>$destadd;
        ind=2;
        j=$#;
        j=$((j-1));
        # echo $j;
        #enter the details and contents of the files in the archive file
        while [ $ind -le $j ]
        do  
            if test -f "${myargs[$ind]}"; then
                echo ${myargs[$ind]};
                #key marking the start of a filename
                echo $akey>>$destadd;
                
                #entering the address of the file in the archive
                echo ${myargs[$ind]}>>$destadd;
                
                #key marking the start of content
                echo $bkey>>$destadd;  
                
                #appending the contents of the file to the archive
                cat ${myargs[$ind]}>>$destadd;
                        
                echo >>$destadd;
                
                #key marking the end of content
                echo $ckey>>$destadd;
            
                ind=$((ind+1));
            else 
                echo "the file ${myargs[$ind]} doesnt exist";
                ind=$((ind+1));
            fi
            
        done

#cvf implementation
elif [ "$options" == "cf" -o "$options" == "-cf" ]; then 
        #create a new file for archiving       
        touch $destadd;
        rm -r $destadd;
        touch $destadd;
        ind=2;
        j=$#;
        j=$((j-1));
        
        echo $dkey>>$destadd;
        #enter the details which will be printed if the user uses tvf commands afterwards
        while [ $ind -le $j ]
        do
            if test -f "${myargs[$ind]}"; then
                ls -l ${myargs[$ind]}>>$destadd;
                
                ind=$((ind+1));
            else 
                ind=$((ind+1));
            fi
        done
        echo $ekey>>$destadd;
        ind=2;
        j=$#;
        j=$((j-1));
        # echo $j;
        #enter the details and contents of the files in the archive file
        while [ $ind -le $j ]
        do  
            if test -f "${myargs[$ind]}"; then
                
                #key marking the start of a filename
                echo $akey>>$destadd;
                
                #entering the address of the file in the archive
                echo ${myargs[$ind]}>>$destadd;
                
                #key marking the start of content
                echo $bkey>>$destadd;  
                
                #appending the contents of the file to the archive
                cat ${myargs[$ind]}>>$destadd;
                        
                echo >>$destadd;
                
                #key marking the end of content
                echo $ckey>>$destadd;
            
                ind=$((ind+1));
            else 
                echo "the file ${myargs[$ind]} doesnt exist";
                ind=$((ind+1));
            fi
            
        done
#xvf implementation
elif [ "$options" == "xvf" -o "$options" == "-xvf" ]; then
        if test -f "$destadd"; then
                flag=0;
            src="";
            input=$destadd;
            counter2=0
            while IFS= read -r line
            
                do
                    #if flag is 1 create a new file on the given address
                    if [ $flag -eq 1 ]; then
                    touch $line;
                    rm -r $line;
                    touch $line;
                    src=$line
                    echo $src;
                    flag=0;
                    # echo $flag;
                    
                    #if flag is 2 enter the contents into the file
                    elif [ $flag -eq 2 ]; then
                    #check for the key that shows the end of the content
                    if [ "$line" == "$ckey" ]; then
                        # echo "ckey found";
                        flag=0;
                        # echo $flag;
                    else
                        echo $line>>$src;
                    fi
                    # x=$line;
                    #if flag equals 3 do nothing(this is for tvf implementation)
                    elif [ $flag -eq 3 ]; then
                    #check for the key that shows the end of the tvf details
                    if [ "$line" == "$ekey" ]; then
                        # echo "ckey found";
                        flag=0;
                        # echo $flag;
                    else
                        counter3=0;
                    fi
                    
                    #if the key signifying the start of filename is found set flag = 1
                    elif [ "$line" == "$akey" ]; then
                    # echo "akey found";
                    flag=1;
                    # echo $flag;
                    
                    #if the key signifying the end of filename is found set flag = 2
                    elif [ "$line" == "$bkey" ]; then
                    # echo "bkey found";
                    flag=2;
                    # echo $flag;
                    
                    #if the key signifying the start of tvf details is found set flag = 3
                    elif [ "$line" == "$dkey" ]; then
                    # echo "bkey found";
                    flag=3;
                    # echo $flag;
                    fi
                done < "$input"
            else   
                echo "The archive file $destadd doesn't exist";
            fi

            
#tvf implementation
elif [ "$options" == "tvf" -o "$options" == "-tvf" ]; then
        if test -f "$destadd"; then
            flag=0;
            src="";
            input=$destadd;
            while IFS= read -r line
            do
                #if flag = 1 do nothing(it is for xvf implementation)
                if [ $flag -eq 1 ]; then
                
                src=$line
                
                flag=0;
                # echo $flag;
                
                #if flag = 2 do nothing(it is for xvf implementation)
                elif [ $flag -eq 2 ]; then
                if [ "$line" == "$ckey" ]; then
                    # echo "ckey found";
                    flag=0;
                    # echo $flag;
                else
                    counter=0;
                fi
                # x=$line;
                #if flag = 3 print the lines on the terminal
                elif [ $flag -eq 3 ]; then
                    if [ "$line" == "$ekey" ]; then
                        # echo "ckey found";
                        flag=0;
                        # echo $flag;
                    else
                        echo $line;
                    fi
                
                #if the key signifying the start of filename is found set flag = 1
                elif [ "$line" == "$akey" ]; then
                # echo "akey found";
                flag=1;
                # echo $flag;
                
                #if the key signifying the end of filename is found set flag = 2
                elif [ "$line" == "$bkey" ]; then
                # echo "bkey found";
                flag=2;

                #if the key signifying the start of tvf details is found set flag = 3
                elif [ "$line" == "$dkey" ]; then
                    # echo "bkey found";
                    flag=3;
                # echo $flag;
                fi
            done < "$input"
            else   
                echo "The archive file $destadd doesn't exist";
            fi
#tf implementation
elif [ "$options" == "tf" -o "$options" == "-tf" ]; then
        if test -f "$destadd"; then
            flag=0;
            src="";
            input=$destadd;
            while IFS= read -r line
            do
                #if flag = 1 print out the name of the file
                if [ $flag -eq 1 ]; then
                
                src=$line
                echo $src;
                flag=0;
                # echo $flag;
                
                #if flag = 2 do nothing(it is for xvf implementation)
                elif [ $flag -eq 2 ]; then
                if [ "$line" == "$ckey" ]; then
                    # echo "ckey found";
                    flag=0;
                    # echo $flag;
                else
                    counter=0;
                fi
                # x=$line;
                #if flag = 3 do nothing it is for tvf implemenation
                elif [ $flag -eq 3 ]; then
                    if [ "$line" == "$ekey" ]; then
                        # echo "ckey found";
                        flag=0;
                        # echo $flag;
                    else
                        counter4=0;
                    fi
                
                #if the key signifying the start of filename is found set flag = 1
                elif [ "$line" == "$akey" ]; then
                # echo "akey found";
                flag=1;
                # echo $flag;
                
                #if the key signifying the end of filename is found set flag = 2
                elif [ "$line" == "$bkey" ]; then
                # echo "bkey found";
                flag=2;

                #if the key signifying the start of tvf details is found set flag = 3
                elif [ "$line" == "$dkey" ]; then
                    # echo "bkey found";
                    flag=3;
                # echo $flag;
                fi
            done < "$input"
            else   
                echo "The archive file $destadd doesn't exist";
            fi
#rf implementation
elif [ "$options" == "rf" -o "$options" == "-rf" ]; then 
        #create a new file for archiving       
        touch $destadd;
        ind=2;
        j=$#;
        j=$((j-1));
        
        echo $dkey>>$destadd;
        #enter the details which will be printed if the user uses tvf commands afterwards
        while [ $ind -le $j ]
        do
            if test -f "${myargs[$ind]}"; then
                ls -l ${myargs[$ind]}>>$destadd;
                
                ind=$((ind+1));
            else 
                ind=$((ind+1));
            fi
        done
        echo $ekey>>$destadd;
        ind=2;
        j=$#;
        j=$((j-1));
        # echo $j;
        #enter the details and contents of the files in the archive file
        while [ $ind -le $j ]
        do  
            if test -f "${myargs[$ind]}"; then
                #key marking the start of a filename
                echo $akey>>$destadd;
                
                #entering the address of the file in the archive
                echo ${myargs[$ind]}>>$destadd;
                
                #key marking the start of content
                echo $bkey>>$destadd;  
                
                #appending the contents of the file to the archive
                cat ${myargs[$ind]}>>$destadd;
                        
                echo >>$destadd;
                
                #key marking the end of content
                echo $ckey>>$destadd;
            
                ind=$((ind+1));
            else 
                echo "the file ${myargs[$ind]} doesnt exist";
                ind=$((ind+1));
            fi
            
        done

fi
#finish

