# **Tools for comparison**  

Kmer-ssr: v0.8  
Misa: v2.1  
PERF: v0.4.6  
divissr: v0.1.2  
dot2dot: v1.0  

  
# **Command for each tool**  
``` 
genome=t2t-col.20210610.fa  
Kmer-ssr: kmer-ssr -i $genome -o kmer-ssr.out -n 10 -p 1-6  
Misa: perl misa.pl $genome (**misa.ini**)  
PERF_python: python ../bin/perf/PERF/core.py -i $genome -m 1 -M 6 -u **repeat_units.txt** -o python.PERF.out  
PERF_pypy: pypy ../bin/perf/PERF/core.py -i $genome -m 1 -M 6 -u **repeat_units.txt** -o pypy.PERF.out  
divissr: python3 ../bin/divissr/divissr/core.py -i $genome -o $1.divissr.out  
Dot2dot: dot.linux -c **dot2dot.config** -s $genome 1> dot2dot.out  
BLISTR perfect_str_default -f $genome 1> BLISTR_perfect.out  
```
**Time comsumming**  
see time.txt
