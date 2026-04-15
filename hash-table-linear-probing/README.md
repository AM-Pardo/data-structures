# Hash Table with Linear Probing
A hash table implementation in Java using linear probing for collision resolution, tracking probe counts per insertion to measure efficiency.

## Features
**Operations**
- Modulo-based hash function
- Linear probing with wraparound indexing
- Per-insertion probe tracking
- Average probe count calculation across all insertions
- Interactive table display

## How to Compile
```
javac LinearProbingHashTable.java
```
## How to Run
```
java LinearProbingHashTable
```
## Example Input

Inserted keys: {12,18,13,2,3,23,5,15}

## Example Output
```
Inserting:
Inserted 12 with 1 probe
Inserted 18 with 1 probe
Inserted 13 with 1 probe
Inserted 2 with 3 probes
Inserted 3 with 3 probes
Inserted 23 with 4 probes
Inserted 5 with 3 probes
Inserted 15 with 5 probes

Hash Table:
Index | Value
0 | -1
1 | -1
2 | 12
3 | 13
4 | 2
5 | 3
6 | 23
7 | 5
8 | 18
9 | 15

Average number of probes = 2.625
```
## Algorithmic Notes
Hash Function: key % size

Linear Probing: On collision, sequentially checks (home +i) % size until an empty slot is found

Probe Tracking: Each insertion records how many slots were checked, used to calculate average insertion efficiency 
