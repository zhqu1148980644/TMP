# !/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $(basename $0) hosts_file username"
    exit
fi

hosts=$1
username=$2
while IFS=' ' read -r addr name
do
    if [ $addr = `hostname -I` ]; then
        if [ ! -f ~/.ssh/id_rsa.pub ]; then
           cat /dev/zero | ssh-keygen -q -N "" 
        fi
        cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
        chmod 600 ~/.ssh/authorized_keys
    else
        cat ~/.ssh/id_rsa.pub | ssh $username@$addr \
        "cat > ~/tmp_file; if [ ! -d  !/.ssh ]; then cat /dev/zero | ssh-keygen -q -N ''; fi;\
         cat tmp_file >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys;\
         rm -f ~/tmp_file 2>/dev/null"
        scp -p $(basename $0) $username@${addr}:~/
        scp -p $1 $username@${addr}:~/
    fi
done < "$hosts"

