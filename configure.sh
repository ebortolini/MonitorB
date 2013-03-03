#!/bin/bash
EXIT="y"
CONF_FILE="MonitorB.cfg"
CheckIfDirExist(){
    if [ -d $1 ] 
    then
		retureturnedVal=1
    else
		retureturnedVal=0
    fi
	return $retureturnedVal
}

CheckIfFileExist(){
    if [ -f $1 ] 
    then
		retureturnedVal=1
    else
		retureturnedVal=0
    fi
	return $retureturnedVal
}

CreateConfigurationFile(){
	touch $CONF_FILE
}
CreateLogDir(){
	CheckIfDirExist "/var/MonitorB"
	if [ "$?" -eq  0 ]; then
		mkdir /var/MonitorB	
	else
		CheckIfFileExist "/var/MonitorB/logs"
		if [ "$?" -eq 1 ];then
			rm /var/MonitorB/logs
		fi
	fi
}

CheckIfFileExist "MonitorB.cfg"
if [ "$?" -eq 1 ]
	then
	read -p "File Exists. Would you like to substitute for a new file? (y/N) :" opt
	if [ $opt = "N" ]; then
		exit 1;
	else
		rm -f $CONF_FILE
		CreateConfigurationFile
	fi
else
	echo "Not Exists"
	CreateConfigurationFile
fi
CreateLogDir
while [ $EXIT = "y" ]
do
    echo "Please, inform a directory/file to monitor: "
    read Monitor
    CheckIfDirExist "$Monitor"
    if [ "$?" -eq 1 ]
	then
		#echo "Directory exists"
		echo $Monitor >> $CONF_FILE
	else
		echo "Directory not exists"
    fi
    #echo "input from user: $Monitor"
    echo "More dirs ?  (y/N) :"
    read EXIT
done

