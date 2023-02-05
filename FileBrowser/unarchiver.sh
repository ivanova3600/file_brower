#echo $1
if [ -f $1 ]
then
    echo $1

    file_dir=`dirname $1`
    file_dir+="/"
    file_dir+=`basename $1 | sed 's/\..*//'`

    a=1
    str=""

    new_dir=""

    while :
    do
        new_dir="$file_dir$str"
        if ! [ -d $new_dir ]
        then
            echo $new_dir
            mkdir $new_dir
            break
        fi
        str="($a)"
        ((a++)) 
    done

    echo $new_dir

	case $1 in
		*.tar)	tar -xvf $1 -C $new_dir		;;
		*.zip)		unzip -u $1 -d $new_dir     ;;
	#	*.tar.bz2)   tar -xvjf $1	;;
    #    *.tar.gz)    tar -xvzf $1   ;;
    #    *.tar.xz)    tar -xvJf $1   ;;
    #    *.lzma)      unlzma $1      ;;
    #    *.bz2)       bunzip2 $1     ;;
    #    *.rar)       unrar x -ad $1 ;;
   #     *.7z)        7z -x $1       ;;
        *)          echo -n "Unknown"; rmdir $new_dir ;;
	esac
else
    echo "Archive doesnt exist"
    echo $1
fi
