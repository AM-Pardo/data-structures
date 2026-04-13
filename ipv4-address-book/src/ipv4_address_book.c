#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for IPv4 address and alias
struct address_t
{
    int octet[4];
    char alias[11];
    struct address_t *next;
};

// Pointer for linked list
struct address_t *head = NULL;

// Prototypes for each user defined function
void addAddress();
void lookUpAddress();
void updateAddress();
void deleteAddress();
void displayList();
void displayAliasesForLocation();
void saveToFile();

// Main function
int main () {
    FILE *inputFile;
    char addrStr[20];
    char alias[11];
    int choice;

    // Open file to read
    inputFile = fopen ("data/address_input.txt", "r");

    if (inputFile == NULL)
    {  
	perror("Error opening address_input.txt");
	return 1;
    }

    // Create a single linkedlist based on file
    while (fscanf(inputFile, "%s %s", addrStr, alias) == 2)
    {
         struct address_t *link = (struct address_t*) malloc(sizeof(struct address_t));
	 if (link == NULL)
	 {
	     printf("\nNode creation failed\n");
	     return 1;
	 }
	 	 
	 sscanf(addrStr, "%d.%d.%d.%d", &link->octet[0], &link->octet[1], 
		&link->octet[2], &link->octet[3]);
	 strcpy(link->alias, alias);

	 link->next = head;
	 head = link;
    }
    
    // Close file
    fclose(inputFile);

    // Display menu and scan for input from user 
    do 
    {
     printf("\n1) Add address\n");
	 printf("2) Look up address\n");
	 printf("3) Update address\n");
	 printf("4) Delete address\n");
	 printf("5) Display List\n");
	 printf("6) Display Aliases for Location\n");
	 printf("7) Save to file\n");
	 printf("8) Quit\n");
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
	      case 7: saveToFile();
			break;
	      case 8: printf("Good bye!\n");
			break;
	      default: printf("Invalid Choice\n");	  
    	  }
     } while (choice != 8);
     
     return 0;
}

// Add address to linkedlist from user input, checks for duplication and structure before adding
// a new node
void addAddress() 
{ 
    char alias[11];
    char addrStr[20];
    int oct1, oct2, oct3, oct4;
    struct address_t *ptr = head;

    printf("Enter alias: ");
    scanf("%s", alias);
    alias[strcspn(alias, "\n")] = 0;
    while (strlen(alias) > 10)
    {
        printf("Error: alias too long - please reenter: ");
	scanf("%s", alias);
	alias[strcspn(alias, "\n")] = 0;
    }
 
    while (ptr != NULL)
    {
    	if (strcasecmp(ptr->alias, alias) == 0)
	{
	     printf("Error: %s already exists\n", alias);
	     return;
	}
	ptr = ptr->next;
    }

    printf("Enter address for %s: ", alias);
    scanf("%s", addrStr);
    sscanf(addrStr, "%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);
 
    while (oct1 < 0 || oct1 > 255 || oct2 < 0 || oct2 > 255 ||
		    oct3 < 0 || oct3 > 255 || oct4 < 0 || oct4 > 255) 
    {
         printf("Error: %s is an illegal address - please reenter:\n", addrStr);
	 printf("Enter address for %s: ", alias);
	 scanf("%s", addrStr);
	 sscanf(addrStr, "%d.%d.%d.%d", &oct1, &oct2, &oct3, &oct4);
    }
    ptr = head;
    while (ptr != NULL)
    {
	 if (ptr->octet[0] == oct1 && ptr->octet[1] == oct2 &&
	     ptr->octet[2] == oct3 && ptr->octet[3] == oct4)
	 {
	      printf("Error: address already exists\n");
	      return;
         }
	 ptr = ptr->next;
    }
   
    // Create new node 
    struct address_t *link = (struct address_t*) malloc(sizeof(struct address_t));
    if(NULL == link)
    {
         printf("\n Node creation failed \n");
	 return;
    }

    link->octet[0] = oct1;
    link->octet[1] = oct2;
    link->octet[2] = oct3;
    link->octet[3] = oct4;
    strcpy(link->alias, alias);
    link->next = head;
    head = link;
}

// Prompt user for an alias and display corresponding address
void lookUpAddress()
{
    char alias[11];
    struct address_t *ptr = head;

    printf("Enter alias: ");
    scanf("%s", alias);
    alias[strcspn(alias, "\n")] = 0; 

    while (ptr != NULL)
    {
         if (strcasecmp(ptr->alias, alias) == 0)
	 {
	      printf("Address for %s: %d.%d.%d.%d\n", ptr->alias, ptr->octet[0], ptr->octet[1],
	             ptr->octet[2], ptr->octet[3]);
	      return;
	 }
	 ptr = ptr->next;
    }
    printf("Error: %s does not exist\n", alias);
}

// Prompt user for alias and display address for update
void updateAddress()
{
    char alias[11];
    int oct1, oct2, oct3, oct4;
    struct address_t *ptr = head;

    printf("Enter alias: ");
    scanf("%s", alias);
    alias[strcspn(alias, "\n")] = 0;

    while (ptr != NULL)
    {
         if (strcasecmp(ptr->alias, alias) == 0)
		 break;
	 ptr = ptr->next;
    }
    if (ptr == NULL)
    {
	 printf("Error: %s does not exist\n", alias);
	 return;
    }

    printf("Update address for %s: %d.%d.%d.%d\n", ptr->alias,
         ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3]);

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
	
    struct address_t *tmp = head;
    while (tmp != NULL)
    {
         if (tmp != ptr && tmp->octet[0] == oct1 && tmp->octet[1] 
	     == oct2 && tmp->octet[2] == oct3 && tmp->octet[3] == oct4)
	 {
	     printf("Error: address already exists\n");
	     return;
	 }
	 tmp = tmp->next;
    }

    ptr->octet[0] = oct1;
    ptr->octet[1] = oct2;
    ptr->octet[2] = oct3;
    ptr->octet[3] = oct4;

}

