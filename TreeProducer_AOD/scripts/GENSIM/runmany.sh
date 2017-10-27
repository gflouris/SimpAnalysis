#!/bin/bash

#$1 number of jobs

#jobs=$1

#dir="Out_"`date +"%F_%T"`
#mkdir $dir
for j in {1..10}; do
  for i in {1..12}; do

    jobname=Job_${i}\_${j}
    #seed=4234${i}

    export LS_JOBNAME=${jobname}
    export id=${i}
    export id1=${j}
    export direc=$(pwd)
    cp SUS-RunIISummer15GS-00146_IIDD_cfg.py ./SUS-RunIISummer15GS-00146_IIDDD_cfg.py
    sed -i "s/IIDD/$id\_$id1/g" ./SUS-RunIISummer15GS-00146_IIDDD_cfg.py
    rename IIDDD $id\_$id1 ./SUS-RunIISummer15GS-00146_IIDDD_cfg.py
    cp ./simp.sh ./simptmp.sh
    sed -i "s/IDDD/$id\_$id1/g" ./simptmp.sh
    sed -i "s@PPWWDD@$direc@g" ./simptmp.sh

    qsub -q localgrid -N simp10_gensim -o script_${i}\_${j}.stdout -e script_${i}\_${j}.stderr < simptmp.sh
    #rm ./simptmp.sh

  done
done


