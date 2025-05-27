#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int maxx = 100;
const int maxp = 100;

// Struktur untuk layanan
struct Buku
{
    string buku;
    string deskripsi;
    int harga;
};

Buku jenisBuku[maxx];

int jml = 0;

// Struktur untuk pelanggan
struct Pelanggan
{
    string NamaPelanggan;
    int IdPelanggan;
    int nmrpesanan[maxx]; // Menyimpan layanan yang dipesan
    int Jumlahbuku;
};

Pelanggan pelanggan[maxp];
int JumlahPelanggan = 0;

// Struktur untuk login admin
struct Admin
{
    string username = "admin";
    string password = "1234";
};

Admin admiin;
bool mengulang;
int x;

void muatLayananDariFile() {
    ifstream file("data_buku.txt");
    if (!file) {
        cout << "File layanan.txt tidak ditemukan. Menggunakan data default.\n";
        return;
    }

    jml = 0;
    while (getline(file, jenisBuku[jml].buku)) {
        getline(file, jenisBuku[jml].deskripsi);
        file >> jenisBuku[jml].harga;
        file.ignore(); 
        jml++;
    }
    file.close();
}

void simpanLayananKeFile() {
    ofstream file("data_buku.txt");
    for (int i = 0; i < jml; i++) {
        file << jenisBuku[i].buku << endl;
        file << jenisBuku[i].deskripsi << endl;
        file << jenisBuku[i].harga << endl;
    }
    file.close();
}

void daftarbuku()
{
    string nama_File, line, buku1, desk1, harga1;
    Buku outputBuku[100];
    ifstream File("data_buku.txt");
    if (!File.is_open())
    {
        cout << "File tidak terbuka\n";
        return;
    }

    int i = 0;
    while (getline(File, line))
    {
        istringstream conv(line);
        Buku temp;
        getline(conv, buku1, ',');
        getline(conv, desk1, ',');
        getline(conv, harga1);

        temp.buku = buku1;
        temp.deskripsi = desk1;
        temp.harga = stoi(harga1);
        outputBuku[i++] = temp;
    }
    File.close();
    int pilihanbuku;
    do
    {
        cout << "\nPILIH SORTING HARGA" << endl;
        cout << "1. Termahal - Termurah" << endl;
        cout << "2. Termurah - Termahal" << endl;
        cout << "Pilih : ";
        cin >> pilihanbuku;

        if (pilihanbuku == 1)
        {
            for (int i = 0; i < jml - 1; i++)
            {
                int maks = i;
                for (int j = i + 1; j < jml; j++)
                {
                    if (outputBuku[j].harga > outputBuku[maks].harga)
                    {
                        maks = j;
                    }
                }
                swap(outputBuku[i], outputBuku[maks]);
            }
        }
        else if (pilihanbuku == 2)
        {
            for (int i = 0; i < jml - 1; i++)
            {
                int min = i;
                for (int j = i + 1; j < jml; j++)
                {
                    if (outputBuku[j].harga < outputBuku[min].harga)
                    {
                        min = j;
                    }
                }
                swap(outputBuku[i], outputBuku[min]);
            }
        }
        else
        {
            cout << "\nPilihan Tidak Valid !\n";
        }

    } while (pilihanbuku != 1 && pilihanbuku != 2);

    cout << "\nDAFTAR BUKU\n"
         << endl;
    cout << string(116, '-') << endl;
    cout << "| " << left << setw(3) << "NO." << " | " << setw(25) << "Judul buku   " << " | " << setw(15) << "Harga" << " | " << setw(60) << "Deskripsi" << " | " << endl;
    cout << string(116, '-') << endl;
    for (int i = 0; i < jml; i++)
    {
        cout << "| " << left << setw(3) << i + 1 << " | " << setw(25) << outputBuku[i].buku << " | " << setw(15) << outputBuku[i].harga << " | " << setw(60) << outputBuku[i].deskripsi << " | " << endl;
    }
    cout << string(116, '-') << endl;
}

