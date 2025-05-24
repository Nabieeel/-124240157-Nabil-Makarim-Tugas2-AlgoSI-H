#include <iostream>
#include <string>

using namespace std;

// Struktur data untuk node pasien
struct Pasien
{
    int noAntrian;
    string nama;
    string keluhan;
    Pasien *prev;
    Pasien *next;
};

// Pointer global untuk head dan tail
Pasien *head = nullptr;
Pasien *tail = nullptr;

// Fungsi untuk menambahkan pasien baru
void tambahPasien(int noAntrian, string nama, string keluhan)
{
    Pasien *baru = new Pasien;
    baru->noAntrian = noAntrian;
    baru->nama = nama;
    baru->keluhan = keluhan;
    baru->prev = nullptr;
    baru->next = nullptr;

    if (head == nullptr)
    {
        head = tail = baru;
        cout << "Pasien berhasil ditambahkan ke daftar.\n";
        return;
    }

    if (noAntrian < head->noAntrian)
    {
        baru->next = head;
        head->prev = baru;
        head = baru;
        cout << "Pasien berhasil ditambahkan ke daftar.\n";
        return;
    }

    if (noAntrian > tail->noAntrian)
    {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
        cout << "Pasien berhasil ditambahkan ke daftar.\n";
        return;
    }

    Pasien *current = head;
    while (current != nullptr && current->noAntrian < noAntrian)
    {
        current = current->next;
    }

    if (current != nullptr && current->noAntrian == noAntrian)
    {
        cout << "Nomor antrian sudah ada!\n";
        delete baru;
        return;
    }

    baru->prev = current->prev;
    baru->next = current;
    current->prev->next = baru;
    current->prev = baru;

    cout << "Pasien berhasil ditambahkan ke daftar.\n";
}

// Fungsi untuk menampilkan antrian dari awal
void tampilkanDariAwal()
{
    if (head == nullptr)
    {
        cout << "Antrian kosong!\n";
        return;
    }

    cout << "\nDaftar Antrian (Dari Awal)\n";
    cout << "================================================\n";

    Pasien *current = head;
    while (current != nullptr)
    {
        cout << "No Antrian: " << current->noAntrian << endl;
        cout << "Nama    : " << current->nama << endl;
        cout << "Keluhan   : " << current->keluhan << endl;
        cout << "---\n";
        current = current->next;
    }
}

// Fungsi untuk menampilkan antrian dari akhir
void tampilkanDariAkhir()
{
    if (tail == nullptr)
    {
        cout << "Antrian kosong!\n";
        return;
    }

    cout << "\nDaftar Antrian (Dari Akhir)\n";
    cout << "================================================\n";

    Pasien *current = tail;
    while (current != nullptr)
    {
        cout << "No Antrian: " << current->noAntrian << endl;
        cout << "Nama    : " << current->nama << endl;
        cout << "Keluhan   : " << current->keluhan << endl;
        cout << "---\n";
        current = current->prev;
    }
}

// Fungsi untuk mencari pasien
void cariPasien(int noAntrian)
{
    if (head == nullptr)
    {
        cout << "Antrian kosong!\n";
        return;
    }

    Pasien *current = head;
    while (current != nullptr)
    {
        if (current->noAntrian == noAntrian)
        {
            cout << "\nPasien Ditemukan:\n";
            cout << "No Antrian: " << current->noAntrian << endl;
            cout << "Nama    : " << current->nama << endl;
            cout << "Keluhan   : " << current->keluhan << endl;
            return;
        }
        current = current->next;
    }

    cout << "Pasien dengan nomor antrian " << noAntrian << " tidak ditemukan.\n";
}

// Fungsi untuk menghapus pasien
void hapusPasien(int noAntrian)
{
    if (head == nullptr)
    {
        cout << "Antrian kosong!\n";
        return;
    }

    if (head->noAntrian == noAntrian)
    {
        Pasien *temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
        cout << "Data pasien berhasil dihapus.\n";
        return;
    }

    if (tail->noAntrian == noAntrian)
    {
        Pasien *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        cout << "Data pasien berhasil dihapus.\n";
        return;
    }

    Pasien *current = head;
    while (current != nullptr && current->noAntrian != noAntrian)
    {
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Pasien dengan nomor antrian " << noAntrian << " tidak ditemukan.\n";
        return;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    cout << "Data pasien berhasil dihapus.\n";
}

// Fungsi untuk membersihkan semua data saat keluar
void hapusSemuaPasien()
{
    Pasien *current = head;
    while (current != nullptr)
    {
        Pasien *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

// Fungsi untuk menampilkan menu
void tampilkanMenu()
{
    cout << "\n=== MENU ANTRIAN PASIEN KLINIK SEHAT SELALU ===" << endl;
    cout << "1. Tambah Data Pasien" << endl;
    cout << "2. Tampilkan Antrian dari Awal" << endl;
    cout << "3. Tampilkan Antrian dari Akhir" << endl;
    cout << "4. Cari Data Pasien" << endl;
    cout << "5. Hapus Data Pasien" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main()
{
    int pilihan, noAntrian;
    string nama, keluhan;

    do
    {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan No Antrian : ";
            cin >> noAntrian;
            cin.ignore();
            cout << "Masukkan Nama Pasien: ";
            getline(cin, nama);
            cout << "Masukkan Keluhan   : ";
            getline(cin, keluhan);
            tambahPasien(noAntrian, nama, keluhan);
            break;

        case 2:
            tampilkanDariAwal();
            break;

        case 3:
            tampilkanDariAkhir();
            break;

        case 4:
            cout << "Masukkan No Antrian yang dicari: ";
            cin >> noAntrian;
            cariPasien(noAntrian);
            break;

        case 5:
            cout << "Masukkan No Antrian yang ingin dihapus: ";
            cin >> noAntrian;
            hapusPasien(noAntrian);
            break;

        case 6:
            hapusSemuaPasien();
            cout << "Terima kasih telah menggunakan program ini.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 6);

    return 0;
}
