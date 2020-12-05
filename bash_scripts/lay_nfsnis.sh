# !/bin/bash

DEPENDENCY="openssh-clients vim rpcbind nfs-utils yp-tools ypserv ypbind"
NFS_CLIENT_ARGS="nosuid,nodev,rw,bg,soft,rsize=32768,wsize=32768"


declare -a append_records


log() {
    if [ $1 = 0 ]; then
        echo "$2 done!"
    else
        echo "$2 failed!"
    fi
    IFS=$'\n'
    if [ $# = 3 ]; then
        for line in $3
        do
            echo -e "\t"$3
        done
    fi
}

exit_safe() {
# restore original file and exit
    if [ $# != 0 ]; then
        for line in "$@"
        do
            echo -e "ERROR: $line"
        done
    fi
    for (( i=0;i<${#append_records[*]};i++ ))
    do
        record=${append_records[$i]}
        filename=${record%%:::*}
        line="${record##*:::}"
        if [ -z "$line" ]; then
            rm -f $filename 2>/dev/null
            continue
        fi
        lineno=$(fgrep -n "$line" $filename | cut -d ':' -f 1)
        if [ $lineno != "" ]; then
            tmpfile=$(mktemp tmp.XXXXXX)
            cat "$filename" | sed -e "${lineno}d" > $tmpfile 2>/dev/null
            cat $tmpfile > $filename
            rm -f $tmpfile 2>/dev/null
        fi
    done
    append_records=()
    exit 1
}

append_safe() {
# append one line to a file and record the changes.
    line=$1
    filename=$2
    if [ ! -f $filename ]; then
        append_records[${#append_records[@]}]="$filename:::"
    else
        append_records[${#append_records[@]}]="$filename:::$line"
    fi
    if ! `fgrep -q "$line" $filename`; then
        echo $line >> $filename
    fi
}


add_hosts() {
# alter /etc/hosts /etc/hostname
    cur_name=$1
    hosts=$2
    IFS=$'\n'
    for line in `cat $hosts`
    do
        append_safe "$line" /etc/hosts
    done
    cat "" > /etc/hostname 2>/dev/null    
    append_safe $cur_name /etc/hostname 
    hostname $cur_name
    append_safe "hostname $cur_name" /etc/rc.d/rc.local
}

check_dep() {
# check and install required packages.
    IFS=' '
    for soft in "$@"
    do
        if ! `rpm -qa | fgrep -q "$soft"` ; then
            yum install -y $soft 1>/dev/null
	    if [ $? != 0 ]; then
                echo 'Installing '$soft' failed.'
            else
                echo 'Installing '$soft' success.'
            fi
        fi
    done
}

show_help() {
    echo "Usage: lay_nfsnis server hosts_file server_dir"
    echo "       lay_nfsnis client hosts_file server_dir local_dir"
    echo "hosts_file format: "
    echo "192.167.0.3 hostname1"
    echo "192.167.0.5 hostname2"
    echo "192.167.0.58 hostname3"
    echo "The first line represent the NFS/NIS server."
    echo "This node's ip address must correspond to a certain line in hosts_file"
    exit
}

check_status() {
    for service in "$@"
    do
        if ! `systemctl status $service|fgrep -q "Active: active"`; then
            echo "Service: $service not active."
            return 1
        fi
    done
}

####################################server#####################################
start_nfs_server() {
    hosts=$1
    server_dir=$2
    lines=()
    while IFS=' ' read -r addr name
    do
        lines=(${lines[*]} "$name(rw,no_root_squash)")
    done < "$hosts"
    append_safe "$server_dir ${lines[*]}" /etc/exports
    systemctl restart rpcbind
    systemctl restart nfs
    systemctl restart nfslock
    exportfs -arv 1>/dev/null
    if [ $? != 0 ]; then
        exit_safe "Error when mounting shared folder: $server_dir"
    fi
    append_safe "systemctl restart rpcbind" /etc/rc.d/rc.local
    append_safe "systemctl restart nfs" /etc/rc.d/rc.local
    append_safe "systemctl restart nfslock" /etc/rc.d/rc.local
    append_safe "exportfs -arv" /etc/rc.d/rc.local
}

start_nis_server() {
    hosts=$1
    server_name=$2
    append_safe "NISDOMAIN=$server_name" /etc/sysconfig/network
    append_safe "YPSERV_ARGS='-p 1011'" /etc/sysconfig/network
    nisdomainname $server_name
    append_safe "nisdomainname $server_name" /etc/rc.d/rc.local
    append_safe "YPPASSWDD_ARGS='--port 1012'" /etc/sysconfig/yppasswdd
    while IFS=' ' read addr name
    do
        if [ $name = $server_name ]; then continue; fi
        append_safe "$addr:*:*:none" /etc/ypserv.conf
    done < "$hosts"
    systemctl restart ypserv
    systemctl restart yppasswdd
    make -C /var/yp 1>/dev/null
    append_safe "systemctl restart ypserv" /etc/rc.d/rc.local
    append_safe "systemctl restart yppasswdd" /etc/rc.d/rc.local
    append_safe "make -C /var/yp" /etc/rc.d/rc.local
}


####################################client#####################################
start_nfs_client() {
    # start nfs client service and mount shared folder.
    cur_name=$1
    server_name=$2
    args=$3
    server_dir=$4
    local_dir=$5
    umount $local_dir 2>/dev/null
    systemctl restart rpcbind
    systemctl restart nfslock
    mount_info=`showmount -e $server_name`
    if [ $? != 0 ]; then
        exit_safe "NFS service not opened in server: $server_name."
    fi
    if ! `echo $mount_info | fgrep -q "$cur_name"`; then
        exit_safe "Access for NFS in server is not available for this client."
    fi
    mount -t nfs -o $args $server_name:$server_dir $local_dir 2>/dev/null
    append_safe 'systemctl restart rpcbind' /etc/rc.d/rc.local
    append_safe 'systemctl restart nfslock' /etc/rc.d/rc.local
    append_safe "mount -t nfs -o $args $server_name:$server_dir $local_dir" /etc/rc.d/rc.local
    if ! `df -h | fgrep -q "$server_name:$server_dir"`; then
        exit_safe "Mount $server_nam:$server_dir at $local_dir failed."
    fi
}

start_nis_client() {
# start nis client service.
    server_name=$1
    PASSWD='passwd:     files nis sss'
    SHADOW='shadow:    files nis sss'
    GROUP='group:     files nis sss'
    HOSTS='hosts:      nis files dns myhostname'
    # /etc/sysconfig/network
    append_safe "NISDOMAIN=$server_name" /etc/sysconfig/network
    append_safe "YPSERV_ARGS='-p 1011'" /etc/sysconfig/network
    nisdomainname $server_name
    # /etc/yp.conf
    append_safe "domain $server_name server $server_name" /etc/yp.conf
    append_safe "ypserver $server_name" /etc/yp.conf
    # /etc/sysconfig/authconfig
    append_safe "USENIS=yes" /etc/sysconfig/authconfig
    # /etc/pam.d/system-auth
    append_safe "password   sufficient    pam_unix.so md5shadow nis 
          nullok try_first_passuse_authtok" /etc/pam.d/system-auth
    # /etc/nsswitch.conf
    sed -i "s/^passwd.*$/$PASSWD/" /etc/nsswitch.conf;
    sed -i "s/^shadow.*$/$SHADOW/" /etc/nsswitch.conf;
    sed -i "s/^group.*$/$GROUP/" /etc/nsswitch.conf;
    sed -i "s/^hosts.*$/$HOSTS/" /etc/nsswitch.conf;
    
    systemctl restart ypbind
    append_safe 'systemctl restart ypbind' /etc/rc.d/rc.local
}

check_path() {
    for dir in "$@"
    do
        if [[ $dir != /* ]]; then
            exit_safe "Path should be absolute path:" $dir
        fi
    done
}

###################################################################################



lay_client() {
    hosts=$1
    server_dir=$2
    local_dir=$3
    if [ ! -d $local_dir ]; then
        if [ -f $local_dir ]; then
            exit_safe "Directory to mount:$local_dir is a file."
        fi
        mkdir $local_dir 2>/dev/null
    fi
    server_ip=`cat $hosts| head -n 1 | cut -d " " -f 1`
    server_name=`cat $hosts| head -n 1 | cut -d " " -f 2`
    cur_ip=`hostname -I`
    cur_name=`cat $hosts | grep $cur_ip | cut -d ' ' -f 2`
    
    if [ -z $cur_name ]; then
        exit_safe "Can't find IP address in host_list which is equal to that of this node." 
    fi
    if [ "$cur_ip" = "$server_ip" ]; then
        exit_safe "Can't start a client in server. Try to deploy the client in another node." 
    fi
    
    check_dep $DEPENDENCY
    log $? "Check dependency"
    add_hosts $cur_name $1
    log $? "Add hosts"
    systemctl stop NetworkManager 2>/dev/null
    start_nfs_client $cur_name $server_name $NFS_CLIENT_ARGS $server_dir $local_dir
    log $? "Start NFS client"
    start_nis_client $server_name
    log $? "Start NIS client"
    check_status rpcbind ypbind
    # check status of each service.
    if [ $? != 0 ] ; then
        echo "Process failed. restroring changed files." 
        if `df -h | fgrep -q "$server_name:$local_dir"`; then
            umount $local_dir
        fi
        echo "Restoring done. exit." 
        exit_safe
    else
        echo "Process success!" 
    fi
}


lay_server() {
    hosts=$1
    server_dir=$2
    server_ip=`cat $hosts| head -n 1 | cut -d " " -f 1`
    server_name=`cat $hosts| head -n 1 | cut -d " " -f 2`
    if [ $server_ip != `hostname -I` ]; then
        exit_safe "First node's ip should be equal to this node's(server) IP."
    fi
    
    if [ ! -d $server_dir ]; then
        code=`mkdir $server_dir`
        if [ $? !=0 ]; then exit_safe "Can't find/create sharing folder: $server_dir"; fi
    fi

    check_dep $DEPENDENCY
    log $? "Check dependency"
    add_hosts $server_name $hosts
    log $? "Add hosts"
    systemctl stop NetworkManager 2>/dev/null
    start_nfs_server $hosts $server_dir
    log $? "Start nfs service"
    start_nis_server $hosts $server_name
    log $? "Start nis service"
    check_status rpcbind nfs nfslock ypserv yppasswdd
    # check status of each service.
    if [ $? != 0 ] ; then
        echo "Process failed. restroring changed files." 
        echo "Restoring done. exit." 
        exit_safe
    else
        echo "Process success!" 
    fi

}


chmod +x /etc/rc.d/rc.local
systemctl enable rc-local.service

if [ $# -eq 3 ] && [ $1 = server ] ; then
    check_path $3
    lay_server $2 $3
elif [ $# -eq 4 ] && [ $1 = client ] ; then
    check_path $3 $4
    lay_client $2 $3 $4
else
    show_help
fi
