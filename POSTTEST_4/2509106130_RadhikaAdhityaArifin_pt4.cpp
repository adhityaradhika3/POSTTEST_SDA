#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX     = 100;
const int MAX_Q   = 50;
const int MAX_STK = 50;

struct Kereta {
    int    nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string jamBerangkat;
    int    hargaTiket;
};

struct Pemesan {
    string namaPenumpang;
    int    nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int    hargaTiket;
};

struct NodePemesan {
    Pemesan data;
    NodePemesan* next;
};

struct Queue {
    NodePemesan* front;
    NodePemesan* rear;
    int count;

    Queue() : front(NULL), rear(NULL), count(0) {}
    bool isFull()  { return count >= MAX_Q; }
    bool isEmpty() const { return front == NULL; }
};

struct Stack {
    NodePemesan* top;
    int count;

    Stack() : top(NULL), count(0) {}
    bool isFull()  { return count >= MAX_STK; }
    bool isEmpty() const { return top == NULL; }
};

void enqueue(Queue& q, const Pemesan& p) {
    if (q.isFull()) {
        cout << "  [!] Antrian penuh!\n";
        return;
    }
    
    NodePemesan* newNode = new NodePemesan;
    newNode->data = p;
    newNode->next = NULL;

    if (q.isEmpty()) {
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
    q.count++;

    cout << "  [v] " << p.namaPenumpang
         << " berhasil masuk antrian (posisi ke-"
         << q.count << ").\n";
}

Pemesan dequeue(Queue& q, bool& berhasil) {
    Pemesan kosong;
    if (q.isEmpty()) {
        cout << "  [!] Antrian kosong!\n";
        berhasil = false;
        return kosong;
    }

    NodePemesan* temp = q.front;
    Pemesan p = temp->data;
    
    q.front = q.front->next;
    if (q.front == NULL) {
        q.rear = NULL;
    }
    
    delete temp;
    q.count--;
    berhasil = true;
    return p;
}

void peekQueue(const Queue& q) {
    if (q.isEmpty()) {
        cout << "  [!] Antrian kosong.\n";
        return;
    }
    const Pemesan* p = &(q.front->data);
    cout << "  Penumpang terdepan antrian:\n";
    cout << "    Nama        : " << p->namaPenumpang << "\n";
    cout << "    Kereta      : " << p->namaKereta    << "\n";
    cout << "    Rute        : " << p->asal << " -> " << p->tujuan << "\n";
    cout << "    Harga Tiket : Rp " << p->hargaTiket << "\n";
}

void tampilQueue(const Queue& q) {
    if (q.isEmpty()) {
        cout << "  [!] Antrian kosong.\n";
        return;
    }
    cout << "\n  ============================================================\n";
    cout << "                ANTRIAN PEMBELIAN TIKET\n";
    cout << "  ============================================================\n";
    
    int urutan = 1;
    NodePemesan* curr = q.front;
    while (curr != NULL) {
        const Pemesan* p = &(curr->data);
        cout << "  [" << urutan++ << "] Nama        : " << p->namaPenumpang << "\n";
        cout << "      Kereta      : " << p->namaKereta    << "\n";
        cout << "      Rute        : " << p->asal << " -> " << p->tujuan << "\n";
        cout << "      Harga Tiket : Rp " << p->hargaTiket << "\n";
        cout << "  ------------------------------------------------------------\n";
        curr = curr->next;
    }
    cout << "  Total antrian: " << q.count << " penumpang.\n";
}

void push(Stack& s, const Pemesan& p) {
    if (s.isFull()) {
        cout << "  [!] Riwayat penuh!\n";
        return;
    }
    
    NodePemesan* newNode = new NodePemesan;
    newNode->data = p;
    newNode->next = s.top;
    s.top = newNode;
    s.count++;

    cout << "  [v] Transaksi atas nama \"" << p.namaPenumpang
         << "\" dicatat ke riwayat.\n";
}

void pop(Stack& s) {
    if (s.isEmpty()) {
        cout << "  [!] Riwayat kosong!\n";
        return;
    }
    
    NodePemesan* temp = s.top;
    Pemesan p = temp->data;
    
    s.top = s.top->next;
    delete temp;
    s.count--;

    cout << "  [v] Transaksi atas nama \"" << p.namaPenumpang
         << "\" berhasil dibatalkan.\n";
    cout << "      Kereta  : " << p.namaKereta << "\n";
    cout << "      Rute    : " << p.asal << " -> " << p.tujuan << "\n";
    cout << "      Harga   : Rp " << p.hargaTiket << "\n";
}

void peekStack(const Stack& s) {
    if (s.isEmpty()) {
        cout << "  [!] Riwayat transaksi kosong.\n";
        return;
    }
    const Pemesan* p = &(s.top->data);
    cout << "  Transaksi terakhir di riwayat:\n";
    cout << "    Nama        : " << p->namaPenumpang << "\n";
    cout << "    Kereta      : " << p->namaKereta    << "\n";
    cout << "    Rute        : " << p->asal << " -> " << p->tujuan << "\n";
    cout << "    Harga Tiket : Rp " << p->hargaTiket << "\n";
}

void tampilStack(const Stack& s) {
    if (s.isEmpty()) {
        cout << "  [!] Riwayat transaksi kosong.\n";
        return;
    }
    cout << "\n  ============================================================\n";
    cout << "                 RIWAYAT TRANSAKSI TIKET\n";
    cout << "  ============================================================\n";
    
    int urutan = 1;
    NodePemesan* curr = s.top;
    while (curr != NULL) {
        const Pemesan* p = &(curr->data);
        cout << "  [" << urutan++ << "] Nama        : " << p->namaPenumpang << "\n";
        cout << "      Kereta      : " << p->namaKereta    << "\n";
        cout << "      Rute        : " << p->asal << " -> " << p->tujuan << "\n";
        cout << "      Harga Tiket : Rp " << p->hargaTiket << "\n";
        cout << "  ------------------------------------------------------------\n";
        curr = curr->next;
    }
    cout << "  Total riwayat: " << s.count << " transaksi.\n";
}

Kereta* cariKeretaByNomor(Kereta* arr, int n, int nomor) {
    for (int i = 0; i < n; i++)
        if ((arr+i)->nomorKereta == nomor) return arr + i;
    return 0;
}

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
    cin.clear(); cin.ignore(10000, '\n');
    cout << "  Nama Kereta   : "; getline(cin, p->namaKereta);
    cout << "  Asal          : "; getline(cin, p->asal);
    cout << "  Tujuan        : "; getline(cin, p->tujuan);
    cout << "  Jam Berangkat : "; getline(cin, p->jamBerangkat);
    cout << "  Harga Tiket   : Rp "; cin >> p->hargaTiket;
    cin.clear(); cin.ignore(10000, '\n');
    n++;
    cout << "  [v] Data kereta berhasil ditambahkan!\n";
}

