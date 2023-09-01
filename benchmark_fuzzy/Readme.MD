TRF  
time -p trf Col-0.Chr_scaffolds.fa 2 7 7 80 10 24 6 -h -l 6 -ngs > trf.dat  
perl step1.dat2bed.pl trf.dat > trf.dat.bed  
#remove centromere, 5S rDNA, 45S rDNA and telomere  
bedtools subtract -A -a trf.dat.bed -b Col-0.Repeats_merged.gff > trf.dat.nocentro.bed  
bedtools sort -i trf.dat.nocentro.bed > trf.dat.nocentro.sorted.bed  
python3 step2.overlap.trf.py trf.dat.nocentro.sorted.bed trf.dat.nocentro.sorted.overlap.bed  

BLISTR  
time -p ../src/BLISTR fuzzy_costom -f Col-0.Chr_scaffolds.fa -l 6 -c 12,6,4,3,2,2 -p 0.2,0.3,0.4,0.5,0.5,1 -e 1,1,1,1,1,1 > BLISTR.c12-6-4-3-2-2.p0.2-0.3-0.4-0.5-0.5-1.e1-1-1-1-1-1.out  
bedtools subtract -A -a BLISTR.c12-6-4-3-2-2.p0.2-0.3-0.4-0.5-0.5-1.e1-1-1-1-1-1.out -b Col-0.Repeats_merged.gff > BLISTR.c12-6-4-3-2-2.p0.2-0.3-0.4-0.5-0.5-1.e1-1-1-1-1-1.out.noncentro.bed  
bedtools intersect -f 0.5 -a trf.dat.nocentro.sorted.overlap.bed -b BLISTR.c12-6-4-3-2-2.p0.2-0.3-0.4-0.5-0.5-1.e1-1-1-1-1-1.out.noncentro.bed -v | wc -l  
bedtools intersect -f 0.5 -a trf.dat.nocentro.sorted.overlap.bed -b BLISTR.c12-6-4-3-2-2.p0.2-0.3-0.4-0.5-0.5-1.e1-1-1-1-1-1.out.noncentro.bed -wa -wb | awk '{print $3-$2"\t"$25}' > overlap.site  


Look4TRs  
time -p Look4TRs --adr Col-0.Chr_scaffolds.fa.divide --out Col-0.Chr_scaffolds.fa.out --min 4 --max 6 --idn 50 --int 10 --mtf 1 --thr 1 --prn 2000 --ord 0 --minm 1 --maxm 6 --win 4 --seg 3000000 2> Look4TRs.err  
