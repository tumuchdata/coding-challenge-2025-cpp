# TUMuchData Coding Challenge 2025
## Motivation
Modern analytical databases use data skipping to avoid scanning irrelevant data blocks.
Your task is to design such a data skipping index for a simplified scenario.
Read more in our [blogpost](https://www.tumuchdata.club/post/data-skipping/).

## The challenge
You must design a custom data skipping index structure that helps decide whether a data block can be skipped for a given query.
The goal is to minimize the total workload cost consisting of storage and access cost.

Each query is of the form:
    
    SELECT COUNT(*) FROM table WHERE column = x;

The table consists of a single column of unsigned 32bit integers.

The index is asked for each block of data in the table how often it contains the value x.
The index may respond with the exact number or an indication that it does not know the answer.
In this case, the query engine needs to compute the result from the base data.
A single wrong response invalidates the run.

Your entire implementation should be in `User.hpp` as only a single file is uploaded to the submission system. In this file, you need to implement two functions:

    std::vector<std::byte> build_idx(std::span<const uint32_t> data, Parameters config)

`build_idx` receives the contents of a data block that should be indexed and a configuration describing the current workload. Notably `config` contains the values of $F_A$, describing the importance of access cost, and $F_S$, for the storage cost. Based on this information, you should create a custom index structure and wrap its content (raw bytes) as a `std::vector<std::byte>`.

Hint: use `reinterpret_cast`

    std::optional<size_t> query_idx(uint32_t predicate, const std::vector<std::byte>& index)

`query_idx` receives the custom index you have previously constructed for a specific block and has to decide whether it is necessary to scan the underlying block or the index can be used to answer the count query. If the index can answer the query, simply return the number of times `predicate` is contained in the underlying block, otherwise return `std::nullopt`.

## Scoring
Your solution is evaluated based on the total workload cost, computed as: 
<center>Total Workload Cost = Access Cost + Storage Cost</center>

### Scoring Function
```math
Score = (F_A * \text{\# skipped blocks}) - (F_S * \text{size of index in KiB})
```
The displayed score is normalized to 100 points per test case by dividing by the maximum achievable number of points for that test case.
```math
Normalized Score = 100 * \frac{Score}{F_A * \text{\#blocks} * \text{\#queries}}
```

The total score is the sum of the scores for the 3 individual test cases.

You gain points by correctly deciding to skip accessing blocks of base data. However, you lose points for the storage footprint of your index structure.
$F_A$ and $F_S$ are factors that indicate the relative cost of both kinds of costs. Your solution should be robust to varying $F_S$ and $F_A$.

An accurate but overly large index might reduce access costs but increase storage costs disproportionately. Conversely, a compact but imprecise index might lead to higher access costs due to more unnecessary block scans. The challenge is to find the optimal balance for the particular workload.

### Constraints
- 1 <= $F_A,F_S$ <= 100
- Number of unsigned 32bit integers in a block = 131072

## Resources
- [Leaderboard & Submission Website](http://contest.tumuchdata.club)
- More about [TUMuchData](http://tumuchdata.club)
- Prefer Rust to C++? Check out the [Rust Skeleton](https://github.com/tumuchdata/coding-challenge-2025-rust) for this challenge