void linearSearch(Kereta* arr, int n, const string& asal, const string& tujuan) {
    cout << "\n  === SEARCH: Rute " << asal << " -> " << tujuan << " ===\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        cout << "  Iterasi " << i + 1 << " [LINEAR] : cek indeks [" << i << "] rute " 
             << (arr+i)->asal << " -> " << (arr+i)->tujuan;
             
        if ((arr+i)->asal == asal && (arr+i)->tujuan == tujuan) {
            cout << " == TARGET >> COCOK!\n";
            cout << "  [v] DITEMUKAN di indeks [" << i << "]:\n";
            cout << "      No. Kereta  : " << (arr+i)->nomorKereta  << "\n";
            cout << "      Nama Kereta : " << (arr+i)->namaKereta   << "\n";
            cout << "      Jam         : " << (arr+i)->jamBerangkat << "\n";
            cout << "      Harga Tiket : Rp " << (arr+i)->hargaTiket << "\n";
            cout << "  ------------------------------------------------------------\n";
            found = true;
        } else {
            cout << " != TARGET\n";
        }
    }
    if (!found) cout << "  [x] Rute " << asal << " -> " << tujuan << " tidak ditemukan.\n";
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
        cout << "    [" << i << "] No." << temp[i].nomorKereta << " - " << temp[i].namaKereta << "\n";
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

void badCharHeuristic(string str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++) badchar[i] = -1;
    for (int i = 0; i < size; i++) badchar[(unsigned char)str[i]] = i;
}

