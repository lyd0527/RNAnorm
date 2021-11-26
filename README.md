# RNAnorm
Normalization of RNA-seq expression counts


### Supported methods:

- Counts per million (CPM)
- Fragments Per Kilobase of transcript per Million mapped reads (FPKM)
- Transcript per kilobase million (TPM)


### Filtering for coexpression network construction such as WGCNA

- MADs
- coefficient of variation (CV)


### Dependencies
1. gcc 4.8+ or clang 3.4+
2. cmake 3.2+


### Getting start
```
git clone https://github.com/lyd0527/RNAnorm.git
cd RNAnorm; make

Usage: RNAnorm <OPTION>

Option:

	-i 	raw count maxtrix from featureCount or HTSeq
	-o 	output prefix
	-f 	filtering or not [off]
	-v 	minimum threshold value of MAD or CV [0.01]
	-m 	method: CV or MAD [CV]
```

### Examples:

Count2FPKM/TPM
```
./RNAnorm -i count.input -o output_prefix
```

Count2FPKM/TPM + Filtering (CV method)
```
./RNAnorm -i count.input -o output_prefix -f -v 0.01 -m CV
```

Count2FPKM/TPM + Filtering (MAD method)
```
./RNAnorm -i count.input -o output_prefix -f -v 0.01 -m MAD
```
