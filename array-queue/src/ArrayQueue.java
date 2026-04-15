 // Array based queue implementation
class QueueArrayBased {

		private int arr[]; // Array to store queue elements
		private int front; // Front points to front element in the queue (if any)
		private int rear; //  Rear points to last element in the queue
		private int capacity; // Maximum capacity of the queue
		private int count; // Current size of the queue
		
		// Constructor to initialize queue
		QueueArrayBased(int size){
			arr = new int [size];
			capacity = size;
			front = 0;
			rear = -1;
			count = 0;
		}
		
		// Utility function to add an item to the queue
		public void enqueue(int item) {
			// Check for queue overflow
			if (isFull()) {
				System.out.println("Overflow\nProgram Terminated");
				System.exit(1);
			}
			rear = (rear + 1) % capacity;
			arr[rear] = item;
			count ++;
		}
		
		// Utility function to remove front element from the queue
		public void dequeue() {
			// Check for queue underflow
			if (isEmpty()) {
				System.out.println("Underflow\nProgram Terminated");
				System.exit(1);
			}
			front = (front +1) % capacity;
			count --;
		}
		
		// Utility function to return front element in the queue
		public int peek() {
			// Check for queue underflow
			if (isEmpty()) {
				System.out.println("UnderFlow\nProgram Terminated");
				System.exit(1);
			}
			return arr[front];
		}
		
		// Utility function to return the size of the queue 
		public int size() {
			return count;
		}
		
		// Utility function to check if the queue is empty or not
		public Boolean isEmpty() {
			return (size() == 0);
		}
		
		// Utility function to check if the queue is full or not
		public Boolean isFull() {
			return (size() == capacity);
		
		}
		
		// Function to print queue 
		public void printList() {
			if(isEmpty()) {
				return;
			}
			for (int i= 0; i < count; i++) {
				int index = (front + i) % capacity;
				System.out.print(arr[index]);
				if (i < count - 1) {
					System.out.print(",");
				}
			}
			System.out.println();
		}
} 

//Main Queue Class
public class ArrayQueue {
	// Main function
	public static void main(String[] args) {
		// Create a queue of capacity 5
		QueueArrayBased q = new QueueArrayBased(5);
		
		// Enqueue three numbers
		q.enqueue(6);
		q.enqueue(9);
		q.enqueue(4);
		
		// Dequeue three times
		q.dequeue();
		q.dequeue();
		q.dequeue();
		
		// Enqueue three different numbers
		q.enqueue(5);
		q.enqueue(7);
		q.enqueue(2);
		
		// Dequeue one time
		q.dequeue();
		
		// Enqueue three different numbers
		q.enqueue(22);
		q.enqueue(19);
		q.enqueue(26);
		
		// Dequeue two times
		q.dequeue();
		q.dequeue();
		
		// Enqueue two different numbers
		q.enqueue(55);
		q.enqueue(45);
		
		// Dequeue one time
		q.dequeue();
		
		// Print front element and queue size
		System.out.println("Front element is: " + q.peek());
		System.out.println("Queue size is: " + q.size());
		
		// Check if empty and print queue status
		if (q.isEmpty())
			System.out.println("Queue Is Empty");
		
		else 
			System.out.println("Queue Is Not Empty");
		
		// Print contents of queue 
		System.out.println("Contents of the queue: ");
		q.printList();
		
	} // End main
} // End class