void boyerMooreSearch(Kereta* arr, int n, string pat) {
    cout << "\n  === SEARCH : Nama Kereta \"" << pat << "\" ===\n";
    int m = pat.length();
    int badchar[256];
    badCharHeuristic(pat, m, badchar);
    bool foundAny = false;

    for (int k = 0; k < n; k++) {
        string txt = (arr + k)->namaKereta;
        int lenTxt = txt.length();
        int s = 0;

        while (s <= (lenTxt - m)) {
            int j = m - 1;
            while (j >= 0 && pat[j] == txt[s + j]) j--;

            if (j < 0) {
                cout << "  [v] DITEMUKAN PADA: " << txt << "\n";
                cout << "      No. Kereta  : " << (arr+k)->nomorKereta  << "\n";
                cout << "      Rute        : " << (arr+k)->asal << " -> " << (arr+k)->tujuan << "\n";
                cout << "      Jam         : " << (arr+k)->jamBerangkat << "\n";
                cout << "      Harga Tiket : Rp " << (arr+k)->hargaTiket << "\n";
                cout << "  ------------------------------------------------------------\n";
                foundAny = true;
                s += (s + m < lenTxt) ? m - badchar[(unsigned char)txt[s + m]] : 1;
            } else {
                s += max(1, j - badchar[(unsigned char)txt[s + j]]);
            }
        }
    }
    if (!foundAny) cout << "  [x] Nama kereta dengan kata kunci \"" << pat << "\" tidak ditemukan.\n";
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
        if ((L+i)->namaKereta <= (R+j)->namaKereta) *(arr + k++) = *(L + i++);
        else *(arr + k++) = *(R + j++);
    }
    while (i < n1) *(arr + k++) = *(L + i++);
    while (j < n2) *(arr + k++) = *(R + j++);
    delete[] L; delete[] R;
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
            if ((arr+j)->hargaTiket < (arr+minIdx)->hargaTiket) minIdx = j;
        if (minIdx != i) swapKereta(arr + i, arr + minIdx);
    }
}

int partitionQuick(Kereta* arr, int low, int high) {
    int pivot = (arr + high)->nomorKereta;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if ((arr + j)->nomorKereta < pivot) {
            i++;
            swapKereta(arr + i, arr + j);
        }
    }
    swapKereta(arr + i + 1, arr + high);
    return (i + 1);
}

