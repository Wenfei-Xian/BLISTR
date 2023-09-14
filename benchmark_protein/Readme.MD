# Download the tools  
wget https://bioinfo.crbm.cnrs.fr/tools/treks/T-REKS.zip  
wget https://www.ibi.vu.nl/programs/trustwww/trust.tgz  
wget https://amnewmanlab.stanford.edu/xstream/xstream.zip  

# Commands for XSTREAM  
```  
time -p java -jar xstream.jar $1 -m1 -x20  
python3 xstream.html2bed.py XSTREAM__i0.7_g3_m1_e2.0_out_2.html > XSTREAM__i0.7_g3_m1_e2.0_out_2.html.bed  
perl overlap.pl XSTREAM__i0.7_g3_m1_e2.0_out_2.html.bed > XSTREAM__i0.7_g3_m1_e2.0_out_2.html.rd.bed  
bedtools sort -i XSTREAM__i0.7_g3_m1_e2.0_out_2.html.rd.bed > XSTREAM__i0.7_g3_m1_e2.0_out_2.html.rd.sorted.bed  
awk '{if($3-$2>=10)print}' XSTREAM__i0.7_g3_m1_e2.0_out_2.html.rd.sorted.bed > XSTREAM__i0.7_g3_m1_e2.0_out_2.html.rd.sorted.10aa.bed  
wc -l XSTREAM__i0.7_g3_m1_e2.0_out_2.html.rd.sorted.10aa.bed  
```
# Commands for T-REKS  
```  
#time -p java -jar T-REKS/T-Reks.jar -infile=$1 -similarity=0.8 > T-REKS.out  
time -p for i in `ls uniprot_sprot.2023_03.simpleID.fasta.split/`;do java -jar T-REKS/T-Reks.jar -infile=uniprot_sprot.2023_03.simpleID.fasta.split/$i -similarity=0.8 > uniprot_sprot.2023_03.simpleID.fasta.split/T-REKS.$i.out ;done  
cat uniprot_sprot.2023_03.simpleID.fasta.split/*out > T-REKS.out  
perl T-REKS2bed.pl T-REKS.out > T-REKS.out.bed  
perl overlap.pl T-REKS.out.bed > T-REKS.out.rd.bed  
bedtools sort -i T-REKS.out.rd.bed > T-REKS.out.rd.sorted.bed  
awk '{if(($3-$2)>=10)print}' T-REKS.out.rd.sorted.bed > T-REKS.out.rd.sorted.bed.10aa.bed  
wc -l T-REKS.out.rd.sorted.bed.10aa.bed  
```
# Commands for BLISTR
```
time -p ../BLISTR/src/BLISTR fuzzy_costom -f $1 -l 20 -c 10,5,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 -p 0.3,0.4,0.5,0.5,0.5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 -e 1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4 > BLISTR.bed  
#time -p ../BLISTR/src/BLISTR fuzzy_costom -f $1 -l 10 -c 10,5,3,3,2,2,2,2,2,2 -p 0.3,0.4,0.5,0.5,0.5,1,1,1,1,1 -e 1,1,1,1,1,2,2,2,2,2 -a 1 > BLISTR.bed  
awk 'NR>1{print $1"\t"$2"\t"$3}' BLISTR.bed > BLISTR.bed3  
perl overlap.pl BLISTR.bed3 > BLISTR.rd.bed  
bedtools sort -i BLISTR.rd.bed > BLISTR.rd.sorted.bed  
awk '{if(($3-$2)>=10)print}' BLISTR.rd.sorted.bed > BLISTR.rd.sorted.10aa.bed  
wc -l BLISTR.rd.sorted.10aa.bed  
```
