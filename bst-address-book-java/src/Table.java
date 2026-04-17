import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

/** This class implements a binary search tree of key/value pairs of strings **/
public class Table {

	/**Root node in tree */
	private Node root;
	
	/**
	 * Inserts a new Node into the table. If the provided key already 
	 * exists, no entry will be created. Otherwise, the new entry is 
	 * added to the table. Serves as a wrapper for insertNode()
	 * @param key
	 * @param value
	 * @return True if the new node was inserted successfully
	 * 		   False if the provided key already exists in the table
	 */
	public boolean insert(String key, String value) {
		if (lookUp(key) != null) {
			return false;
		}
		Node newNode = new Node(key, value);
		root = insertNode(root, newNode);
		return true;
	}
	
	/**
	 * Inserts a new node into a binary search tree
	 * If the new node key is not unique, the new node will not be added
	 * @param parent Root node of the tree
	 * @param newNode Node to add
	 * @return Root node of the altered tree
	 */
	private Node insertNode(Node parent, Node newNode) {
		if(parent == null) {
			return newNode;
		}
		
		int cmp = newNode.getKey().compareTo(parent.getKey());
		if (cmp < 0) {
			parent.setLeft(insertNode(parent.getLeft(), newNode));
		} else if (cmp > 0) {
			parent.setRight(insertNode(parent.getRight(), newNode));
		}
		return parent;
	}
	
	/**
	 * Looks up the table entry with the provided key
	 * @param key
	 * @return The value of the entry with the provided key. Null if
	 *	       no entry with the key can be found
	 */
	public String lookUp(String key) {
		Node node = lookUpNode(root, key);
		if (node == null) {
			return null;
		}
		
		return node.getValue();
	}
	
	/**
	 * Looks up the node in the binary search tree
	 * @param parent Root node of the tree
	 * @param key Key of the node to search for
	 * @return The Node with the provided key
	 *		   Null if no entry with the key can be found
	 */
	private Node lookUpNode(Node parent, String key) {
		if (parent == null) {
			return null;
		}
		
		int cmp = key.compareTo(parent.getKey());
		if (cmp == 0) {
			return parent;
		} else if (cmp < 0) {
			return lookUpNode(parent.getLeft(), key);
		} else {
			return lookUpNode(parent.getRight(), key);
		}
	}
	
	/**
	 * Updates the value for an existing key
	 * @param key The key of the entry to update
	 * @param newValue The new value to assign
	 * @return True if the entry was updated successfully.
	 * 		   False if no entry with the given key was found
	 */
	public boolean update(String key, String newValue) {
		Node node = lookUpNode(root, key);
		if (node == null) {
			return false;
		}
		node.setValue(newValue);
		return true;
	}
	
	
	/**
	 * Deletes the table entry with the given key
	 * @param key
	 * @return True if the entry was successfully deleted. 
	 * 	       False if no entry with the given key was found
	 */
	public boolean delete(String key) {
		if (lookUp(key) == null) 
			return false;
		root = deleteNode(root, key);
		return true;
	}
	
	/** 
	 * Deletes the node with the provided key from the given tree
	 * @param parent The root of the tree containing the node to delete
	 * @param key The key of the node to delete
	 * @return The root node of the altered tree
	 */
	private Node deleteNode(Node parent, String key) {
		if (parent == null) {
			return null;
		}
		
		int cmp = key.compareTo(parent.getKey());
		if (cmp < 0) {
			parent.setLeft(deleteNode(parent.getLeft(), key));
		} else if (cmp >0) {
			parent.setRight(deleteNode(parent.getRight(), key));
		} else {
			if(parent.getLeft() == null) {
				return parent.getRight();
			}
			if (parent.getRight() == null) {
				return parent.getLeft();
			}
			Node largest = findLargestNode(parent.getLeft());
			parent.setKey(largest.getKey());
			parent.setValue(largest.getValue());
			
			parent.setLeft(deleteNode(parent.getLeft(), largest.getKey()));
		}
		return parent;
	}
	
	/** 
	 * Finds the largest node in the provided tree
	 * @param parent The root in the provided tree
	 * @return the largest node in the provided tree
	 */
	private Node findLargestNode(Node parent) {
		while (parent.getRight() != null) {
			parent = parent.getRight();
		}
		return parent;
	}
	
	/**
	 * Saves the table to a text file
	 * @param filename Name of the file to contain the table
	 */
	public void save(String filename) {
		try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
			writeNode(writer, root);
		} catch (IOException e) {
			System.out.println("Error saving to a text file.");
		}
	}
	
	/** 
	 * Writes a tree to a file using pre-order traversal
	 * (parent, left, right)
	 * @param write Writer to the file
	 * @param node Root node of the tree to write
	 * @throws IOException
	 */
	private void writeNode(BufferedWriter writer, Node node) throws IOException{
		if (node == null) {
			return;
		}
		writer.write(node.getKey());
		writer.newLine();
		writer.write(node.getValue());
		writer.newLine();
		writeNode(writer, node.getLeft());
		writeNode(writer, node.getRight());
	}
	
	/**
	 * Displays all node in the table
	 * @return The number of nodes in the table
	 */
	public int displayAll() {
		return displayNode(root);
	}
	
	/**
	 * Displays all nodes in a (sub)tree using in-order traversal
	 * (left, parent, right)
	 * @param node The root node of the tree to display
	 * @return The number of nodes in the tree
	 */
	private int displayNode(Node node) {
		if (node == null)
			return 0;
		
		int count = 0;
		
		count += displayNode(node.getLeft());
		System.out.println("Name: " + node.getKey());
		System.out.println("Address: " +node.getValue());
		System.out.println();
		count ++;
		count += displayNode(node.getRight());
		return count;
	}
}




