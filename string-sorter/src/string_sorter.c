#include<stdio.h>
#include<string.h>

char arr[10][26];

int illegal_char(char str[]);
int is_duplicate(char str[], int count);
void bubble_sort(int n, char choice);
int check_sort(char choice);

/* 
 *Checks the array for illegal characters: +, $, %, ^, (, )
 */
int illegal_char(char str[])
{
   int i;
   for (i=0; str[i] != '\0'; i++)
   {
       if (str[i] == '+' || str[i] == '$' || str[i] == '%' || str[i] == '^'|| str[i] == '(' || str[i] == ')')
           return 1;
   }
   return 0;
}

/*
 *Checks the array for duplicate characters using strcmp
 */
int is_duplicate(char str[], int c) 
{
   int i;
   for (i=0;i<c; i++) 
   {
	if (strcmp(arr[i], str) == 0)	
   	return 1;
   } 
   return 0;
}

/*
 *Sorts array based on input from user 'A' or 'D' ascending and descending respectfully
 */
void bubble_sort(int n, char choice)
{
    int c, d;
    char t[26];

    for (c=0;c<(n-1);c++)
    {
        for (d=0;d<n-c-1;d++)
        {
           if (choice == 'A')
           {
               if (strcmp(arr[d], arr[d+1]) > 0) 
               {
                  strcpy(t, arr[d]);
	          strcpy(arr[d], arr[d+1]);
	          strcpy(arr[d+1], t);
               }
           }
           else if (choice == 'D') 
           {
	       if (strcmp(arr[d], arr[d+1]) < 0) 
	       {
                  strcpy(t, arr[d]);
                  strcpy(arr[d], arr[d+1]);
                  strcpy(arr[d+1], t);
    	 
   	       }   
           }
        }
    }
} 

/*Checks if user input of 'A' or 'D' is valid and prints the corresponding labels for the lists
 */
int check_sort(char choice){
   if  (choice == 'A'){
      printf("\nAscending Order: \n");
      return 1;
   }else if (choice == 'D'){
      printf("\nDescending Order: \n");
      return 1;
   }
   return 0;
}

/*
 *Main function, reads in 10 strings, utilizes temp number 128 for functions to validate input, sort and print arrays in ascending or descending order
 */
 int main()
{ 
   
   char temp[128], choice;
   int c = 0, i;

   printf("Enter 10 character strings:\n");
   
   while (c<10)
   {
      printf("Enter string %d: ", c + 1);		   
      fgets(temp, sizeof(temp), stdin);
      
      temp[strcspn(temp, "\n")] = '\0';
      
      if (strlen(temp) == 0) 
      {  

	  printf("Error: Empty String - Please Re-Enter \n");    
     
      }else if (strlen(temp) > 25)
      {
	  printf("Error: Overflow - Please Re-Enter \n");

      }
      else if (illegal_char(temp))
      {
	  printf("Error: Illegal Character - Please Re-Enter \n");
      }else if (is_duplicate(temp,c))
      {
	  printf("Error: Duplicate String - Please Re-Enter \n"); 
      }
      else
      {
	  strcpy(arr[c], temp);
          c++;
      }
   }

   int valid=0;
   while (!valid)
   {
       printf("Print character string in Ascending (A) or Descending (D) order:");
       scanf(" %c", &choice);
       valid = check_sort(choice);

       if (!valid)
          printf("Error: Enter 'A' or 'D'\n");
   }

  bubble_sort(10, choice);

  for (i=0; i<10; i++)
  {
      printf("%s\n", arr[i]);
  }
  if (choice == 'A')
  {
     printf("String with lowest ascii value: %s \n", arr[0]);
     printf("String with highest ascii value: %s \n", arr[9]);
  }else
  {  printf("String with lowest ascii value: %s \n", arr[9]);
     printf("String with highest ascii value: %s \n", arr[0]);
  }

  return 0;
}                                    