// Prompt user for an alias to display corresponding address to delete
void deleteAddress()
{
    char alias[11];
    char confirm;
    struct address_t *ptr = head;
    struct address_t *prev = NULL;

    printf("Enter alias: ");
    scanf("%s", alias);
    alias[strcspn(alias, "\n")] = 0;

    while (ptr != NULL)
    {
         if (strcasecmp(ptr->alias, alias) == 0)
	      break;
	 prev = ptr;
	 ptr = ptr->next;
    }

    if (ptr == NULL)
    {
	 printf("Error: %s does not exist\n", alias);
	 displayList();
	 return;
    }

    printf("Delete %s %d.%d.%d.%d? (y/n) ", ptr->alias, ptr->octet[0], ptr->octet[1], 
         ptr->octet[2], ptr->octet[3]);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
	 if (prev == NULL)
		 head = ptr->next;
	 else
		 prev->next = ptr->next;
	 free(ptr);
	 ptr = NULL;
	 printf("%s deleted\n", alias);
    }

}

// Display add address and alias pairs in linked list, check if list empty
void displayList()
{
    struct address_t *ptr = head;
    int count = 0;

    if (head == NULL)
    {
	 printf("List is empty\n");
	 return;
    }
    
    while (ptr != NULL)
    {
	 printf("%d.%d.%d.%d %s\n",
	      ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3],
	      ptr->alias);
	 count++;
	 ptr = ptr->next;
    }
    printf("Total node count: %d\n", count);
}

// Prompt user for address location, check if location values are out of range
// and display error message if does not exist
void displayAliasesForLocation()
{
    int loc1, loc2;
    int found = 0;
    struct address_t *ptr = head;

    printf("Enter location value # 1 (0-255): ");
    scanf("%d", &loc1);
    while (loc1 < 0 || loc1 > 255)
    {
	 printf("Error: %d is an illegal entry - please reenter:\n", loc1);
	 printf("Enter location value #1 (0-255): ");
	 scanf("%d", &loc1);
    }

    printf("Enter location value # 2 (0-255): ");
    scanf("%d", &loc2);
    while (loc2 < 0 || loc2 > 255)
    {
         printf("Error: %d is an illegal entry - please reenter:\n ", loc2);
         printf("Enter location value #2 (0-255): ");
	 scanf("%d", &loc2);
    }

    while (ptr != NULL)
    {
         if (ptr->octet[0] == loc1 && ptr->octet[1] == loc2)
	 {
	     printf("%d.%d.%d.%d %s\n", ptr->octet[0], ptr->octet[1], ptr->octet[2],
	          ptr->octet[3], ptr->alias);
	     found = 1;
	 }
	 ptr = ptr->next;
    }
    if (found == 0)
    {
	 printf("Error: location %d.%d does not exist\n", loc1, loc2);
    }
 }

// Save linked list onto a new file 
void saveToFile()
{
    char newFile[50];
    struct address_t *ptr = head;
    FILE *outFile;

    printf("Enter file name: ");
    scanf("%s", newFile);

    outFile = fopen(newFile, "w");
    if (outFile == NULL)
    {
	 printf("Error: could not open file\n");
	 return;
    }
    
    while (ptr != NULL)
    {
	 fprintf(outFile, "%d.%d.%d.%d %s\n",
	      ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias);
	 ptr = ptr->next;
    }

    // Close file
    fclose(outFile);
    printf("File saved.\n");
}
