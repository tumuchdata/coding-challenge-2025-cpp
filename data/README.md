# Binary File Structure
In case you want to generate your own additional test cases , understanding the binary layout of data and query files could be helpful. Both files consist of 32bit integers stored in little endian format.

## The data file
- The first integer $N$ is the number of blocks (horizontal partitions)
- The second integer $M$ is the number of values in each block
- The following $N * M$ integers are the actual data. The first $M$ values belong to the first block and so forth.

## The query file
- The first integer $K$ is the number of queries
- The following $K$ integers are instantiations of the parameter in our count query.