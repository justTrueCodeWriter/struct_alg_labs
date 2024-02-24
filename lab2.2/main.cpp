#include <iostream>
#include <iostream>
#include <vector>

const int TABLE_SIZE = 10;

class Node {
  public:
    std::string phone_number = "";
    std::string surname = "";

    Node(std::string phone_number, std::string surname) {
      this->phone_number = phone_number;
      this->surname = surname;
    }
};

class HashTable {
  private:
    Node* table[TABLE_SIZE];

  public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr; 
        }
    }

    int hashFunction(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += c; 
        }
        return sum % TABLE_SIZE; 
    }

    int secondHashFunction(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += c; 
        }
        return 7 - (sum % 7); 
    }

    void insert(Node* node) {
        int index = hashFunction(node->phone_number); 
        int step = secondHashFunction(node->phone_number); 

        while (table[index] != nullptr) {
            index = (index + step) % TABLE_SIZE; 
        }

        table[index] = node; 
    }

    Node* search(std::string phone_number) {
        int index = hashFunction(phone_number); 
        int step = secondHashFunction(phone_number); 

        while (table[index] != nullptr) {

            if (table[index]->phone_number == phone_number) {
                return table[index]; 
            }
            index = (index + step) % TABLE_SIZE; 
        }

        return nullptr; 
    }
};

void printFoundHash(Node* found_node) {
  if (found_node != nullptr) {
    std::cout << "Phone found: " << found_node->phone_number << ", " << found_node->surname << std::endl;
  } else {
    std::cout << "Phone not found." << std::endl;
  }
}

int main() {

    HashTable hashTable;

    hashTable.insert(new Node("372821", "Adams"));
    hashTable.insert(new Node("658827", "Grames"));
    hashTable.insert(new Node("658872", "Bones"));
    hashTable.insert(new Node("638872", "Grames"));

    printFoundHash(hashTable.search("658827"));
    printFoundHash(hashTable.search("372821"));
    printFoundHash(hashTable.search("638872"));
    printFoundHash(hashTable.search("658872"));
    printFoundHash(hashTable.search("658772"));
}
