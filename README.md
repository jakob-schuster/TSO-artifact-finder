A program for finding out how many reads in a Fastq have TSO (template switching oligo) artifacts.

Parses an input `.fq` or `.fastq` file, finding which reads contain faulty TSO information.

# Usage instructions

Simply run `./TSO-artifact-finder`, giving one input file to parse, and one output file to store output statistics.

```
./TSO-artifact-finder input.fq output.csv
```

Optionally, you can include the number of reads you want to parse through - usually a small sample from the start of a file will give a good enough estimation.

```
./TSO-artifact-finder input.fq output.csv 10000
```

You can also include a custom TSO sequence, if for some reason your reads use an alternative TSO.

```
./TSO-artifact-finder input.fq output.csv 10000 AAGCAGTGGTATCAACGCAGAGTACATGGG
```

# How it works

A normal read is assumed to include a TSO. If the read is a reverse read, it will include the TSO's reverse complement instead.

```
AGACT .. [TSO] .. AGAGATCTAG
CCGTTAGG .. [TSO reverse complement] .. AAGC
```

Some reads have:
1. the TSO or its reverse complement repeated multiple times, or 
2. include both the TSO and its reverse complement in the one read. 
These reads are often the result of multiple reads being unintentionally concatenated together, and they are called "TSO artifacts".

```
AAAGTTAG .. [TSO] .. CTGACC .. [TSO] .. TTGAC
TTGACG .. [TSO reverse complement] .. AAGTG .. [TSO] .. GTGCA
```

This program counts the occurrences of the TSO and TSO reverse complement in each read. This is done with a string search, allowing for an edit distance of 3 (hence the TSO does not need to perfectly match). If a read matches either of the above criteria, this is considered as a TSO artifact.

The program will output the number of TSO artifacts it finds to the console and the `output.csv`, and what percentage of reads have TSO artifacts.