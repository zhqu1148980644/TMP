#!/bin/bash
#fasta.gz >>> sorted_bam
#creating a list containg all fasta.gz file's directory
getdir(){
   for f in $1/*
   do
   if test -f $f
   then
       if `echo $f|grep -q '.*Clean.*gz'`
       then 
       arr=(${arr[*]} $f)
       fi
   else
       getdir $f
   fi
   done
}
getdir /store/apple_RNAseq/apple_data
#conversion
n=${#arr[*]}
echo $n
max_len=${#arr[*]}/2
for (( i=1; i<=max_len; i=i+1 ))
do
index1=`expr $i \* 2 - 1 - 1`
index2=`expr $i \* 2 - 1`
a=${arr[$index2]}
b=${a%_*}
c=${b##*/}
echo "start alinment and sort"
echo ${arr[$index1]}
echo ${arr[$index2]}
hisat2 -p 20 -t -x ~/gdindex/gdindex -1 ${arr[$index1]} -2 ${arr[$index2]} | samtools sort -@ 16 -o /store/apple_RNAseq/sorted_bam/${c}.bam 2>&1
done
echo "done"
echo "all fasta.gz files converted to sorted_bam file!"
#reads count
for i in /store/apple_RNAseq/sorted_bam/*.bam
do
a=${i%.*}
b=${a##*/}
echo $b
echo $i
htseq-count -s no $i -f bam ~/gd.gtf > /store/apple_RNAseq/count/${b}.count
done

