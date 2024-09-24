#include <iostream>
#include <string>

using namespace std;

const int MAX_ITEMS = 100;

struct GamingItem {
    int id;
    string name;
    double price;
    int stock;
};

GamingItem inventory[MAX_ITEMS];
int itemCount = 0;

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        cout << "Penyimpanan Penuh!!!" << endl;
        return;
    }
    GamingItem *item = &inventory[itemCount];
    item->id = itemCount + 1;
    cout << "Masukan nama Barang: ";
    cin >> item->name;
    cout << "Masukkan Harga Barang: ";
    cin >> item->price;
    cout << "Masukkan stok barang: ";
    cin >> item->stock;
    itemCount++;
    cout << "Barang berhasil ditambah!" << endl;
}

void viewItems() {
    if (itemCount == 0) {
        cout << "Tidak Ada Barang di Penyimpanan" << endl;
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        GamingItem *item = &inventory[i];
        cout << "ID: " << item->id << ", Name: " << item->name << ", Price: " << item->price << ", Stock: " << item->stock << endl;
    }
}

void updateItem() {
    int id;
    cout << "masukkan barang untuk di ubah: ";
    cin >> id;
    if (id <= 0 || id > itemCount) {
        cout << "Invalid ID!" << endl;
        return;
    }
    GamingItem *item = &inventory[id - 1];
    cout << "Enter new item name: ";
    cin >> item->name;
    cout << "Enter new item price: ";
    cin >> item->price;
    cout << "Enter new item stock: ";
    cin >> item->stock;
    cout << "Barng Berhasil DiUpdate!" << endl;
}

void deleteItem() {
    int id;
    cout << "Masukkan Barang Yang dihapus: ";
    cin >> id;
    if (id <= 0 || id > itemCount) {
        cout << "Invalid ID!" << endl;
        return;
    }
    for (int i = id - 1; i < itemCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    itemCount--;
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
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
    return 0;
}