void tambahbuku()
{
    if (jml < maxx)
    {
        cout << "Masukkan Judul Buku      : ";
        cin.ignore();
        getline(cin, jenisBuku[jml].buku);
        cout << "Masukkan Harga Buku   : ";
        cin >> jenisBuku[jml].harga;
        cout << "Masukkan Deskripsi Buku : ";
        cin.ignore();
        getline(cin, jenisBuku[jml].deskripsi);
        jml++;
        simpanLayananKeFile();
        cout << "Data Buku berhasil ditambahkan!\n";
    }
    else
    {
        cout << "Kapasitas data buku penuh!\n";
    }
}

void editbuku()
{
    string nama_File, line, buku1, desk1, harga1;
    Buku daftarBuku[100];
    int jumlahBuku = 0;

    ifstream File("data_buku.txt");
    if (!File.is_open())
    {
        cout << "File tidak terbuka\n";
        return;
    }

    while (getline(File, line))
    {
        istringstream bacabaris(line);
        getline(bacabaris, buku1, ',');
        getline(bacabaris, desk1, ',');
        getline(bacabaris, harga1);
        daftarBuku[jumlahBuku].buku = buku1;
        daftarBuku[jumlahBuku].deskripsi = desk1;
        daftarBuku[jumlahBuku].harga = stoi(harga1);
        jumlahBuku++;
    }
    File.close();

    daftarbuku();

    int nomor;

    cout << "Masukkan nomor buku yang ingin di edit : ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jml)
    {
        cout << "Masukkan Buku Yang Baru      : ";
        cin.ignore();
        getline(cin, daftarBuku[nomor - 1].buku);
        cout << "Masukkan Harga Buku Baru     : ";
        cin >> daftarBuku[nomor - 1].harga;
        cout << "Masukkan Deskripsi Buku Baru : ";
        cin.ignore();
        getline(cin, daftarBuku[nomor - 1].deskripsi);
        simpanLayananKeFile();
        cout << "Data Buku berhasil diperbarui!\n";

        ofstream File("data_buku.txt");
        if (!File.is_open()) {
            cout << "Gagal membuka file untuk menulis.\n";
            return;
        }
        for (int i = 0; i < jumlahBuku; i++) {
            File << daftarBuku[i].buku << ","
                    << daftarBuku[i].deskripsi << ","
                    << daftarBuku[i].harga << endl;
        }
        File.close();
    }
    else
    {
        cout << "Nomor buku tidak valid!\n";
    }
}

void hapusbuku()
{
    int nomor;
    daftarbuku();
    cout << "Masukkan nomor buku yang ingin dihapus: ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jml)
    {
        for (int i = nomor - 1; i < jml - 1; i++)
        {
            jenisBuku[i] = jenisBuku[i + 1];
        }
        jml--;
        simpanLayananKeFile();
        cout << "Data buku berhasil dihapus!\n";
    }
    else
    {
        cout << "Nomor buku tidak valid!\n";
    }
}
void memilihbuku()
{
    int jumlah;
    cout << "Pemesanan untuk berapa orang? ";
    cin >> jumlah;
    JumlahPelanggan += jumlah;

    for (int i = JumlahPelanggan - jumlah; i < JumlahPelanggan; i++)
    {
        cout << "\nID Pelanggan: " << i + 1 << endl;
        pelanggan[i].IdPelanggan = i + 1;

        cout << "Nama pelanggan ke-" << i + 1 << ": ";
        cin.ignore();
        getline(cin, pelanggan[i].NamaPelanggan);

        daftarbuku();
        cout << "\nMau beli berapa buku? ";
        cin >> pelanggan[i].Jumlahbuku;

        for (int j = 0; j < pelanggan[i].Jumlahbuku; j++)
        {
            cout << "Masukkan nomor buku yang ingin dipesan : ";
            cin >> pelanggan[i].nmrpesanan[j];
            if (pelanggan[i].nmrpesanan[j] < 1 || pelanggan[i].nmrpesanan[j] > jml)
            {
                cout << "Nomor buku tidak valid! Coba lagi.\n";
                j--;
            }
        }
    }
    cout << "Pemesanan berhasil ditambahkan!\n";
}

