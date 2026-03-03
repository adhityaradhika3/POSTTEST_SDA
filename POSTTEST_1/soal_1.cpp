#include <iostream>
using namespace std;

/*
Analisis Kompleksitas Algoritma FindMin

Pseudocode:
1  min ← A[0]
2  for i ← 1 to n − 1 do
3      if A[i] < min then
4          min ← A[i]
5      end if
6  end for
7  return min

Tabel Analisis Cost:

Baris | Operasi                     | Cost | Frekuensi
--------------------------------------------------------
1     | min = A[0]                  | c1   | 1
2     | inisialisasi i=1            | c2   | 1
2     | pengecekan i < n            | c3   | n
3     | perbandingan A[i] < min     | c4   | n-1
4     | assignment min = A[i]       | c5   | (0 sampai n-1)
2     | increment i++               | c6   | n-1
7     | return min                  | c7   | 1

Tmin(n) (Best Case):
Terjadi jika elemen pertama sudah paling kecil.
Baris 4 tidak pernah dijalankan.

Tmin(n) = c1 + c2 + c3*n + c4*(n-1) + c6*(n-1) + c7
Tmin(n) = an + b
Big-O Best Case = O(n)

Tmax(n) (Worst Case):
Terjadi jika array dalam urutan menurun,
sehingga assignment selalu terjadi.

Tmax(n) = c1 + c2 + c3*n + c4*(n-1) + c5*(n-1) + c6*(n-1) + c7
Tmax(n) = an + b
Big-O Worst Case = O(n)

Kesimpulan:
Best Case  = O(n)
Worst Case = O(n)
Karena tetap melakukan perulangan sebanyak n-1 kali.
*/

int FindMin(int A[], int n, int &indexMin) {
    int min = A[0];
    indexMin = 0;

    for(int i = 1; i < n; i++) {
        if(A[i] < min) {
            min = A[i];
            indexMin = i;
        }
    }

    return min;
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int indexMin;

    int minimum = FindMin(A, 8, indexMin);

    cout << "Array Fibonacci: ";
    for(int i = 0; i < 8; i++) {
        cout << A[i] << " ";
    }

    cout << "\nNilai minimum : " << minimum;
    cout << "\nIndeks minimum: " << indexMin << endl;

    return 0;
}