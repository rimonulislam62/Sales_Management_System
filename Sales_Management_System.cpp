#include <bits/stdc++.h>
using namespace std;

class SalesRecord {
public:
    int id;
    std::string description;
    double amount;

    SalesRecord(int id, std::string description, double amount)
        : id(id), description(description), amount(amount) {}
};

class HashTable {
private:
    std::vector<std::list<SalesRecord>> table;
    int size;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int size) : size(size) {
        table.resize(size);
    }

    void insertRecord(SalesRecord record) {
        int index = hashFunction(record.id);
        table[index].push_back(record);
    }

    void deleteRecord(int id) {
        int index = hashFunction(id);
        auto& chain = table[index];
        chain.remove_if([id](SalesRecord& record) { return record.id == id; });
    }

    SalesRecord* searchRecord(int id) {
        int index = hashFunction(id);
        auto& chain = table[index];
        for (auto& record : chain) {
            if (record.id == id) {
                return &record;
            }
        }
        return nullptr;
    }

    void displayRecords() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (auto& record : table[i]) {
                std::cout << "[ID: " << record.id << ", Description: " << record.description << ", Amount: " << record.amount << "] ";
            }
            std::cout << std::endl;
        }
    }
};

class LinkedList {
private:
    struct Node {
        SalesRecord data;
        Node* next;
        Node(SalesRecord record) : data(record), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(SalesRecord record) {
        Node* newNode = new Node(record);
        newNode->next = head;
        head = newNode;
    }

    void remove(int id) {
        Node* current = head;
        Node* prev = nullptr;

        while (current && current->data.id != id) {
            prev = current;
            current = current->next;
        }

        if (current) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
        }
    }

    SalesRecord* search(int id) {
        Node* current = head;
        while (current) {
            if (current->data.id == id) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    void display() {
        Node* current = head;
        while (current) {
            std::cout << "[ID: " << current->data.id << ", Description: " << current->data.description << ", Amount: " << current->data.amount << "] ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

class SalesQueue {
private:
    std::queue<SalesRecord> queue;

public:
    void enqueue(SalesRecord record) {
        queue.push(record);
    }

    void dequeue() {
        if (!queue.empty()) {
            queue.pop();
        }
    }

    SalesRecord* front() {
        if (!queue.empty()) {
            return &queue.front();
        }
        return nullptr;
    }

    bool isEmpty() {
        return queue.empty();
    }
};

class SalesManager {
private:
    HashTable hashTable;
    std::vector<SalesRecord> records;
    LinkedList linkedList;
    SalesQueue salesQueue;

public:
    SalesManager(int size) : hashTable(size) {}

    bool compareSalesRecord(const SalesRecord& a, const SalesRecord& b) {
        return a.id < b.id;
    }

    void addRecord(SalesRecord record) {
        hashTable.insertRecord(record);
        records.push_back(record);
        std::sort(records.begin(), records.end(), [this](const SalesRecord& a, const SalesRecord& b) {
            return compareSalesRecord(a, b);
        });
        linkedList.insert(record);
    }

    void removeRecord(int id) {
        hashTable.deleteRecord(id);
        records.erase(std::remove_if(records.begin(), records.end(),
                                     [id](SalesRecord& record) { return record.id == id; }),
                      records.end());
        linkedList.remove(id);
    }

    SalesRecord* searchRecord(int id) {
        return hashTable.searchRecord(id);
    }

    SalesRecord* binarySearchRecord(int id) {
        auto it = std::lower_bound(records.begin(), records.end(), SalesRecord(id, "", 0.0), [this](const SalesRecord& a, const SalesRecord& b) {
            return compareSalesRecord(a, b);
        });
        if (it != records.end() && it->id == id) {
            return &(*it);
        }
        return nullptr;
    }

    void displayAllRecords() {
        std::cout << "HashTable Records:\n";
        hashTable.displayRecords();
        std::cout << "LinkedList Records:\n";
        linkedList.display();
    }

    void enqueueRecord(SalesRecord record) {
        salesQueue.enqueue(record);
    }

    void dequeueRecord() {
        salesQueue.dequeue();
    }

    SalesRecord* frontQueueRecord() {
        return salesQueue.front();
    }
};

void displayMenu() {
    std::cout << "Sales Management System\n";
    std::cout << "1. Add Sales Record\n";
    std::cout << "2. Remove Sales Record\n";
    std::cout << "3. Search Sales Record\n";
    std::cout << "4. Binary Search Sales Record\n";
    std::cout << "5. Display All Records\n";
    std::cout << "6. Enqueue Sales Record\n";
    std::cout << "7. Dequeue Sales Record\n";
    std::cout << "8. Front Queue Sales Record\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    SalesManager manager(10);
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 9) {
            break;
        }

        int id;
        std::string description;
        double amount;
        SalesRecord* record;

        switch (choice) {
            case 1:
                std::cout << "Enter ID, Description, Amount: ";
                std::cin >> id >> description >> amount;
                manager.addRecord(SalesRecord(id, description, amount));
                break;
            case 2:
                std::cout << "Enter ID to remove: ";
                std::cin >> id;
                manager.removeRecord(id);
                break;
            case 3:
                std::cout << "Enter ID to search: ";
                std::cin >> id;
                record = manager.searchRecord(id);
                if (record) {
                    std::cout << "Found: [ID: " << record->id << ", Description: " << record->description << ", Amount: " << record->amount << "]\n";
                } else {
                    std::cout << "Record not found.\n";
                }
                break;
            case 4:
                std::cout << "Enter ID for binary search: ";
                std::cin >> id;
                record = manager.binarySearchRecord(id);
                if (record) {
                    std::cout << "Found: [ID: " << record->id << ", Description: " << record->description << ", Amount: " << record->amount << "]\n";
                } else {
                    std::cout << "Record not found.\n";
                }
                break;
            case 5:
                manager.displayAllRecords();
                break;
            case 6:
                std::cout << "Enter ID, Description, Amount to enqueue: ";
                std::cin >> id >> description >> amount;
                manager.enqueueRecord(SalesRecord(id, description, amount));
                break;
            case 7:
                manager.dequeueRecord();
                break;
            case 8:
                record = manager.frontQueueRecord();
                if (record) {
                    std::cout << "Front of Queue: [ID: " << record->id << ", Description: " << record->description << ", Amount: " << record->amount << "]\n";
                } else {
                    std::cout << "Queue is empty.\n";
                }
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
