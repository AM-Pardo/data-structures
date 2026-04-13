# **IPv4 Address Book (C)**
A c program that stores, searches, updates and deletes IPv4 address-alias pairs using a singly linked list. 
The program loads initial data from a file, provides a menu-driven interface and supports saving the updated list back to disk.

## **Features**
- Loads IPv4 address and alias pairs from a file
- Strores entries ina singly linked list
- Supports:
  - Adding new addresses
  - Looking up an address by aliash
  - Updating an existing address
  - Deleting an entry
  - Displaying all entries
  - Displaying aliases for a given locaiton (first two octets)
  - Saving the list to a new file
- Validates:
  - Alias lenght (<= 10 characters)
  - Duplicate aliases and IPv4 addresses
  - IPv4 octet ranges (0-255)
    
## **How to Compile**
```
gcc src/ipv4_address_book.c -o ipv4_address_book
```
## **How to Run**
```
./ipv4_address_book
```
## **Example Input file (address_book.txt)



## **Example Program Out**

## **Data Structure Overview**
**Linked List Node**
Each entry contains: 
- Four IPv4 octets
- Alias (up to 10 chars)
- Pointer to next node
**Operations**
  - Insert at head for O(n) insertion
  - Linear search for lookup, update and delete
  - Traversal for display and save operations
 
##  **Why This Project Matters**
This project implements a functional IPv4 address book using a singly linked list
It demonstrates practical systems-level skills:
- Parsing and validating IPv4 addresses from user input and files
- Managing dynamic memory and pointer-based data structures
- Implementing insertion, deletion, search, and update operations in a linked list
- Designing a menu-driven interface for interactive programs
- Handling file I/O for loading and saving structured data
- Preventing duplicate entries thorugh linear search and validation logic

These capabilities ar edirectly relevant to vuilding low-level utilities, networking tools, and data-structure-driven applications in C. 
