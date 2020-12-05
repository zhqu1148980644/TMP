#!/bin/bash
show_help() {
    echo "Usage: $(basename $0) create/remove NUM_NODES INIT_PORT SUBNETS GATEWAY"
    echo "Example: $(basename $0) create 20 2345 192.168.3.0/24 192.168.3.254"
    exit
}


if [ $# -ne 5 ]; then
    show_help
    exit
fi

command=$1
num=$2
port=$3
subnet=$4
gateway=$5
network_name=$4_$4_$2

declare -a nodes
declare -a containers

if [ "$command" == "create" ]; then

    echo -n "Created network ${network_name} "
    docker network create -d bridge --subnet=$subnet  --gateway=$gateway --attachable $network_name
    echo ""
    for i in `seq 1 $num`
    do
        nodes[i]="${network_name}_node_${i}"
        echo "Created node-${i}-${port}"
        containers[i]=$(docker run -d -p $port:22 --name "node-${i}-${port}" --network $network_name ilemonrain/centos-sshd)
        port=$((port+1))
    done
else
    for i in `seq 1 $num`
    do
        echo -n "Stop and deleted "
        docker container stop  "node-${i}-${port}"
        x=$(docker container rm  "node-${i}-${port}")
        echo ""
        port=$((port+1))
    done
    echo -n "Delete network "
    docker network rm $network_name
fi