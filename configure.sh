#!/bin/bash
EXIT=0
CheckIfExist(){
    if [ -d $Monitor ] 
    then
	echo "directory"
    else
	echo "not"
    fi
}
while [ $EXIT -ne 1 ]
do
    echo "Please, inform a directory/file to monitor"
    read Monitor
    CheckIfExist "$Monitor"
    echo "input from user: $Monitor"
    read EXIT
done