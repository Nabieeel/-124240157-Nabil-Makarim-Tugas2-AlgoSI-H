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

// Kelas untuk mengelola antrian pasien
class AntrianPasien
{
private:
    Pasien *head;
    Pasien *tail;

public:
    // Constructor
    AntrianPasien()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Destructor
    ~AntrianPasien()
    {
        Pasien *current = head;
        while (current != nullptr)
        {
            Pasien *temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Method untuk menambahkan pasien baru
    void tambahPasien(int noAntrian, string nama, string keluhan)
    {
        Pasien *baru = new Pasien;
        baru->noAntrian = noAntrian;
        baru->nama = nama;
        baru->keluhan = keluhan;
        baru->prev = nullptr;
        baru->next = nullptr;

        // Jika linked list kosong
        if (head == nullptr)
        {
            head = baru;
            tail = baru;
            cout << "Pasien berhasil ditambahkan ke daftar.\n";
            return;
        }

        // Jika nomor antrian lebih kecil dari head
        if (noAntrian < head->noAntrian)
        {
            baru->next = head;
            head->prev = baru;
            head = baru;
            cout << "Pasien berhasil ditambahkan ke daftar.\n";
            return;
        }

        // Jika nomor antrian lebih besar dari tail
        if (noAntrian > tail->noAntrian)
        {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
            cout << "Pasien berhasil ditambahkan ke daftar.\n";
            return;
        }

        // Cari posisi yang tepat untuk menyisipkan
        Pasien *current = head;
        while (current != nullptr && current->noAntrian < noAntrian)
        {
            current = current->next;
        }

        // Jika nomor antrian sudah ada
        if (current != nullptr && current->noAntrian == noAntrian)
        {
            cout << "Nomor antrian sudah ada!\n";
            delete baru;
            return;
        }

        // Sisipkan node baru sebelum current
        baru->prev = current->prev;
        baru->next = current;
        current->prev->next = baru;
        current->prev = baru;

        cout << "Pasien berhasil ditambahkan ke daftar.\n";
    }

    // Method untuk menampilkan antrian dari awal
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

    // Method untuk menampilkan antrian dari akhir
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

    // Method untuk mencari pasien berdasarkan nomor antrian
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

    // Method untuk menghapus pasien berdasarkan nomor antrian
    void hapusPasien(int noAntrian)
    {
        if (head == nullptr)
        {
            cout << "Antrian kosong!\n";
            return;
        }

        // Jika node yang akan dihapus adalah head
        if (head->noAntrian == noAntrian)
        {
            Pasien *temp = head;
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr; // List menjadi kosong
            }
            delete temp;
            cout << "Data pasien berhasil dihapus.\n";
            return;
        }

        // Jika node yang akan dihapus adalah tail
        if (tail->noAntrian == noAntrian)
        {
            Pasien *temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            cout << "Data pasien berhasil dihapus.\n";
            return;
        }

        // Cari node yang akan dihapus
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

        // Hapus node yang berada di tengah
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        cout << "Data pasien berhasil dihapus.\n";
    }
};

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
    AntrianPasien antrian;
    int pilihan, noAntrian;
    string nama, keluhan;

    do
    {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer

        switch (pilihan)
        {
        case 1: // Tambah Data Pasien
            cout << "Masukkan No Antrian : ";
            cin >> noAntrian;
            cin.ignore();
            cout << "Masukkan Nama Pasien: ";
            getline(cin, nama);
            cout << "Masukkan Keluhan   : ";
            getline(cin, keluhan);
            antrian.tambahPasien(noAntrian, nama, keluhan);
            break;

        case 2: // Tampilkan Antrian dari Awal
            antrian.tampilkanDariAwal();
            break;

        case 3: // Tampilkan Antrian dari Akhir
            antrian.tampilkanDariAkhir();
            break;

        case 4: // Cari Data Pasien
            cout << "Masukkan No Antrian yang dicari: ";
            cin >> noAntrian;
            antrian.cariPasien(noAntrian);
            break;

        case 5: // Hapus Data Pasien
            cout << "Masukkan No Antrian yang ingin dihapus: ";
            cin >> noAntrian;
            antrian.hapusPasien(noAntrian);
            break;

        case 6: // Keluar
            cout << "Terima kasih telah menggunakan program ini.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 6);

    return 0;
}