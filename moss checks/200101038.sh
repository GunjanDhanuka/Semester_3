#! /bin/bash
# Shell script to replicate the behaviour of the `tar` command.
args=("$@");
flags="${args[0]}";
#echo "flags: $flags";
destination="${args[1]}";
#echo "destination: $destination";

argcount=$#;
#echo "argcount: $argcount";
input_i=2;

if [[ "$flags" = "cvf" ]] || [[ "$flags" = "-cvf" ]]; then
    #echo "COMPRESSION MODE ON!";
    if [ -e "$destination" ]; then
        rm $destination;
    fi
    touch $destination;
    echo "<<MDOPEN>>" >> $destination;
    while [ $input_i -lt $argcount ]
    do
        input_file="${args[$input_i]}";
        if [ -e $input_file ]
        then
            ls -l $input_file >> $destination;
        fi
        input_i=$((input_i+1));
    done
    echo "<<MDCLOSE>>" >> $destination;

    input_i=2;
    while [ $input_i -lt $argcount ]
    do
        input_file="${args[$input_i]}";
      
        if [ -e $input_file ]
        then
            echo "$input_file";
            echo -e "<<NFA>>$input_file<<AE>>" >> $destination;
            cat $input_file >> $destination;
            echo -e "\n<<FE>>" >> $destination;
            
        else
            echo "File $input_file does not exist";
        fi
        input_i=$((input_i+1));
    done

elif [[ "$flags" = "xvf" ]] || [[ "$flags" = "-xvf" ]]; then
    #echo "EXTRACTION MODE ON!";
    while IFS= read -r line; do
        #echo "Text read from file: $line";
        if [[ "$line" = "<<NFA>>"* ]]; then
            #echo "NFA found";
            file_name="${line#*<<NFA>>}";
            file_name="${file_name%<<AE>>}";
            echo "$file_name";
            touch $file_name;
            #echo "File created: $file_name";
        elif [[ "$line" = "<<FE>>" ]]; then
            #echo "FE found";
            #echo "File $file_name closed";
            file_name="";
        else
            if [ -n "$file_name" ]; then
                #echo "Writing to file: $file_name";
                echo "$line" >> $file_name;
            fi
        fi
    done < $destination

elif [[ "$flags" = "tvf" ]] || [[ "$flags" = "-tvf" ]]; then
    #echo "DISPLAY FILES LIST VERBOSE!";
    flag=0;
    while IFS= read -r line; do
        #echo "Text read from file: $line";
        if [[ "$line" = "<<MDOPEN>>" ]]; then
            #echo "MDOPEN found";
            flag=1;
        elif [[ "$line" = "<<MDCLOSE>>" ]]; then
            #echo "MDCLOSE found";
            flag=0;
        else
            if [ $flag -eq 1 ]; then
                echo "$line";
            fi
        fi
    done < $destination;

elif [[ "$flags" = "tf" ]] || [[ "$flags" = "-tf" ]]; then
    #echo "DISPLAY MODE NORMAL!";
    while IFS= read -r line; do
        #echo "Text read from file: $line";
        if [[ "$line" = "<<NFA>>"* ]]; then
            #echo "NFA found";
            file_name="${line#*<<NFA>>}";
            file_name="${file_name%<<AE>>}";
            echo "$file_name";
        fi
    done < $destination

elif [[ "$flags" = "rf" ]] || [[ "$flags" = "-rf" ]]; then
    #echo "ADDING TO EXISITING ARCHIVE ON!";
    if [ -e $destination ]; then
        echo "<<MDOPEN>>" >> $destination;
        while [ $input_i -lt $argcount ]
        do
            input_file="${args[$input_i]}";
            if [ -e $input_file ]
            then
                ls -l $input_file >> $destination;
            fi
            input_i=$((input_i+1));
        done
        echo "<<MDCLOSE>>" >> $destination;

        input_i=2;
        while [ $input_i -lt $argcount ]
        do
            input_file="${args[$input_i]}";
            if [ -e $input_file ]
            then
                echo -e "<<NFA>>$input_file<<AE>>" >> $destination;
                cat $input_file >> $destination;
                echo -e "\n<<FE>>" >> $destination;
                
            else
                echo "File $input_file does not exist";
            fi
            input_i=$((input_i+1));
        done
    else
        echo "Archive file $destination does not exist";
    fi
else
    echo "Invalid flags";
fi



