**List of tools for comparison along with their respective version numbers**  
Kmer-ssr: v0.8  
Misa: v2.1  
PERF: v0.4.6  
divissr: v0.1.1  
dot2dot: v1.0 

**Command for each tool**
Kmer-ssr: kmer-ssr -i $1 -o kmer-ssr.TAIR10.out -n 10 -p 1-6
Misa: perl misa.pl $1
PERF_python: python ../bin/perf/PERF/core.py -i $1 -m 1 -M 6 -u repeat_units.txt -o python.PERF.out
PERF_pypy: pypy ../bin/perf/PERF/core.py -i $1 -m 1 -M 6 -u repeat_units.txt -o pypy.PERF.out
divissr: python3 ../bin/divissr/divissr/core.py -i $1 -o $1.divissr.out
Dot2dot: dot.linux -c dot2dot.config -s $1 1> dot2dot.out
