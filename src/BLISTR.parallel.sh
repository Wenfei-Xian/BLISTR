#!/bin/bash

# 检查参数个数
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <fasta> <num_threads>"
  exit 1
fi

seqkit split2 -p $2 $1 --force

# 设置文件夹和线程数量
DIRECTORY=$1.split
NUM_THREADS=$2

# 使用GNU parallel 并行运行 BLISTR
parallel -j ${NUM_THREADS} '/tmp/global2/wxian/software/BLISTR/src/BLISTR fuzzy_costom -l 20 -c 10,5,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 -p 0.3,0.4,0.5,0.5,0.5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 -e 1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4 -f {}' ::: ${DIRECTORY}/*
