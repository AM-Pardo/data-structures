import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

// Driver program for the address book 
public class AddressBook {

	public static void main(String[] args) {
		// Table declaration
		Table table = new Table();
		Scanner scanner = new Scanner(System.in);
		
		// Prompt user to open a file 
		System.out.println("Do you want to open a file? (y/n)");
		String reply = scanner.nextLine().trim().toLowerCase();
		
		if (reply.equals("y")) {
			System.out.println("Enter file name: ");
			String filename = scanner.nextLine().trim();
			loadFile(table, filename);
		}
		
		// Display menu options 
		while (true) {
			menu();
			String choice = scanner.nextLine().trim().toLowerCase();
			
			if (choice.equals("q")) {
				break;
			}
			
			switch (choice) {
				
				// Case to add a name entry
				case "n": 
					System.out.println("Name: ");
					String name = scanner.nextLine();
					System.out.println("Address: ");
					String address = scanner.nextLine();
					if(table.insert(name,  address)) {
						System.out.println("Inserting: " + name + " -> " + address);
					} else {
						System.out.println(name + " is already in the book");
					}
					break;
			
				// Case to look up a name in address book
				case "l":
					System.out.println("Name: ");
					String lookupName = scanner.nextLine();
					String found = table.lookUp(lookupName);
					if (found == null) {
						System.out.println(lookupName + " is not in the book");
					} else {
						System.out.println("Address: " + found);
					}
					break;
				
					// Update address in address book
				case "u":
					System.out.println("Name: ");
					String updateName = scanner.nextLine();
					String oldAddress = table.lookUp(updateName);
					if (oldAddress == null) {
						System.out.println(updateName + " is not in the book");
					} else {
						System.out.println("Old Address is " + oldAddress);
						System.out.println("New Address: ");
						String newAddress = scanner.nextLine();
						table.update(updateName, newAddress);
					}
					break;
				
				// Delete an entry in address book
				case "d":
					System.out.println("Name to delete ");
					String deleteName = scanner.nextLine();
					if(!table.delete(deleteName)) {
						System.out.println(deleteName + " is not in the book");
					}
					break;
				
				// Display all entries in the address book
				case "a":
					int count = table.displayAll();
					if (count == 0) {
						System.out.println("Address book is empty: ");
					}
					break;
			
				// Save address book into a file
				case "s":
					System.out.println("Enter file name to save to: ");
					String saveFile = scanner.nextLine();
					table.save(saveFile);
					break;
				
				// Default case for invalid  choice
				default: 
					System.out.println("Invalid choice ");
			}
			System.out.println();
		}

		// Close scanner
		scanner.close();
	}
	
	// Structure for menu
	private static void menu() {
		System.out.println();
		System.out.println("Add a name (n)");
		System.out.println("Look up a name (l)");
		System.out.println("Update address (u)");
		System.out.println("Delete an entry (d)");
		System.out.println("Display all entries (a)");
		System.out.println("Save address book (s)");
		System.out.println("Quit (q)");
		System.out.print("->");
	}
	
	// Extract name and address form a file into the table
	private static void loadFile(Table table, String filename) {
		try(BufferedReader read = new BufferedReader(new FileReader(filename))) {
			String line;
			while ((line = read.readLine()) != null) {
				if (line.trim().isEmpty()) 
					continue;
				String[] parts = line.split("->");
				if (parts.length != 2) {
					System.out.println("Skipping invalid line: " + line);
					continue;
				}
				String name = parts[0].trim();
				String address = parts [1].trim();
				table.insert(name, address);
				System.out.println("Inserting: " + name.trim() + "->" +address.trim());
			}
		} catch (IOException e) {
			System.out.println("Error loading file: " + e.getMessage());
		}
	} 
} // end class
