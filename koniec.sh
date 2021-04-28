#!/bin/bash
$(rm -f "procesy.txt")
$(ps -a >> procesy.txt)
cat procesy.txt | while read linia
do 
    #string=  echo $linia | cut -d' ' -f1-1
    #echo $(awk -F: '$1' $linia) 
    #echo  $string
    if [[ $linia =~ [^a-zA-Z0-9\] ]] ; then
        echo  $linia 
    fi

    $(kill -9 $(echo $linia | cut -d' ' -f1-1))
done

$(rm -f "procesy.txt")
$(rm -f Proces2.o)
$(rm -f client.o)