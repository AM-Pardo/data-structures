# data-structures
Collection of small, focused projects implementing data structures in C and Java. Demonstrating dynamic memory management, tree operations, linked lists, and sorting.

## Projects
- **bst-ipv4-address-book:**
Binary Search Tree implementation of an IPv4 address book. Supports insert, search, update, delete, in-order traversal and location based lookup. Initial entries are read from a file and logs invalid input lines to an error log.
- **ipv4-address-book:**
Linked List implementation of an IPv4 address book. List is built from an input file and supports insert, search, update, deletion and saving back to disk.

- **string-sorter:**
Reads list of strings, validates input and sorts data using bubble sort in ascending or descending ASCII order.

- **bst-address-book-java:**
Binary Search Tree implementation of a name and address book in Java.
Supports insert, lookup, update, delete, in-order traversal and file loading.

- **hash-table-linear-probing:**
Hash table implementation in Java using linear probing for collision resolution. Tracks probe counts for each insertion to measure efficiency .

- **array-queue:**
Array-based queue implementation in Java using a circular buffer. Supports enqueue, dequeue, peek and overflow/underflow detection.

## Building
C Projects can be compiled with GCC: 
```
gcc src/filename.c -o output
```
Java projects can be compiled with: 
```
javac FileName.java
```
## Requirements
- GCC
- C standard library
- Java JDK
