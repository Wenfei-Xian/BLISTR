TRF  
time -p trf Col-0.Chr_scaffolds.fa 2 7 7 80 10 24 6 -h -l 6 -ngs > trf.dat  
perl step1.dat2bed.pl trf.dat > trf.dat.bed  
#remove centromere, 5S rDNA, 45S rDNA and telomere  
bedtools subtract -A -a trf.dat.bed -b Col-0.Repeats_merged.gff > trf.dat.nocentro.bed  
bedtools sort -i trf.dat.nocentro.bed > trf.dat.nocentro.sorted.bed  
python3 step2.overlap.trf.py trf.dat.nocentro.sorted.bed trf.dat.nocentro.sorted.overlap.bed  

BLSTR
