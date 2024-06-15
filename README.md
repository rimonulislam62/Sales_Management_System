# Sales_Management_System
In the provided code, several data structures are used to manage sales records, each with specific functionalities:

1. **HashTable**: This is implemented using a vector of lists. It provides quick insertion, deletion, and search based on the record ID by hashing the ID to determine the bucket index.
    - **Purpose**: Fast average-case time complexity for insertion, deletion, and search operations.
    - **Implementation Details**: 
        - `table` is a vector of lists (`std::vector<std::list<SalesRecord>>`).
        - `hashFunction` determines the bucket index by computing `key % size`.
        - Records are stored in the appropriate list based on the hash index.
        - Methods: `insertRecord`, `deleteRecord`, `searchRecord`, `displayRecords`.

2. **LinkedList**: This is a custom singly linked list where each node contains a sales record.
    - **Purpose**: To maintain a simple dynamic list of records, allowing insertion and deletion.
    - **Implementation Details**:
        - `Node` struct contains a `SalesRecord` and a pointer to the next node.
        - `head` points to the beginning of the list.
        - Methods: `insert`, `remove`, `search`, `display`.

3. **SalesQueue**: This uses the standard library queue (`std::queue<SalesRecord>`).
    - **Purpose**: To manage records in a first-in, first-out (FIFO) order.
    - **Implementation Details**:
        - `queue` is an instance of `std::queue<SalesRecord>`.
        - Methods: `enqueue`, `dequeue`, `front`, `isEmpty`.

4. **Vector (std::vector)**: Used to store sales records in a sorted order for binary search.
    - **Purpose**: To support binary search on records.
    - **Implementation Details**:
        - `records` is a `std::vector<SalesRecord>`.
        - After insertion, the vector is kept sorted by the record ID using `std::sort`.
        - Methods: binary search using `std::lower_bound`.

**SalesManager**: This class orchestrates the use of the above data structures.
- **Purpose**: To provide a unified interface for managing sales records using different data structures.
- **Implementation Details**:
    - Contains an instance of `HashTable`, `LinkedList`, and `SalesQueue`.
    - Contains a vector of `SalesRecord`.
    - Methods: 
        - `addRecord`: Adds a record to all data structures.
        - `removeRecord`: Removes a record from all data structures.
        - `searchRecord`: Searches for a record in the hash table.
        - `binarySearchRecord`: Performs a binary search in the sorted vector.
        - `displayAllRecords`: Displays records from the hash table and linked list.
        - Queue operations: `enqueueRecord`, `dequeueRecord`, `frontQueueRecord`.

**Menu Functionality**:
- **Purpose**: Provides a console-based interface for interacting with the `SalesManager`.
- **Implementation Details**:
    - `displayMenu` function shows available operations.
    - `main` function handles user input to perform various operations using `SalesManager`.

In summary:
- **HashTable** is used for efficient record management with quick lookups.
- **LinkedList** is used for dynamic record management with straightforward insertion and deletion.
- **SalesQueue** manages records in a FIFO order.
- **Vector** provides a sorted collection of records for binary search.
