#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int MAX = 100;

struct Kereta {
    int    nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string jamBerangkat;
    int    hargaTiket;
};

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tampilSemua(Kereta* arr, int n) {
    if (n == 0) { cout << "\n  [!] Belum ada data kereta.\n"; return; }
    cout << "\n  ============================================================\n";
    cout << "                      JADWAL KERETA API\n";
    cout << "  ============================================================\n";
    for (int i = 0; i < n; i++) {
        Kereta* p = arr + i;
        cout << "  [" << i+1 << "] No. Kereta   : " << p->nomorKereta  << "\n";
        cout << "      Nama Kereta  : " << p->namaKereta   << "\n";
        cout << "      Rute         : " << p->asal << " -> " << p->tujuan << "\n";
        cout << "      Jam          : " << p->jamBerangkat << "\n";
        cout << "      Harga Tiket  : Rp " << p->hargaTiket << "\n";
        cout << "  ------------------------------------------------------------\n";
    }
}

void tambahKereta(Kereta* arr, int& n) {
    if (n >= MAX) { cout << "  [!] Data penuh.\n"; return; }
    Kereta* p = arr + n;
    cout << "\n  === TAMBAH DATA KERETA BARU ===\n";
    cout << "  Nomor Kereta  : "; cin >> p->nomorKereta;
    cin.ignore();
    cout << "  Nama Kereta   : "; getline(cin, p->namaKereta);
    cout << "  Asal          : "; getline(cin, p->asal);
    cout << "  Tujuan        : "; getline(cin, p->tujuan);
    cout << "  Jam Berangkat : "; getline(cin, p->jamBerangkat);
    cout << "  Harga Tiket   : Rp "; cin >> p->hargaTiket;
    n++;
    cout << "  [v] Data kereta berhasil ditambahkan!\n";
}

void linearSearch(Kereta* arr, int n,
                  const string& asal, const string& tujuan) {
    cout << "\n  === SEARCH: Rute " << asal << " -> " << tujuan << " ===\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if ((arr+i)->asal == asal && (arr+i)->tujuan == tujuan) {
            cout << "  [v] DITEMUKAN di indeks [" << i << "]:\n";
            cout << "      No. Kereta  : " << (arr+i)->nomorKereta  << "\n";
            cout << "      Nama Kereta : " << (arr+i)->namaKereta   << "\n";
            cout << "      Jam         : " << (arr+i)->jamBerangkat << "\n";
            cout << "      Harga Tiket : Rp " << (arr+i)->hargaTiket << "\n";
            cout << "  ------------------------------------------------------------\n";
            found = true;
        }
    }
    if (!found)
        cout << "  [x] Rute " << asal << " -> " << tujuan << " tidak ditemukan.\n";
}

void jumpSearch(Kereta* arr, int n, int target) {
    if (n == 0) { cout << "  [!] Tidak ada data.\n"; return; }

    cout << "\n  === SEARCH: Nomor Kereta [" << target << "] ===\n";

    Kereta temp[MAX];
    for (int i = 0; i < n; i++) temp[i] = *(arr + i);
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (temp[i].nomorKereta > temp[j].nomorKereta) {
                Kereta t = temp[i]; temp[i] = temp[j]; temp[j] = t;
            }

    cout << "  Data terurut berdasarkan No. Kereta:\n";
    for (int i = 0; i < n; i++)
        cout << "    [" << i << "] No." << temp[i].nomorKereta
             << " - " << temp[i].namaKereta << "\n";
    cout << "  Step = sqrt(" << n << ") = " << (int)sqrt((double)n) << "\n\n";

    int step = (int)sqrt((double)n);
    int prev = 0;
    int iter = 1;

    while (step <= n && temp[step - 1].nomorKereta < target) {
        cout << "  Iterasi " << iter++ << " [LOMPAT] : cek indeks ["
             << (step - 1) << "] No." << temp[step - 1].nomorKereta
             << " < " << target << "  | lompat ke indeks " << step << "\n";
        prev = step;
        step += (int)sqrt((double)n);
    }

    int batas = (step < n) ? step : n;
    for (int i = prev; i < batas; i++) {
        cout << "  Iterasi " << iter++ << " [LINEAR] : cek indeks ["
             << i << "] No." << temp[i].nomorKereta;
        if (temp[i].nomorKereta == target) {
            cout << " == " << target << "  >> KETEMU!\n";
            cout << "  ------------------------------------------------------------\n";
            cout << "  No. Kereta   : " << temp[i].nomorKereta  << "\n";
            cout << "  Nama Kereta  : " << temp[i].namaKereta   << "\n";
            cout << "  Rute         : " << temp[i].asal << " -> " << temp[i].tujuan << "\n";
            cout << "  Jam          : " << temp[i].jamBerangkat << "\n";
            cout << "  Harga Tiket  : Rp " << temp[i].hargaTiket << "\n";
            return;
        }
        cout << " != " << target << "\n";
    }
    cout << "  [x] Nomor kereta " << target << " tidak ditemukan.\n";
}

