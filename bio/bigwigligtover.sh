# reference https://www.biostars.org/p/81185/#476941
chain="/store/qzhong/soft/biosoft/ucsctools/liftover/hg19ToHg38.over.chain"
chromsizes="/store/qzhong/bio/hicdata/hg19_repliseq/hg38.chromsizes"
for bw in `ls *bigWig`
do
    hg19bw=${bw%%.bigWig}.hg19.bw
    hg19bg=${bw%%.bigWig}.hg19.bedGraph
    hg38bg=${bw%%.bigWig}.hg38.bedGraph
    hg38novbg=${bw%%.bigWig}.hg38.nov.bedGraph
    hg38bw=${bw%%.bigWig}.hg38.bw
    echo $hg19bw $hg19bg $hg38bg $hg38novbg $hg38bw

    mv $bw $hg19bw
    # 1) Convert bigwig to bedGraph
    bigWigToBedGraph $hg19bw $hg19bg
    # 2) Liftover from mm9 to mm10
    liftOver  $hg19bg $chain $hg38bg ${hg19bg}.unmapped
    # 3) Sort the bed file
    sort -k1,1 -k2,2n ${hg38bg} --output ${hg38bg}
    # 4) Fix the overlapping intervals
    # The bed file from liftover might have overlapping intervals. You will hit
    # error if directly using bedGraphToBigWig for file conversion. In this case,
    # you need to split the overlapping intervals and assign mean signal to a new
    # bed file.
    awk -vOFS="\t" '{ print $1, $2, $3, ".", $4 }'  ${hg38bg} > tmp.bed
    bedops --partition tmp.bed | bedmap --echo --mean --delim '\t' - tmp.bed > $hg38novbg

    # 5) Convert bedGraph to bigwig
    bedGraphToBigWig  $hg38novbg $chromsizes $hg38bw
done