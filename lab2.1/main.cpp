#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 10; // размер хеш-таблицы

class Address {
public:
    string street;
    string city;
    string state;
    string zip;

    Address(string street, string city, string state, string zip) {
        this->street = street;
        this->city = city;
        this->state = state;
        this->zip = zip;
    }
};

class HashTable {
private:
    Address* table[TABLE_SIZE]; 
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr; 
        }
    }

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c; 
        }
        return sum % TABLE_SIZE; 
    }

    int secondHashFunction(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c; 
        }
        return 7 - (sum % 7); 
    }

    void insert(Address* address) {
        int index = hashFunction(address->zip); 
        int step = secondHashFunction(address->zip); 

        while (table[index] != nullptr) {
            index = (index + step) % TABLE_SIZE; 
        }

        table[index] = address; 
    }

    Address* search(string zip) {
        int index = hashFunction(zip); 
        int step = secondHashFunction(zip); 

        while (table[index] != nullptr) {
            if (table[index]->zip == zip) {
                return table[index]; 
            }
            index = (index + step) % TABLE_SIZE; 
        }

        return nullptr; 
    }

};

void printFoundHash(Address* foundAddress) {
  if (foundAddress != nullptr) {
    cout << "Address found: " << foundAddress->street << ", " << foundAddress->city << ", " << foundAddress->state << ", " << foundAddress->zip << endl;
  } else {
    cout << "Address not found." << endl;
  }
}

int main() {
    HashTable hashTable;

    Address* address1 = new Address("Street 1", "City 1", "State 1", "11111");
    Address* address2 = new Address("Street 2", "City 2", "State 2", "22222");
    Address* address3 = new Address("Street 3", "City 3", "State 3", "33433");
    Address* address4 = new Address("Street 4", "City 3", "State 3", "34333");

    hashTable.insert(address1);
    hashTable.insert(address2);
    hashTable.insert(address3);
    hashTable.insert(address4);

    printFoundHash(hashTable.search("22222"));
    printFoundHash(hashTable.search("33333"));
    printFoundHash(hashTable.search("33433"));
    printFoundHash(hashTable.search("34333"));

    return 0;
}