void mergeArr(Kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];
    for (int i = 0; i < n1; i++) *(L + i) = *(arr + left + i);
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + mid + 1 + j);
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((L+i)->namaKereta <= (R+j)->namaKereta)
            *(arr + k++) = *(L + i++);
        else
            *(arr + k++) = *(R + j++);
    }
    while (i < n1) *(arr + k++) = *(L + i++);
    while (j < n2) *(arr + k++) = *(R + j++);
    delete[] L;
    delete[] R;
}

void mergeSort(Kereta* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        mergeArr(arr, left, mid, right);
    }
}

void selectionSort(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if ((arr+j)->hargaTiket < (arr+minIdx)->hargaTiket)
                minIdx = j;
        if (minIdx != i)
            swapKereta(arr + i, arr + minIdx);
    }
}

void temukanTermurah(Kereta* arr, int n, Kereta*& hasil) {
    hasil = arr;
    for (int i = 1; i < n; i++)
        if ((arr+i)->hargaTiket < hasil->hargaTiket)
            hasil = arr + i;
}

int main() {
    Kereta daftar[MAX];
    int n = 0;

    daftar[n++] = {3, "Argo Bromo Anggrek", "Jakarta", "Surabaya",   "08:00", 350000};
    daftar[n++] = {1, "Bima Express",       "Jakarta", "Yogyakarta", "20:00", 250000};
    daftar[n++] = {5, "Gajayana",           "Jakarta", "Malang",     "17:00", 420000};
    daftar[n++] = {2, "Lodaya",             "Bandung", "Solo",       "09:30", 180000};
    daftar[n++] = {4, "Argo Wilis",         "Bandung", "Surabaya",   "07:00", 310000};

    int pilihan;
    do {
        cout << "\n  ============================================================\n";
        cout << "          SISTEM MANAJEMEN KEBERANGKATAN KERETA API\n";
        cout << "  ============================================================\n";
        cout << "    1. Tampil Jadwal Semua Kereta\n";
        cout << "    2. Tambah Data Kereta Baru\n";
        cout << "    3. Cari Kereta berdasarkan Rute\n";
        cout << "    4. Cari Kereta berdasarkan Nomor\n";
        cout << "    5. Urutkan Nama Kereta A-Z\n";
        cout << "    6. Urutkan Harga Tiket Termurah\n";
        cout << "    7. Tampilkan Kereta Harga Termurah\n";
        cout << "    0. Keluar\n";
        cout << "  ------------------------------------------------------------\n";
        cout << "    Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilSemua(daftar, n);
                break;

            case 2:
                tambahKereta(daftar, n);
                break;

            case 3: {
                string asal, tujuan;
                cin.ignore();
                cout << "  Kota Asal   : "; getline(cin, asal);
                cout << "  Kota Tujuan : "; getline(cin, tujuan);
                linearSearch(daftar, n, asal, tujuan);
                break;
            }

            case 4: {
                int noKereta;
                cout << "  Nomor Kereta yang dicari: "; cin >> noKereta;
                jumpSearch(daftar, n, noKereta);
                break;
            }

            case 5:
                if (n > 1) mergeSort(daftar, 0, n - 1);
                cout << "\n  [v] Data berhasil diurutkan berdasarkan Nama (A-Z)!\n";
                tampilSemua(daftar, n);
                break;

            case 6:
                if (n > 1) selectionSort(daftar, n);
                cout << "\n  [v] Data berhasil diurutkan berdasarkan Harga (termurah)!\n";
                tampilSemua(daftar, n);
                break;

            case 7: {
                if (n == 0) { cout << "  [!] Belum ada data kereta.\n"; break; }
                Kereta* hasil = 0;
                temukanTermurah(daftar, n, hasil);
                cout << "\n  === KERETA DENGAN HARGA TIKET TERMURAH ===\n";
                cout << "  No. Kereta  : " << hasil->nomorKereta  << "\n";
                cout << "  Nama Kereta : " << hasil->namaKereta   << "\n";
                cout << "  Rute        : " << hasil->asal << " -> " << hasil->tujuan << "\n";
                cout << "  Jam         : " << hasil->jamBerangkat << "\n";
                cout << "  Harga Tiket : Rp " << hasil->hargaTiket << "\n";
                break;
            }

            case 0:
                cout << "\n  Terima kasih telah menggunakan sistem ini!\n\n";
                break;

            default:
                cout << "  [!] Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}