void melihatbuku()
{
    if (JumlahPelanggan == 0)
    {
        cout << "Belum Ada Pesanan Yang Diinput. Silahkan Input Terlebih Dahulu!!\n";
        return;
    }

    for (int i = 0; i < JumlahPelanggan; i++)
    {
        cout << "\nID Pelanggan        : " << pelanggan[i].IdPelanggan << endl;
        cout << "Nama Pelanggan       : " << pelanggan[i].NamaPelanggan << endl;
        cout << "Buku Yang Dipesan : \n";
        for (int j = 0; j < pelanggan[i].Jumlahbuku; j++)
        {
            cout << "\t=> " << jenisBuku[pelanggan[i].nmrpesanan[j] - 1].buku << "\tHarga : " << jenisBuku[pelanggan[i].nmrpesanan[j] - 1].harga << endl;
        }
    }
}

void caribuku()
{
    string bukuCari;
    bool ditemukan = false;

    cout << "Masukan judul buku yang dicari : ";
    getline(cin >> ws, bukuCari);

    for (int i = 0; i < 100; i++)
    {
        if (jenisBuku[i].buku == bukuCari)
        {
            cout << "Buku dengan judul " << bukuCari << " berada pada urutan ke-"
                 << i + 1 << endl;
            cout << "Harga     : " << jenisBuku[i].harga << endl;
            cout << "Deskripsi : " << jenisBuku[i].deskripsi << endl;

            ditemukan = true;
        }
    }
    if (!ditemukan)
    {
        cout << "Buku tidak ditemukan" << endl;
    }
}

void checkoutbuku()
{
    if (JumlahPelanggan == 0)
    {
        cout << "Belum ada pesanan yang terdaftar..\n";
        return;
    }

    int idPelanggan;
    cout << "Mau membayar untuk pelanggan ke berapa? (1-" << JumlahPelanggan << "): ";
    cin >> idPelanggan;
    idPelanggan--;

    int totalBayar = 0;
    cout << "\n================ STRUK PEMBAYARAN ================\n";
    cout << "Nama Pelanggan: " << pelanggan[idPelanggan].NamaPelanggan << endl;
    cout << "Buku Yang Dipesan : \n";

    for (int j = 0; j < pelanggan[idPelanggan].Jumlahbuku; j++)
    {
        cout << "=> " << jenisBuku[pelanggan[idPelanggan].nmrpesanan[j] - 1].buku << "\t" << jenisBuku[pelanggan[idPelanggan].nmrpesanan[j] - 1].harga << endl;
        totalBayar += jenisBuku[pelanggan[idPelanggan].nmrpesanan[j] - 1].harga;
    }

    char isMember;
    cout << "Apakah pelanggan adalah member? (Y/N): ";
    cin >> isMember;

    if (isMember == 'Y' || isMember == 'y')
    {
        totalBayar *= 0.95;
        cout << "Anda mendapatkan diskon 5%\n";
    }

    cout << "Total yang harus dibayar: " << totalBayar << endl;
    int uang;
    do
    {
        cout << "Masukkan nominal uang: ";
        cin >> uang;
    } while (uang < totalBayar);

    cout << "Pembayaran berhasil! Kembalian: " << uang - totalBayar << endl;
    JumlahPelanggan--;
}

