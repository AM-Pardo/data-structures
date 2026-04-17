# BST Address Book
An address-book application implemented in Java using a Binary Search Tree (BST).
Allows users to store, retrieve, update, delete and persist contact information. 

## Features
**Operations** 
- Insert new name and address pairs
- Look up addresses by name
- Delete entries
- Update existing entries
- In-order traversal for sorted alphabetical output
- Pre-order traversal for saving data to file
- Load entries from a file

**Error Handling**
- Prevents duplicate names being inserted
- Handles missing file or read/write errors

## Files
- AddressBook.java: Driver program - contains menu loop and file loading
- Table.java: BST implementation - methods for insert, lookup, update, delete and save
- Node.java: BST node - Stores key/value pair and child references

## How to Compile
```
javac Node.java Table.java AddressBook.java
```

## How to Run
```
java AddressBook
```
## Usage
At startup User will be prompted to optionally load entries from a file. A menu will then list the following: 
```
Add a name (n)
Look up a name (l)
Update address (u)
Delete an entry (d)
Display all entries (a)
Save address book (s)
Quit (q)
```
User selecting Save (s) will write current tree into a file though pre-order traversal.
User selecting Quit (q) exits the program.

## Example Input
Program optionally loads entries from a file at startup. This example opens file 'Book1.txt' with each line containing name followed by -> then corresponding address
```
James Smith -> 1545 Park Ave
Nicole Moore -> 275 Gallows St
Emma Ronan -> 487 Manhattan Ave
Jake Farms -> 154 State St
Daniel Bale -> 1567 Washington Lane
```

## Example Output
```
Do you want to open a file? (y/n)
y
Enter file name: 
Book1.txt
Inserting: James Smith->1545 Park Ave
Inserting: Nicole Moore->275 Gallows St
Inserting: Emma Ronan->487 Manhattan Ave
Inserting: Jake Farms->154 State St
Inserting: Daniel Bale->1567 Washington Lane

Add a name (n)
Look up a name (l)
Update address (u)
Delete an entry (d)
Display all entries (a)
Save address book (s)
Quit (q)
->a
Name: Daniel Bale
Address: 1567 Washington Lane

Name: Emma Ronan
Address: 487 Manhattan Ave

Name: Jake Farms
Address: 154 State St

Name: James Smith
Address: 1545 Park Ave

Name: Nicole Moore
Address: 275 Gallows St
```

## Algorithmic Notes
**Binary Search Tree**
Nodes are ordered alphabetically by alias using case-sensitive comparison using String.compareTo. Each node contains a key/value string pair and left/right child references.

**Deletion cases Handled**
- Node with no children - removed directly
- Node with one child - replaced by that child
- Node with two children - replaced by inorder successor

## Time Complexity
- Insert, Look Up, Update and Delete: O(log n) average, O(n) worst case
- Display All: O(n)
> Worst case occurs when entries are inserted in alphabetical order. An AVL tree (self-balancing) would quarantee O(log n) in all cases.
## Why This Project Matters
- Implementation of a core data structure (BST) in Java
- OOP design with encapsulated Node and Table classes
- File serialization using pre-order traversal preserves tree structure
