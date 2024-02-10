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
    Address* table[TABLE_SIZE]; // хеш-таблица
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr; // инициализируем все ячейки таблицы значением nullptr
        }
    }

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c; // складываем коды символов строки
        }
        return sum % TABLE_SIZE; // возвращаем остаток от деления суммы на размер таблицы
    }

    int secondHashFunction(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c; // складываем коды символов строки
        }
        return 7 - (sum % 7); // возвращаем разность 7 и остатка от деления суммы на 7
    }

    void insert(Address* address) {
        int index = hashFunction(address->zip); // вычисляем индекс для вставки адреса
        int step = secondHashFunction(address->zip); // вычисляем шаг для двойного хеширования

        while (table[index] != nullptr) {
            index = (index + step) % TABLE_SIZE; // переходим к следующей ячейке с учетом шага
        }

        table[index] = address; // вставляем адрес в таблицу
    }

    Address* search(string zip) {
        int index = hashFunction(zip); // вычисляем индекс для поиска адреса
        int step = secondHashFunction(zip); // вычисляем шаг для двойного хеширования

        while (table[index] != nullptr) {
            if (table[index]->zip == zip) {
                return table[index]; // возвращаем найденный адрес
            }
            index = (index + step) % TABLE_SIZE; // переходим к следующей ячейке с учетом шага
        }

        return nullptr; // адрес не найден
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
    Address* address3 = new Address("Street 3", "City 3", "State 3", "33333");
    Address* address4 = new Address("Street 4", "City 3", "State 3", "33333");

    hashTable.insert(address1);
    hashTable.insert(address2);
    hashTable.insert(address3);

    printFoundHash(hashTable.search("22222"));
    printFoundHash(hashTable.search("33333"));
    printFoundHash(hashTable.search("33333"));
    printFoundHash(hashTable.search("44444"));

    return 0;
}