void customer()
{
    char kembali;
    int pilihan;
    do
    {
        system("cls");
        cout << "\nMENU CUSTOMER\n";
        cout << "1. Lihat Daftar Buku\n2. Memilih menu buku \n3. Melihat pesanan\n4. Checkout Pesanan\n5. Mencari buku\n6. Kembali ke Menu Utama\n>> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            daftarbuku();
            break;
        case 2:
            memilihbuku();
            break;
        case 3:
            melihatbuku();
            break;
        case 4:
            checkoutbuku();
            break;
        case 5:
            caribuku();
            break;
        case 6:
            return; // kembali ke menu utama
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        do
        {
            cout << "\nApakah mau kembali ke menu customer (Y/N)? ";
            cin >> kembali;
            if (kembali == 'y' || kembali == 'Y')
            {
                mengulang = false;
            }
            else if (kembali == 'n' || kembali == 'N')
            {
                cout << "Kembali ke menu utama";
                mengulang = false;
            }
            else
            {
                mengulang = true;
            }
        } while (mengulang == true);
    } while (kembali == 'Y' || kembali == 'y');
}

void admin(Admin adminku, int kesempatan)
{
    char kembali;
    int pilihan;
    string username, password;
    // x=3;
    // do{
    // cout << "\n=== LOGIN ADMIN ===" << endl;
    // cout << "Username: ";
    // cin >> username;
    // cout << "Password: ";
    // cin >> password;

    // // Validasi login
    // if (username == username && password == password) {
    //     cout << "\nLogin berhasil! Selamat datang, Admin.\n";
    //     mengulang=false;
    // } else {
    //     x--;mengulang=true;
    //     cout << "\nLogin gagal! Username atau password salah.\n";
    //     cout << "Anda memiliki "<<x<<" kesempatan lagi\n";
    // }
    // if(x==0){
    //     cout<<"KESEMPATAN ANDA TELAH HABIS, KELUAR DARI PROGRAM!!!!!!\n";
    //     exit(0);
    // }
    // }while(mengulang==true);
    cout << "\n=== LOGIN ADMIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (kesempatan == 0)
    {
        cout << "Kesempatan anda telah habis, anda keluar dari program!!";
        exit(0);
    }

    if (username == adminku.username && password == adminku.password)
    {
        cout << "\nLogin berhasil! Selamat datang, Admin.\n";
    }
    else
    {
        cout << "\nLogin gagal! Username atau password salah.\n";
        cout << "Anda memiliki " << (kesempatan - 1) << " kesempatan lagi.\n";
        admin(adminku, kesempatan - 1); // Panggil kembali fungsi admin() dengan kesempatan berkurang
        return;
    }

    do
    {
        cout << "\nMENU ADMIN\n";
        cout << "1. Lihat Daftar Layanan\n2. Tambah layanan\n3. Edit layanan\n4. Hapus layanan\n5. Kembali ke Menu Utama\n>> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            daftarbuku();
            break;
        case 2:
            tambahbuku();
            break;
        case 3:
            editbuku();
            break;
        case 4:
            hapusbuku();
            break;
        case 5:
            return;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }

        do
        {
            cout << "Apakah mau kembali ke menu admin (y/n)? ";
            cin >> kembali;
            if (kembali == 'y' || kembali == 'Y')
            {
                mengulang = false;
            }
            else if (kembali == 'n' || kembali == 'N')
            {
                cout << "Kembali ke menu utama";
                mengulang = false;
            }
            else
            {
                mengulang = true;
            }
        } while (mengulang == true);
    } while (kembali == 'Y' || kembali == 'y');
}

int main()
{
    int pilihan;
    Admin adminku;
    do
    {
        cout << "\n       MAIN MENU\n";
        cout << "PILIH LOGIN SEBAGAI APA\n";
        cout << "1. Admin\n2. Customer\n3. Exit\n>> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            admin(adminku, 3);
            break;
        case 2:
            customer();
            break;
        case 3:
            cout << "Terima kasih sudah menggunakan layanan ini.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            system("pause");
        }
    } while (pilihan != 3);

    return 0;
}
