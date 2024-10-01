#include <iostream>
#include <string>

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

void updateItem() {
    int id;
    cout << "masukkan barang untuk di ubah: ";
    cin >> id;
    Node* current = head;
    while (current != nullptr && current->item.id != id) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Invalid ID!" << endl;
        return;
    }
    cout << "Enter new item name: ";
    cin >> current->item.name;
    cout << "Enter new item price: ";
    cin >> current->item.price;
    cout << "Enter new item stock: ";
    cin >> current->item.stock;
    cout << "Barng Berhasil DiUpdate!" << endl;
}

void deleteItem() {
    int id;
    cout << "Masukkan Barang Yang dihapus: ";
    cin >> id;
    if (head == nullptr) {
        cout << "Invalid ID!" << endl;
        return;
    }
    if (head->item.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Barang Berhasil Dihapus!" << endl;
        return;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->item.id != id) {
        current = current->next;
    }
    if (current->next == nullptr) {
        cout << "Invalid ID!" << endl;
        return;
    }
    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    cout << "Barang Berhasil Dihapus!" << endl;
}

int main() {
    int choice;
    do {
        cout << "Selamat datang di Program Kami"<< endl;
        cout << "Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. View Items" << endl;
        cout << "3. Update Item" << endl;
        cout << "4. Delete Item" << endl;
        cout << "5. Exit" << endl;
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
                cout << "keluar" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
    return 0;
}