void quickSort(Kereta* arr, int low, int high) {
    if (low < high) {
        int pi = partitionQuick(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void temukanTermurah(Kereta* arr, int n, Kereta*& hasil) {
    hasil = arr;
    for (int i = 1; i < n; i++)
        if ((arr+i)->hargaTiket < hasil->hargaTiket) hasil = arr + i;
}

int main() {
    Kereta daftar[MAX];
    int n = 0;

    daftar[n++] = {3, "Argo Bromo Anggrek", "Jakarta", "Surabaya",   "08:00", 350000};
    daftar[n++] = {1, "Bima Express",       "Jakarta", "Yogyakarta", "20:00", 250000};
    daftar[n++] = {5, "Gajayana",           "Jakarta", "Malang",     "17:00", 420000};
    daftar[n++] = {2, "Lodaya",             "Bandung", "Solo",       "09:30", 180000};
    daftar[n++] = {4, "Argo Wilis",         "Bandung", "Surabaya",   "07:00", 310000};

    Queue antrian;
    Stack riwayat;

    int pilihan;
    do {
        cout << "\n  ============================================================\n";
        cout << "            SISTEM MANAJEMEN KEBERANGKATAN KERETA API\n";
        cout << "  ============================================================\n";
        cout << "    1.  Tampil Jadwal Semua Kereta\n";
        cout << "    2.  Tambah Data Kereta Baru\n";
        cout << "    3.  Cari Kereta berdasarkan Rute\n";
        cout << "    4.  Cari Kereta berdasarkan Nomor\n";
        cout << "    5.  Cari Kereta berdasarkan Nama\n";
        cout << "    6.  Urutkan Nama Kereta A-Z\n";
        cout << "    7.  Urutkan Harga Tiket Termurah\n";
        cout << "    8.  Urutkan Nomor Kereta\n";
        cout << "    9.  Tampilkan Kereta Harga Termurah\n";
        cout << "            ---ANTRIAN TIKET---\n";
        cout << "    10. Pesan Tiket\n";
        cout << "    11. Proses Tiket Terdepan\n";
        cout << "    12. Tampil Semua Antrian\n";
        cout << "           ---RIWAYAT TRANSAKSI---\n";
        cout << "    13. Batalkan Transaksi Terakhir\n";
        cout << "    14. Tampil Semua Riwayat\n";
        cout << "                ---PEEK---\n";
        cout << "    15. Peek Antrian & Riwayat\n";
        cout << "    0.  Keluar\n";
        cout << "  ------------------------------------------------------------\n";
        cout << "    Pilihan: "; cin >> pilihan;
        cin.clear(); cin.ignore(10000, '\n');

        switch (pilihan) {

            case 1:
                tampilSemua(daftar, n);
                break;

            case 2:
                tambahKereta(daftar, n);
                break;

            case 3: {
                string asal, tujuan;
                cout << "  Kota Asal   : "; getline(cin, asal);
                cout << "  Kota Tujuan : "; getline(cin, tujuan);
                linearSearch(daftar, n, asal, tujuan);
                break;
            }

            case 4: {
                int noKereta;
                cout << "  Nomor Kereta yang dicari: "; cin >> noKereta;
                cin.clear(); cin.ignore(10000, '\n');
                jumpSearch(daftar, n, noKereta);
                break;
            }

            case 5: {
                string namaCari;
                cout << "  Masukkan nama kereta: "; getline(cin, namaCari);
                boyerMooreSearch(daftar, n, namaCari);
                break;
            }

            case 6:
                if (n > 1) mergeSort(daftar, 0, n - 1);
                cout << "\n  [v] Data berhasil diurutkan berdasarkan Nama (A-Z)!\n";
                tampilSemua(daftar, n);
                break;

            case 7:
                if (n > 1) selectionSort(daftar, n);
                cout << "\n  [v] Data berhasil diurutkan berdasarkan Harga (termurah)!\n";
                tampilSemua(daftar, n);
                break;

            case 8:
                if (n > 1) quickSort(daftar, 0, n - 1);
                cout << "\n  [v] Data berhasil diurutkan berdasarkan Nomor Kereta (kecil-besar)!\n";
                tampilSemua(daftar, n);
                break;

            case 9: {
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

            case 10: {
                if (n == 0) { cout << "  [!] Belum ada data kereta.\n"; break; }
                tampilSemua(daftar, n);
                Pemesan p;
                int noKereta;
                cout << "\n  === PESAN TIKET ===\n";
                cout << "  Nama Penumpang  : "; getline(cin, p.namaPenumpang);
                if (p.namaPenumpang.empty()) {
                    cout << "  [!] Nama tidak boleh kosong.\n"; break;
                }
                cout << "  Nomor Kereta    : "; cin >> noKereta;
                cin.clear(); cin.ignore(10000, '\n');
                Kereta* k = cariKeretaByNomor(daftar, n, noKereta);
                if (!k) { cout << "  [!] Nomor kereta tidak ditemukan.\n"; break; }
                p.nomorKereta = k->nomorKereta;
                p.namaKereta  = k->namaKereta;
                p.asal        = k->asal;
                p.tujuan      = k->tujuan;
                p.hargaTiket  = k->hargaTiket;
                cout << "\n  Detail Pemesanan:\n";
                cout << "    Penumpang   : " << p.namaPenumpang << "\n";
                cout << "    Kereta      : " << p.namaKereta    << "\n";
                cout << "    Rute        : " << p.asal << " -> " << p.tujuan << "\n";
                cout << "    Harga Tiket : Rp " << p.hargaTiket << "\n";
                enqueue(antrian, p);
                break;
            }

            case 11: {
                cout << "\n  === PROSES TIKET TERDEPAN ===\n";
                bool ok;
                Pemesan p = dequeue(antrian, ok);
                if (ok) {
                    cout << "  [v] Tiket diproses untuk: " << p.namaPenumpang << "\n";
                    cout << "      Kereta      : " << p.namaKereta << "\n";
                    cout << "      Rute        : " << p.asal << " -> " << p.tujuan << "\n";
                    cout << "      Harga Tiket : Rp " << p.hargaTiket << "\n";
                    cout << "\n  >> Mencatat ke riwayat transaksi...\n";
                    push(riwayat, p);
                }
                break;
            }

            case 12:
                tampilQueue(antrian);
                break;

            case 13:
                cout << "\n  === BATALKAN TRANSAKSI TERAKHIR ===\n";
                pop(riwayat);
                break;

            case 14:
                tampilStack(riwayat);
                break;

            case 15:
                cout << "\n  ============================================================\n";
                cout << "                 PEEK ANTRIAN & RIWAYAT\n";
                cout << "  ============================================================\n";
                cout << "\n  [QUEUE] "; peekQueue(antrian);
                cout << "\n  [STACK] "; peekStack(riwayat);
                break;

            case 0:
                cout << "\n  Terima kasih telah menggunakan sistem ini!\n\n";
                break;

            default:
                cout << "  [!] Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}