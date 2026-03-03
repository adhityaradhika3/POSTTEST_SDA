#include <iostream>
using namespace std;


void reverseArray(int* arr, int n) {
    int* start = arr;
    int* end = arr + n - 1;

    while(start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}


void tampilArray(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        cout << "Nilai: " << *(arr + i)
             << " | Alamat: " << (arr + i) << endl;
    }
}

int main() {
    const int n = 7;


    int angka[n] = {2, 3, 5, 7, 11, 13, 17};

    cout << "=== ARRAY SEBELUM DIBALIK ===\n";
    tampilArray(angka, n);

    
    reverseArray(angka, n);

    cout << "\n=== ARRAY SETELAH DIBALIK ===\n";
    tampilArray(angka, n);

    return 0;
}