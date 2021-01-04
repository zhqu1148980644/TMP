---
title: Transpose File
date: 2021-01-04
---
---
title: Transpose File
date: 2021-01-04
---
Given a text file file.txt, transpose its content.

You may assume that each row has the same number of columns and each field is separated by the ' ' character.

Example:

If file.txt has the following content:

name age
alice 21
ryan 30
Output the following:

name alice ryan
age 21 30

#### Solutions

1. ##### cut


```bash
# ncol=`head file.txt -n 1|grep -o ' '|wc -l`
# ncol=$(($ncol + 1))
ncol=`awk '{print NF}' file.txt| uniq`
# for i in `seq 1 $ncol`
for((i=1;i<=ncol;i++))
do
    cut -d " " -f $i file.txt|xargs
done
```