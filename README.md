# Hash-Table
CS202 - HW4


You are asked to implement a class named HashTable that uses a hash table with open addressing to store the items in a data collection. To simplify the implementation, we will consider only integer items where the items themselves are used as the key values.
The items should be stored in an array whose size is given as tableSize when the HashTable object is constructed. You should use the mod operation as the primary hash function:
hash(key) = key mod tableSize
The HashTable class should support insert, delete, and search operations, and should
use a separate function named f as the collision resolution strategy: hi(key) = 􏰀hash(key) + f(i)􏰁 mod tableSize
where h_i is the array index used and i = 0,1,2,... is the iteration number for finding alternative cells in the array. Your implementation should resolve the collisions using linear probing, quadratic probing, and double hashing as follows:
• Linear probing: f(i) = i
• Quadratic probing: f(i) = i^2
 • Double hashing: f (i) = i · hash 2 (key) where hash 2 (key) = reverse (key) is the secondary hash function that reverses the digits of the key (e.g., reverse(1234) = 4321).
Your implementation should be in the files named HashTable.h and HashTable.cpp. You should define the following enumeration to indicate which collision resolution strategy is used:
enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
Your implementation of the HashTable class should have the following functions:
• HashTable::HashTable( const int tableSize, const CollisionStrategy option ); Constructor that initializes the hash table with the given size. The collision resolution strategy is given as an option that will be used in the insert, delete, and search operations.
• HashTable::∼HashTable();
Destructor that cleans up any dynamic memory used.
• bool HashTable::insert( const int item );
Inserts the given item (also used as the key value) into the hash table, and returns true if insertion is successful, and false otherwise.
• bool HashTable::delete( const int item );
Deletes the given item from the hash table, and returns true if deletion is successful, and false otherwise.
• bool HashTable::search( const int item, int& numProbes );
Searches the given item in the hash table, and returns true if search is successful (i.e., the item is found), and false otherwise. This function also returns the number of probes used during the search for this item.
• void HashTable::display();
Displays the contents of the hash table in the following format:
0:
1: 39 
2:
3: 22 
4: 60 
5:
...

 (In each line, the first value indicates the array index, followed by colon, followed by the item value stored at that index (no item value is shown if the cell is empty).)
• void HashTable::analyze( int& numSuccProbes, int& numUnsuccProbes ); Analyzes the current hash table in terms of the average number of probes for successful and unsuccessful searches, and returns these two values in the variables passed by reference. For analyzing the performance for successful searches, you can use the item values currently stored in the table for searching. For analyzing the performance of unsuccessful searches, you can initiate a search that starts at each array location (index), and count the number of probes needed to reach an empty location in the array for each search.
