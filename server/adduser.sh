# !/bin/bash

NUM_RE="^[0-9]+$"
DEFAULT_HOME_PATH="/data"
FILE_NAME=$(basename $0)

show_help() {
    tmp_file=$(mktemp help_info.XXXXX)
    useradd --help >> $tmp_file
    IFS=$'\n'
    for line in $(cat $tmp_file | sed "s/useradd/$FILE_NAME/")
    do
        echo $line
    done
    rm -f $tmp_file 2> /dev/null
    exit
}

relay_arg() {
    if [ $# -eq 0 ]; then show_help; fi
    while [ -n "$1" ]; do
        case "$1" in
            --help|-h) show_help ;;
            -g) group=$2; shift  ;;
            *)                   ;;
        esac
        shift
    done
}

check_grp() {
    if [ -z "$group" ]; then return 0; fi
    if ! [[ "$group" =~ $NUM_RE ]]; then
        record=$(cat /etc/group | cut -d ":" -f 1 | grep -w $group)
        if [ -z "$record" ]; then
            groupadd $group
            newgrp=TRUE
        fi
    else
        record=$(cat /etc/group | cut -d ":" -f 3 | grep -w $group)
        if [ -z "$record" ]; then
            echo "GUID not exit, please choose \
            a group name of an existed GUID."
            exit
        fi
    fi
}

make -C /var/yp 1>/dev/null
echo -e "Updated user infos.\n"
relay_arg $*
check_grp
useradd -D -b $DEFAULT_HOME_PATH
if `echo "$*" | grep -q '\-m'`; then
    useradd $*
else
    useradd -m $*
fi

if [ $? != 0 ]; then
    if [ "$newgrp" = "TRUE" ]; then
        groupdel $group
    fi
    echo "Add user $user_name failure!"
else
    username=`cat /etc/passwd | tail -n 1 | cut -d ":" -f 1`
    make -C /var/yp 1>/dev/null
    echo "Add user $username success: $(cat /etc/passwd| tail -n 1)"
fi
