/**
 * This class is a single entry in a binary search tree.
 * It stores a key/value pair of strings and references to 
 * the left and right child Nodes in the tree. Implements Comparable<Node> 
 * so nodes can be compared by key.
 */
public class Node implements Comparable<Node>{
	
	/* Node key and value*/ 
	private String key, value;
	
	/* Child Nodes in the tree */ 
	private Node left, right;
	
	/** Creates a new Node
	 * @param key
	 * @param value
	 */
	public Node(String key, String value) {
		this.key = key;
		this.value = value;
		this.left = null;
		this.right = null;
	}
	
	/**
	 * @return The Node key
	 */
	public String getKey() {
		return key;
	}
	
	/**
	 * @param key The Node key
	 */
	public void setKey(String key) {
		this.key = key;
	}
	
	/**
	 * @return The Node value
	 */
	public String getValue() {
		return value;
	}
	
	/**
	 * @param value The Node value
	 */
	public void setValue(String value) {
		this.value = value;
	}
	
	/**
	 * @return The left child Node
	 */
	public Node getLeft() {
		return left;
	}
	
	/**
	 * @param left The left child Node
	 */
	public void setLeft(Node left) {
		this.left = left;
	}
	
	/**
	 * @return The right child Node
	 */
	public Node getRight() {
		return right;
	}

	/**
	 * @param right The right child Node
	 */
	public void setRight(Node right) {
		this.right = right;
	}
	
	/**
	 * Compares a Node to another by key, using String ordering. 
	 * Keeps Node's ordering consistent during insertion and lookups
	 * 
	 * @param other The Node to compare to
	 * @return Negative if the key comes before other's, 0 if equal
	 * 		   and positive if the key comes after
	 */
	@Override
	public int compareTo(Node that) {
		return this.key.compareTo(that.key);
	}
	
	@Override
	public String toString() {
		return String.format("%s%n%s%n",  this.key, this.value);
	}
}









