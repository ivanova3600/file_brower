function archive {
	case $1 in
    	*.zip)	zip -jr $2 $3	;;
    	*.tar)	
    		if [ -f "$2.tar" ]
    		then
    			tar rf "$2.tar" --directory=`dirname $3` `basename $3`
    		else	
    			tar cf "$2.tar" --directory=`dirname $3` `basename $3`
    		fi;;
    	*)          echo -n "Unknown"	;;
    esac
}

if [[ "$#" -gt 1 ]]
then 
    arch_name=`echo $1 | sed 's/\..*//'`
    files=($@)
	
	echo $arch_name
	    
    for ((i = 1; i < "$#"; i++))
    do
    	archive $1 $arch_name ${files[$i]}
    done
else
	echo "Use ./archiver.sh archiver_name file1 file2 ..."
fi
