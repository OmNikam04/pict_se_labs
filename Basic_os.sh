#!/bin/bash

#Creating file to store the database
echo "File name:"
read fileName
touch $fileName

add() {
    echo "Enter number of records to insert: "
    read records

    for (( i=0 ; i < $records ; i++ ))
    do

    echo "Enter id:"
    read id

    echo "Enter name:"
    read name

    echo "Enter marks:"
    read marks

    echo -e "$id\t$name\t$marks" >> $fileName
    done
}

show () {
    cat $fileName
}


search () {
    read -p "Enter id to search: " to_search

    if grep -wi $to_search $fileName
    then
        echo "Found the record"
    else
        echo "Not found the record"
    fi
}


delete () {
    read -p "Enter id to delete: " to_search

    if grep -wi $to_search $fileName
    then
        # Logic to delete file
        # find the all all the lines that do not matches the pattern using -v flag of grep command
        # print all those lines into sepearate file temp
        echo "Record being deleted: "
        grep -wv $to_search $fileName >> temp
        # delete the original file
        rm $fileName
        # rename the temp as our old file name
        mv temp $fileName
    else
        echo "Record does not exist"
    fi
}


delete 
