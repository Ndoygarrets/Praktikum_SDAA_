#include <iostream>
#include <string>
#include <cmath>
using namespace std; 

struct GamingItem {
    int id;
    string name;
    float price;
    int stock;
};

struct Node {
    GamingItem item;
    Node* next;
};

Node* head = nullptr;

// Fungsi Fibonacci Search
Node* fibonacciSearch(int x) {
    if (head == nullptr) return nullptr;

    // Inisialisasi Fibonacci numbers
    int fibM2 = 0; // (m-2)'th Fibonacci No.
    int fibM1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibM1 + fibM2; // m'th Fibonacci

    // Hitung ukuran linked list
    int size = 0;
    Node* temp = head;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    int offset = -1;
    Node* current = head;

    // FibM akan digunakan untuk menentukan rentang pencarian
    while (fibM < size) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM1 + fibM2;
    }

    while (fibM > 1) {
        int i = min(offset + fibM2, size - 1);
        Node* nodeAtI = head;
        for (int j = 0; j < i; j++) nodeAtI = nodeAtI->next;

        if (nodeAtI->item.id < x) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        } else if (nodeAtI->item.id > x) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        } else {
            return nodeAtI;
        }
    }

    if (fibM1 && head->item.id == x) {
        return head;
    }

    return nullptr;
}

// Fungsi Jump Search
Node* jumpSearch(int x) {
    if (head == nullptr) return nullptr;

    int size = 0;
    Node* temp = head;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    int step = sqrt(size);
    Node* prev = nullptr;
    Node* current = head;

    while (current != nullptr && current->item.id < x) {
        prev = current;
        for (int i = 0; i < step && current->next != nullptr; i++) {
            current = current->next;
        }
    }

    // Linear search in the block
    while (prev != nullptr && prev->item.id < x) {
        prev = prev->next;
    }

    if (prev != nullptr && prev->item.id == x) {
        return prev;
    }

    return nullptr;
}

// Fungsi Boyer-Moore untuk string pencarian nama
int* buildLastTable(const string& pattern) {
    const int ALPHABET_SIZE = 256;
    int* last = new int[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        last[i] = -1;
    }
    for (int i = 0; i < pattern.size(); i++) {
        last[(int)pattern[i]] = i;
    }
    return last;
}

Node* boyerMooreSearch(const string& name) {
    if (head == nullptr) return nullptr;

    Node* current = head;
    while (current != nullptr) {
        const string& text = current->item.name;
        int n = text.size();
        int m = name.size();

        int* last = buildLastTable(name);

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && name[j] == text[s + j]) {
                j--;
            }
            if (j < 0) {
                delete[] last;
                return current;
            } else {
                s += max(1, j - last[(int)text[s + j]]);
            }
        }
        delete[] last;
        current = current->next;
    }

    return nullptr;
}

// Fungsi untuk menambah barang
void addItem() {
    Node* newNode = new Node();
    newNode->item.id = (head == nullptr) ? 1 : head->item.id + 1;
    cout << "Masukan nama Barang: ";
    cin >> newNode->item.name;
    cout << "Masukkan Harga Barang: ";
    cin >> newNode->item.price;
    cout << "Masukkan stok barang: ";
    cin >> newNode->item.stock;
    newNode->next = head;
    head = newNode;
    cout << "Barang berhasil ditambah!" << endl;
}

// Fungsi untuk menampilkan barang
void viewItems() {
    if (head == nullptr) {
        cout << "Tidak Ada Barang di Penyimpanan" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->item.id << ", Name: " << current->item.name << ", Price: " << current->item.price << ", Stock: " << current->item.stock << endl;
        current = current->next;
    }
}

// Fungsi untuk mengubah barang
void updateItem() {
    int id;
    cout << "Masukkan ID barang untuk diubah: ";
    cin >> id;
    Node* current = head;
    while (current != nullptr && current->item.id != id) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "ID tidak ditemukan!" << endl;
        return;
    }
    cout << "Masukkan nama baru: ";
    cin >> current->item.name;
    cout << "Masukkan harga baru: ";
    cin >> current->item.price;
    cout << "Masukkan stok baru: ";
    cin >> current->item.stock;
    cout << "Barang berhasil diperbarui!" << endl;
}

// Fungsi untuk menghapus barang
void deleteItem() {
    int id;
    cout << "Masukkan ID barang yang akan dihapus: ";
    cin >> id;
    if (head == nullptr) {
        cout << "ID tidak valid!" << endl;
        return;
    }
    if (head->item.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Barang berhasil dihapus!" << endl;
        return;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->item.id != id) {
        current = current->next;
    }
    if (current->next == nullptr) {
        cout << "ID tidak valid!" << endl;
        return;
    }
    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    cout << "Barang berhasil dihapus!" << endl;
}

// Fungsi untuk menampilkan hasil pencarian
void searchItem() {
    int choice;
    cout << "Pilih metode pencarian:" << endl;
    cout << "1. Fibonacci Search (ID)" << endl;
    cout << "2. Jump Search (ID)" << endl;
    cout << "3. Boyer-Moore Search (Name)" << endl;
    cin >> choice;

    if (choice == 1 || choice == 2) {
        int id;
        cout << "Masukkan ID barang: ";
        cin >> id;

        Node* result = nullptr;
        if (choice == 1) {
            result = fibonacciSearch(id);
        } else if (choice == 2) {
            result = jumpSearch(id);
        }

        if (result != nullptr) {
            cout << "Barang ditemukan: " << result->item.name << ", Harga: " << result->item.price << ", Stok: " << result->item.stock << endl;
        } else {
            cout << "Barang tidak ditemukan!" << endl;
        }
    } else if (choice == 3) {
        string name;
        cout << "Masukkan nama barang: ";
        cin >> name;

        Node* result = boyerMooreSearch(name);
        if (result != nullptr) {
            cout << "Barang ditemukan: ID: " << result->item.id << ", Harga: " << result->item.price << ", Stok: " << result->item.stock << endl;
        } else {
            cout << "Barang tidak ditemukan!" << endl;
        }
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

// Tambahkan menu untuk pencarian di main
int main() {
    int choice;
    do {
        cout << "Selamat datang di Program Kami"<< endl;
        cout << "Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. View Items" << endl;
        cout << "3. Update Item" << endl;
        cout << "4. Delete Item" << endl;
        cout << "5. Search Item" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                viewItems();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                deleteItem();
                break;
            case 5:
                searchItem();
                break;
            case 6:
                cout << "keluar" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);
    return 0;
}
