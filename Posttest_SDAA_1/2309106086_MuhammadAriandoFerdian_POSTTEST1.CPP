#include <iostream>
using namespace std;

// Fungsi rekursif untuk menghitung nilai pada Segitiga Pascal
int pascal(int n, int k) {
    // Basis: jika di tepi segitiga atau pada baris pertama
    if (k == 0 || k == n) {
        return 1;
    }
    return pascal(n - 1, k - 1) + pascal(n - 1, k);
}

int main() {
    int n = 3; // Jumlah tingkat segitiga (3 tingkat)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << pascal(i, j) << " ";
        }
        cout << endl;
    }
    
    return 0;
}
