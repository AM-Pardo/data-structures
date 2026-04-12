# **String Sorter(C)**
A C program that reads 10 user-provided strings, validates them and sorts them in ascending or decending ASCII order using a bubble sort implementation.
The project demonstrates defensive input handling, string manipulation and algorithmic reasoning in C. 

## **Features**
- Input is valided for strings:
  - Maximum length (<= 25 characters)
  - Illegal characters (+,$,%,^,(,))
  - Duplicate entries
  - Empty strings
- Implements bubble sort using strcmp for lexicographic comparison
- Supports ascending or descending order
- Identifies and prints:
  - Lowest ASCII string
  - Highest ASCII string
- Uses safe input handling with 'fgets' and buffer limits

## **How to Compile**
gcc src/string_sorter.c -o string_sorter

## **How to Run**
./string_sorter

## **Example Input**

```
Enter string 1: apple
Enter string 2: zebra
Enter string 3: hello
...
Print character string in Ascending (A) or Descending (D) order: A
```

## **Example Output**
```
Ascending Order:
apple
hello
zebra

String with lowest ascii value: apple
String with highest ascii value: zebra
```
## **Algorithmic Notes**
### **Bubble Sort**
- Time complexity:
  - Worst: O(n^2)
  - Average: O(n^2)
  - Best: O(n) (already sorted)
- Space complexity: O(1)
### **Validation Logic**
- Uses 'strcmp' for duplicate detection
- Uses 'strcspn' to safely strip newline characters
- Uses a temporary buffer ('temp[128]' to prevent overflow

### **Why This Project Matters**
- Low-level string handling
- Manual memory-safe input processing
- Algorithm implementation
- Defensive programming and robust error handling
- Clean procedural design and modular functions

These skills form a strong foundation for systems programming, embedded devleopment and performance-critical software.
