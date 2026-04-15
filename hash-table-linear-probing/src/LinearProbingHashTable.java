public class LinearProbingHashTable {

	private int[] table;
	private int size;
	
	//Initialize table
	public LinearProbingHashTable(int size) {
		this.size = size;
		table = new int[size];
		for (int i = 0; i < size; i++)
			table[i] = -1;
	}
	
	// Hash function
	private int hash(int key) {
		return key % size;
	}
	
	// Insert key to hash table with linear probing
	public int insert(int key) {
		int home = hash(key);
		int i =0;
		int probes = 0;
		
		while (i < size) {
			int index = (home + i) % size;
			probes++;
			
			if (table[index] == -1) {
				table[index] = key;
				return probes;
			}
			i++;
		}
		return probes;
	}
	
	// print hash table
	public void display() {
		System.out.println("Index | Value");
		for (int i = 0; i < size; i++) {
			System.out.println(i + " | " + table[i]);
			
		}
	}
	
	public static void main(String[] args) {
		int [] keys = {12, 18, 13, 2, 3, 23, 5, 15};
		LinearProbingHashTable hashTable  =new LinearProbingHashTable(10);
		int totalProbes = 0;
		System.out.println("Inserting: ");
		for (int key : keys) {
			int probes = hashTable.insert(key);
			totalProbes += probes;
			System.out.println("Inserted " + key + " with " + probes + (probes == 1 ? " probe" : " probes"));
		}
		System.out.println("\nHash Table:");
		hashTable.display();
		
		double average = (double) totalProbes / keys.length;
		System.out.println("\nAverage number of probes = " + average);
	}

}
