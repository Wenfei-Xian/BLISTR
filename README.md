# BLISTR
BLurry Imperfect Short Tandem Repeats in DNA and Protein sequences

# Motivation  

# Getting Started  
## Prerequisite
The only dependency for BLISTR is zlib, which is used for handling gz-compressed files.  
## Installation  
```
git clone https://github.com/Wenfei-Xian/BLISTR.git  
cd BLISTR/src  
make
```
## Installation with Bioconda  
```
conda install BLISTR`  
```
# Usage  
## Input Files  
DNA or protein sequences in fasta format, which can be compressed in gz format.   

## Running BLISTR
```
BLISTR perfect_str_default -f test.fa > test.fa.blistr.out
```

## Available Options:
```
BLISTR: BLurry Imperfect Short Tandem Repeats
Usage: BLISTR <command> [options]
Command:
	perfect_str_default <options>
	perfect_costom <options>
	fuzzy_str_default <options>
	fuzzy_costom <options>
```  
