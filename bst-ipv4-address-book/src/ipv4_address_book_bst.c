#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node structure for IPv4 address and alias
struct address_t
{
	int octet[4];
	char alias[11];
	struct address_t *leftChild, *rightChild, *parent;
	int height, depth;
};

// Pointer for BST 
struct address_t *head = NULL;

// Function Prototypes for menu-driven operation
void addAddress();
void lookUpAddress();
void updateAddress();
void deleteAddress();
void displayList();
void displayAliasesForLocation();
void displayErrorLog();

// Helper function prototypes
int isValidOctet(int oct1, int oct2, int oct3, int oct4);
int isValidAlias(const char *alias);
void lowerCaseStr(char *str);
int calcHeight(struct address_t *root);
void updateHeight(struct address_t *root);
struct address_t* insertBST(struct address_t *root, struct address_t *newNode, struct address_t *parent, int depth);
struct address_t* searchBST(struct address_t *root, const char *alias);
struct address_t* minValueNode(struct address_t *root);
struct address_t* deleteNode(struct address_t *root, const char *alias);
void inorderDisplay(struct address_t *root);
void inorderLocation(struct address_t *root, int loc1, int loc2, int *found);
int addressExists(struct address_t *root, int oct1, int oct2, int oct3, int oct4);

// Driver program
int main() {

	FILE *inputFile;
	FILE *errorLog;
	char line[100];
	char addrStr[20];
	char alias[11];
	char extra[50];  
	int choice;

	// Open address input file for reading
	inputFile = fopen ("data/address_input2.txt", "r");

	if (inputFile == NULL)
	{
		perror("Error opening address_input2.txt");
		return 1;
	}

	// Open or create error log file for writing invalid entries
	errorLog = fopen("data/input_error_log.txt", "w");

	if (errorLog == NULL)
	{
		perror("Error opening input_error_log");
		fclose(inputFile);
		return 1;
	}

	while (fgets(line, sizeof(line), inputFile) != NULL)
	{
		if (line[0] == '\n' || line [0] == '\r')
			continue;
		
		char errorlogLine[100];
		strncpy(errorlogLine, line, sizeof(errorlogLine) -1);
		errorlogLine[sizeof(errorlogLine) - 1] = '\0';
		errorlogLine[strcspn(errorlogLine, "\n")] = '\0';

		int oct1, oct2, oct3, oct4;
		int hasError = 0;

		extra[0] = '\0';
		int parsed = sscanf(line, "%s %s %49[^\n]", addrStr, alias, extra);
		
		if (parsed <2)
		{
			hasError = 1;
		}
		else if (parsed >= 3 && strlen(extra) > 0)
		{
			hasError = 1;
		}
		
		if (!hasError)
		{
			char checkStr[20];
			int matched = sscanf(addrStr, "%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);
			sprintf(checkStr, "%d.%d.%d.%d", oct1, oct2, oct3, oct4);
			if (matched != 4 || strcmp(checkStr, addrStr) !=0)
				hasError = 1;
			else if (!isValidOctet(oct1, oct2, oct3, oct4))
				hasError = 1;
		}

		if (!hasError)
		{
			if(!isValidAlias(alias))
				hasError = 1;
		}

		if (hasError)
		{
			fprintf(errorLog, "%s\n", errorlogLine);
		}
		else 
		{
			struct address_t *node = (struct address_t*) malloc(sizeof(struct address_t));
			if (node == NULL)
			{
				printf("\nNode creation failed\n");
				fclose(inputFile);
				fclose(errorLog);
				return 1;
			}

			node->octet[0]  = oct1;
			node->octet[1]  = oct2;
			node->octet[2] = oct3;
			node->octet[3] = oct4;
			strcpy(node->alias, alias);
			node->leftChild = NULL;
			node->rightChild = NULL;
			node->parent = NULL;
			node->height = 0;
			node->depth = 0;

			head = insertBST(head, node, NULL, 0);
		}
	}

	// Close file
	fclose(inputFile);
	fclose(errorLog);

	// Update heights and depths of BST for all nodes after inserts
	updateHeight(head);

	// Display menu and scan for input from user
	do
	{

		printf("\n1)Add address\n");
		printf("2)Look up address\n");
		printf("3)Update address\n");
		printf("4)Delete address\n");
		printf("5)Display List\n");
		printf("6)Display Aliases for location\n");
		printf("7)Display Error Log\n");
		printf("8)Quit\n");
		printf("Enter Option: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice)
		{
			case 1: addAddress();
				break;
			case 2: lookUpAddress();
				break;
			case 3: updateAddress();
				break;
			case 4: deleteAddress();
				break;
			case 5: displayList();
				break;
			case 6: displayAliasesForLocation();
				break;
			case 7: displayErrorLog();
				break;
			case 8: printf("Goodbye!\n");
				break;
			default: printf("Invalid Choice\n");
				break;
		}
	} while (choice !=8);

	return 0;
}

// Check if octets are valid from 0-255
int isValidOctet(int oct1, int oct2, int oct3, int oct4)
{
	return (oct1 >=0 && oct1 <=255 && oct2 >=0 && oct2 <=255 &&
		oct3 >=0 && oct3 <=255 && oct4 >=0 && oct4 <=255);
}

// Validate alias format length (1-10), unless uppercase, whitespace and non-printable characters
int isValidAlias(const char *alias)
{
	int len = strlen(alias);
	if (len < 1 || len > 10)
		return 0;
	for (int i=0; i < len; i++)
	{
		if (isupper((unsigned char)alias[i]))
			return 0;
		if (isspace((unsigned char)alias[i]))
			return 0;
		if (!isprint((unsigned char)alias[i]))
			return 0;
	}
	return 1;
}

// Convert input strings to lowercase
void lowerCaseStr(char *str)
{
	for (int i = 0; str[i]; i++)
		str[i] = (char)tolower((unsigned char) str[i]);
}

// Recursively calculate height of node
int calcHeight(struct address_t *root)
{
	if (root == NULL)
		return -1;

	int leftHeight = calcHeight(root->leftChild);
	int rightHeight = calcHeight(root->rightChild);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Traverse BST and update hight and depth of node
void updateHeight(struct address_t *root)
{
	if (root == NULL)
		return;

	if (root->parent == NULL)
		root->depth = 0;

	else 
		root->depth = root->parent->depth +1;

	root->height = calcHeight(root);

	updateHeight(root->leftChild);
	updateHeight(root->rightChild);
}

//Insert BST in-order traversal and return root of the subtree
struct address_t* insertBST(struct address_t* root, struct address_t *newNode, struct address_t *parent, int depth)
{
	if (root == NULL) 
	{
		newNode->parent = parent;
		newNode->depth = depth;
		newNode->height = 0;
		return newNode;
	}

	int cmp = strcasecmp(newNode->alias, root->alias);

	if (cmp < 0)
		root->leftChild = insertBST(root->leftChild, newNode, root, depth + 1);
	else if (cmp > 0)
		root->rightChild = insertBST(root->rightChild, newNode, root, depth + 1);
	
	root->height = calcHeight(root);
	return root;
}

// Recursively reach leftmost node 
struct address_t* minValueNode(struct address_t *root)
{
	struct address_t *cur = root;

	while (cur && cur->leftChild != NULL)
		cur = cur->leftChild;
	return cur;
}

//Delete node in BST if alias node matches and return updated tree
struct address_t* deleteNode(struct address_t *root, const char *alias)
{
	if (root == NULL) 
		return root;

	int cmp = strcasecmp(alias, root->alias);

	if (cmp < 0)
		root->leftChild = deleteNode(root->leftChild, alias);
	else if(cmp > 0)
		root->rightChild = deleteNode(root->rightChild, alias);
	else
	{
		if (root->leftChild == NULL)
		{
			struct address_t *temp = root->rightChild;
			free(root);
			return temp;
		}
		else if (root->rightChild == NULL)
		{
			struct address_t *temp = root->leftChild;
			free(root);
			return temp;
		}
		else
		{	
			struct address_t *temp = minValueNode(root->rightChild);
			root->octet[0] = temp->octet[0];
			root->octet[1] = temp->octet[1];
			root->octet[2] = temp->octet[2];
			root->octet[3] = temp->octet[3];
			strncpy(root->alias, temp->alias, sizeof(root->alias));

			root->rightChild = deleteNode(root->rightChild, temp->alias);
		}
	}
	root->height = calcHeight(root);
	return root;
}

// Search BST using alias and return the node if found
struct address_t* searchBST(struct address_t *root, const char *alias)
{
	if (root == NULL)
		return NULL;

	int cmp = strcasecmp(alias, root->alias);
	
	if (cmp == 0)
		return root;
	else if (cmp < 0)
		return searchBST(root->leftChild, alias);
	else
		return searchBST(root->rightChild, alias);
}

// Print in-order traversal, alphabetically, displaying IP address, height, depth and parent
void inorderDisplay(struct address_t *root)
{
	if (root != NULL)
	{
		inorderDisplay(root->leftChild);

		if (root->parent == NULL)
			printf("%-15s %d.%d.%d.%d height:%d depth:%d parent: NONE\n",
					root->alias, root->octet[0], root->octet[1], root->octet[2], root->octet[3], 
					root->height, root->depth);
		else
			printf("%-15s %d.%d.%d.%d height:%d depth:%d parent: %s\n",
					root->alias, root->octet[0], root->octet[1], root->octet[2], root->octet[3], 
					root->height, root->depth, root->parent->alias);

		inorderDisplay(root->rightChild);
	}
}

// Traverse BST and validate if address exists   
int addressExists(struct address_t *root, int oct1, int oct2, int oct3, int oct4)
{
	struct address_t *stack[1000];
	int top = 0;
	struct address_t *cur = root;

	while (cur != NULL || top > 0)
	{
		while (cur != NULL)
		{
			stack[top++] = cur;
			cur = cur->leftChild;
		}
		cur = stack[--top];
		if (cur->octet[0]==oct1 && cur->octet[1]==oct2 && cur->octet[2]==oct3 && cur->octet[3]==oct4)
		return 1;
		cur=cur->rightChild;
	}
	return 0;
}

// Traverse BST in-order and print alias when first two octets are matching
void inorderLocation(struct address_t *root, int loc1, int loc2, int *found)
{
	if (root != NULL)
	{
		inorderLocation(root ->leftChild, loc1, loc2, found);

		if (root->octet[0] == loc1 && root->octet[1] == loc2)
		{
			printf("%s\n", root->alias);
			*found = 1;
		}

		inorderLocation(root->rightChild, loc1, loc2, found);
	}
}

// Add address to Binary Search Tree from user input, check for duplication and structure before adding a new node
void addAddress()
{
	char alias[11];
	char addrStr[20];
	int oct1, oct2, oct3, oct4;

	printf("Enter IPv4 address: ");
		scanf("%s", addrStr);
		sscanf(addrStr, "%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);

		while (oct1 < 0 || oct1 > 255 || oct2 < 0 || oct2 > 255 ||
			oct3 < 0 || oct3 > 255 || oct4 < 0 || oct4 > 255)
		{
			printf("Error: %s is an illegal address - please reenter:\n", addrStr);
			printf("Enter IPv4 address: ");
			scanf("%s", addrStr);
			sscanf(addrStr, "%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);
		}

		if (addressExists(head, oct1, oct2, oct3, oct4)){
			printf("Error: address already exists\n");
			return;
		}

	printf("Enter alias: ");
	scanf("%s", alias);
	alias[strcspn(alias, "\n")] = 0;
	lowerCaseStr(alias);

	while (strlen(alias) > 10)
	{
		printf("Error: alias too long - please reenter: ");
		scanf("%s", alias);
		alias[strcspn(alias, "\n")] = 0;
		lowerCaseStr(alias);
	}	
		if (searchBST(head, alias) != NULL)
		{
			printf("Error: %s already exists\n", alias);
			return;
		}

		struct address_t *node = (struct address_t*)malloc(sizeof(struct address_t));
		if (node == NULL)
		{
			printf("\nNode creation failed\n");
			return;
		}

		node->octet[0] = oct1;
		node->octet[1] = oct2;
		node->octet[2] = oct3;
		node->octet[3] = oct4;
		strcpy(node->alias, alias);
		node->leftChild = NULL;
		node->rightChild = NULL;
		node->parent = NULL;
		node->height = 0;
		node->depth = 0;

		head = insertBST(head, node, NULL, 0);
		updateHeight(head);
}

// Look-up IPv4 addresses based on user input of alias when prompted
void lookUpAddress()
{
	char alias[11];
	printf("Enter alias: ");
	scanf("%s", alias);
	alias[strcspn(alias, "\n")] = 0;
	lowerCaseStr(alias);

	struct address_t *node = searchBST(head, alias);

	if (node == NULL)
		printf("Error: %s does not exist\n", alias);
	else
		printf("%s: %d.%d.%d.%d\n", node->alias, node->octet[0], node->octet[1], node->octet[2], node->octet[3]);
}

// Update IPv4 address based on user input of alias by finding node and prompt for a new octet
void updateAddress()
{
	char alias[11];
	int oct1, oct2, oct3, oct4;

	printf("Enter alias: ");
	scanf("%s", alias);
	alias[strcspn(alias, "\n")] = 0;
	lowerCaseStr(alias);

	struct address_t *node = searchBST(head, alias);

	if (node == NULL)
	{
		printf("Error:  %s does not exist\n", alias);
		return;
	}

	printf("Update address for %s: %d.%d.%d.%d\n", node->alias, node->octet[0], node->octet[1], node->octet[2],
		node->octet[3]);
	
	printf("Enter location value #1 (0-255): ");
    scanf("%d", &oct1);
    while (oct1 < 0 || oct1 > 255)
    {
		printf("Error: %d is an illegal entry - please reenter:\n", oct1);
		printf("Enter location value #1 (0-255): ");
		scanf("%d", &oct1);
    }

    printf("Enter location value #2 (0-255): ");
    scanf("%d", &oct2);
    while (oct2 < 0 || oct2> 255)
    {
        printf("Error: %d is an illegal entry - please reenter:\n", oct2);
        printf("Enter location value #2 (0-255): ");
		scanf("%d", &oct2);
    }

    printf("Enter value #3 (0-255): ");
    scanf("%d", &oct3);
    while (oct3 < 0 || oct3 > 255)
    {
        printf("Error: %d is an illegal entry - please reenter:\n", oct3);
        printf("Enter location value #3 (0-255): ");
		scanf("%d", &oct3);
    }

    printf("Enter value #4 (0-255): ");
    scanf("%d", &oct4);
    while (oct4 < 0 || oct4 > 255)
    {
        printf("Error: %d is an illegal entry - please reenter:\n", oct4);
    	printf("Enter location value #4 (0-255): ");
		scanf("%d", &oct4);
    }

	if (addressExists(head, oct1, oct2, oct3, oct4))
	{
		printf("Error: address already exists\n");
		return;
	}

	node->octet[0] = oct1;
	node->octet[1] = oct2;
	node->octet[2] = oct3;
	node->octet[3] = oct4;
}

// Delete IPv4 address according to user input for an alias
void deleteAddress() 
{
	char alias[11];
	char confirm;

	printf("Enter alias: ");
	scanf("%s", alias);
	alias[strcspn(alias, "\n")] = 0;
	lowerCaseStr(alias);

	struct address_t *node = searchBST(head, alias);

	if (node == NULL)
	{
		printf("Error: %s does not exist\n", alias);
		displayList();
		return;
	}

	printf("Delete %s %d.%d.%d.%d? (y/n) ", node->alias, node->octet[0], node->octet[1],
		node->octet[2], node->octet[3]);
		scanf(" %c", &confirm);

	if (confirm == 'y' || confirm == 'Y')
	{
		head = deleteNode(head, alias);
		if (head !=NULL)
		{
			head->parent = NULL;
			head->depth = 0;
			updateHeight(head);
		}
		printf("%s deleted\n", alias);
	}
}

// Display entries in alphabetical order
void displayList()
{
	if (head == NULL)
	{
		printf("List is empty\n");
		return;
	}
	inorderDisplay(head);
}

// Display locality, validate format and print aliases corresponding to first two octets matching
void displayAliasesForLocation()
{
	char locStr[20];
	int loc1, loc2;
	int found = 0;

	printf("Enter Locality: ");
	scanf("%s", locStr);
    
	if (sscanf(locStr, "%d.%d", &loc1, &loc2) != 2 || loc1 < 0 ||
		 loc1 > 255 || loc2 < 0 || loc2 > 255)
	{
		printf("Error: %s is an invalid locality\n", locStr);
		return;
	}

	printf("Location: %d.%d\n", loc1, loc2);
	inorderLocation(head, loc1, loc2, &found);

	if (found == 0)
		printf("Error: location %d.%d does not exist\n", loc1, loc2);
}

// Open error log and print every invalid entry from file loading
void displayErrorLog()
{
	FILE *errorLog = fopen("data/input_error_log.txt", "r");
	char string[100];

	if (errorLog == NULL)
	{
		printf("Error: Could not open input_error_log.txt");
		return;
	}

	printf("Error Log:\n\n");

	while (fgets(string, sizeof(string), errorLog) != NULL)
		printf("%s", string);
	
	fclose(errorLog);
}
