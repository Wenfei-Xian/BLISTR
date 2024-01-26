# BLISTR
BLurry Imperfect Short Tandem Repeats in DNA and Protein sequences

# Motivation  
XXX

# Getting Started  
## Prerequisite
The only dependency for BLISTR is zlib, which is used for handling gz-compressed files.  
## Installation  
```
git clone https://github.com/Wenfei-Xian/BLISTR.git  
cd BLISTR/src  
make
```
## Installation with Bioconda (on the way)
```
conda install BLISTR  
```
# Usage  
## Input Files  
DNA or protein sequences in fasta format, which can be compressed in gz format.   

## Running BLISTR
```
BLISTR perfect_str_default -f test.fa > test.fa.blistr.out
```
## Identify tandem repeats of amino acid on uniprot set
```
wget https://ftp.uniprot.org/pub/databases/uniprot/knowledgebase/complete/uniprot_sprot.fasta.gz
BLISTR fuzzy_str_default -f uniprot_sprot.fasta.gz > uniprot_sprot.fasta.blistr.fuzzy.out
```  

## Available Commands:
```
BLISTR: BLurry Imperfect Short Tandem Repeats
Usage: BLISTR <command> [options]
Command:
	perfect_str_default <options>
	perfect_custom <options>
	fuzzy_str_default <options>
	fuzzy_custom <options>
```

## Available Options:
### perfect_str_default  
```
BLISTR: BLurry Imperfect Short Tandem Repeats
Usage: BLISTR perfect_str_default <options>
	unit length range is 1-6bp and copy number threshold is 10,5,4,3,2,2
Options:
       -f string     fasta format file (mandatory)
       -s int        whether output the flanking sequence of SSR region (default value: 0 -> don't output; length of flanking sequences -> output)
       -u int        whether replace all letters with uppercase letters (default value: 0 -> don't replace; 1 -> replace)
       -r int        whether output the reverse complement sequence (default value: 0 -> don't output; 1 -> output)
```
### perfect_custom  
```
BLISTR: BLurry Imperfect Short Tandem Repeats
Usage: BLISTR perfect_custom <options>
Options:
       -f string     fasta format file (mandatory)
       -l int        maximum length of SSR unit, example: -l 10 (mandatory)
       -c string     copy threshold for each unit, example: -c 10,5,4,3,2,2,2,2,2,2 (mandatory)
       -s int        whether output the flanking sequence of SSR region (default value: 0 -> don't output; length of flanking sequences -> output)
       -u int        whether replace all letters with uppercase letters (default value: 0 -> don't replace; 1 -> replace)
       -r int        whether output the reverse complement sequence (default value: 0 -> don't output; 1 -> output)
```
### fuzzy_str_default
```
BLISTR: BLurry Imperfect Short Tandem Repeats
Usage: BLISTR fuzzy_str_default <options>
	unit length range is 1-6bp, copy number threshold is 12,6,4,3,2,2, percentage of imperfect threshold is 0.3,0.4,0.5,0.5,0.5,1, edit distance of each unit is 1,1,1,1,1,1
Options:
	-f string     fasta format file (mandatory)
	-u int        whether to replace all letters with uppercase letters (default value: 0 -> don't replace; 1 -> replace)
	-s int        whether output the flanking sequence of SSR region (default value: 0 -> don't output; length of flanking sequences -> output)
	-r int        whether output the reverse complement sequence (default value: 0 -> don't output; 1 -> output)
```
### fuzzy_custom
```
BLISTR: BLurry Imperfect Short Tandem Repeats
Usage: BLISTR fuzzy_custom <options>
Options:
	-f string     fasta format file (mandatory)
	-l int        maximum length of SSR unit, example: -l 6 (mandatory)
	-c string     copy threshold for each unit, example: -c 12,6,4,3,2,2 (mandatory)
	-p string     percentage of imperfect units, example: -p 0.3,0.4,0.5,0.5,0.5,1 (mandatory)
	-e string     edit distance for each unit, example: -e 1,1,1,1,1,2 (mandatory)
	-d int        Maximum distance between two seperate STR regions, using negative value for overlapping STRs, example: -d -4
	-u int        whether to replace all letters with uppercase letters (default value: 0 -> don't replace; 1 -> replace)
	-s int        whether output the flanking sequence of SSR region (default value: 0 -> don't output; length of flanking sequences -> output)
	-r int        whether output the reverse complement sequence (default value: 0 -> don't output; 1 -> output)
```
# Contact
Questions, suggestions are welcome by raising an issue on the github page.
