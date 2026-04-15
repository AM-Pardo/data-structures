# Array Queue
A Java program that implements a fixed-capacity queue using a circular array with enqueue, dequeue and peek operations.
## Features
**Operations**
  - Enqueue: adds an element to the rear of the queue
  - Dequeue: removes the front element from the queue
  - Peek: returns the front element without removing it
  - Size: returns the current number of elements
  - isEmpty/isFull: checks queue status
  - printList: prints all current queue elements

## How to Compile
javac ArrayQueue.java

## How to Run
java ArrayQueue

## Example Output
```
Front element is: 19
Queue size is: 4
Queue Is Not Empty
Contents of the queue: 
19,26,55,45
```
## Algorithmic Notes
**Circular Array**
- Instead of shifting elements after each dequeue, the front and rear pointers advance using modulo arithmetic (index +1) % capacity, allowing array to wrap around. 

**Overflow and underflow**
- Enqueue checks isFull() before inserting and exits if capacity is reached. Dequeue and peek check isEmpty() before operating and exits if the queue is empty.

## Why This Project Matters
- Use of circular array logic to avoid unnecessary element shifting
- Demonstrates a core linear data structure in Java
- Tracks front, rear, capacity and count for full queue state management
