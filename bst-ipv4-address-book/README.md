# IPv4 Address Book (Binary Search Implementation)
A C program that reads in a file containing IPv4 address paired with an alias to construct an address book using a Binary Search Tree (BST). This program validates each entry, logs invalid entries and supports insertion, lookup, deletion and sorted traversal.

## Features
**Operations** 
- In-order traversal for sorted output
- File parsing and input validation
- Error logging for invalid input
- Height and depth tracking per node
- Update existing entry
- Node deletion according to all three BST deletion cases
- Interactive menu

**Error Handling**

Input is invalidated and saved to an error log file for the following:
- Illegal IPv4 format (octet out of 0-255 range, wrong number of octets)
- Alias violations (longer than 10 characters, uppercase letters, spaces, non-printable characters)
- Duplicate IP addresses or alias
- Empty lines
- Extra fields on a line

## How to Compile
gcc src/ipv4_address_bookbst.c -o ipv4_address_book_bst

## How to Run
Ensure data/ directory exists and contains address_input2.txt before running:

./ipv4_address_bookbst

## Example Input
Program loads initial entries from data/address_input2.txt file using a binary search tree. Each line containing an IPv4 address paired with an alias separated by whitespace:
```
111.22.3.44 jess
131.250.95.21 amanda
131.350.3.4.5 jacob
172.66.7.88 may
132.43.7.88 james 12
111.22.5.66 purple
172.333.32.5 smith2
131.250.47.63 baker
```
Invalid lines (jacob, james 12, smith2) are written to data/input_error_log.txt and skipped.

## Example Output
```
1)Add address
2)Look up address
3)Update address
4)Delete address
5)Display List
6)Display Aliases for location
7)Display Error Log
8)Quit
Enter Option: 5

amanda          131.250.95.21 height:1 depth:1 parent: jess
baker           131.250.47.63 height:0 depth:2 parent: amanda
jess            111.22.3.44 height:2 depth:0 parent: NONE
may             172.66.7.88 height:1 depth:1 parent: jess
purple          111.22.5.66 height:0 depth:2 parent: may
```
## Algorithmic Notes
**Binary Search Tree**

Nodes are ordered alphabetically by alias using case-insensitive comparison (strcasecmp). 

Each node contains:
- Four IPv4 octets
- Alias with a max of 10 characters and lowercase
- Left child, right child and parent pointers
- Current height and depth and updated after an insert or deletion
  
**Deletion cases Handled**
- Node with no children - removed directly
- Node with one child - replaced by that child
- Node with two children - replaced by inorder successor

## Validation Logic
Ipv4 address: Exactly four octets, each being 0-255 range
Alias: Range of 1-10 characters, lowercase, no spaces
Line format: Contains exactly two whitespace-separated fields
Duplicates: Each line containing the IP address and alias has to be unique 

## Why This Project Matters
- Implementation of a core data structure (BST) in C
- Defensive programming through input validation and error logging
- Procedural design with modular, single-responsibility functions
