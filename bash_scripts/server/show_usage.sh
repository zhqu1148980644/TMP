# !/bin/bash

show_help() {
    echo "Usage: $(basename $0) '/data /tmp /log' "
    echo "Path should be absolute path."
    exit
}

DATE=$(date '+%y-%m-%d')
declare -A usage_dict
usage_dict[total]=0
dirs=$1

# Check if path exits
if [ $# -ne 1 ]; then show_help ;fi
for dir in $dirs
do
    if [ ! -d $dir ]; then
        echo "Error $dir not exit."
        show_help
    fi
done

# Use du to count usage, Use dict to store usage for each user
for dir in $dirs
do
    IFS=$'\n'
    for line in `du -sc ${dir}/* 2>/dev/null`
    do
        size=$(echo $line | cut -f 1)
        path=$(echo $line | cut -f 2)
        if [ ${#path} -gt 30 ]; then continue; fi
        if [ $path = total ]; then
            user=total
	    path=$dir   
        else
            user=`stat -c "%U:%G" $path `
        fi

        if [ -z ${usage_dict[$user]} ]; then
            usage_dict[$user]=$size:::$path
        else
            oldvalue=${usage_dict[$user]}
	    oldsize=${oldvalue%%:::*}
	    oldpath=${oldvalue##*:::}
	    #echo $oldvalue $oldsize $oldpath $size $path
            usage_dict[$user]=$[$oldsize + $size]:::$oldpath:$path
        fi
    done
done

# Convet kb to GB and display the usage info
tmp_file=$(mktemp usage.XXXX)
IFS=' '
for key in $(echo ${!usage_dict[*]})
do
    uname=$(echo $key | cut -d ":" -f 1)
    gname=$(echo $key | cut -d ":" -f 1)
    value=${usage_dict[$key]}
    size=${value%%:::*}
    path=${value##*:::}
    size=$(awk "BEGIN{printf \"%.3f\" ,$size/1048576 }")
    echo -e "${uname}\t${gname}\t${size}GB\t${path}" >> $tmp_file
done

echo "$DATE Usage summary for $dirs:"
sort -t "	" -k3.1rn $tmp_file
rm -f $tmp_file 2>/dev/null


