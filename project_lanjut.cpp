#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int maxx = 100;
const int maxp = 100;
//untuk layanan
string* layanan = new string[maxx] {
    "Paket 1", "Paket 2", "Paket 3", "Potong rambut", "Keramas + Pijat",
    "Creambath ", "Cat rambut"
};
string* deskripsi = new string[maxx] {
    "Potong Rambut+Keramas+pijat", "Potong rambut+Jenggot", "Potong rambut, Creambath, cat rambut dan hairstyle",
    "-", "-", "Perawatan rambut dengan mengoleskan krim khusus ke-rambut", "-"
};
int* harga = new int[maxx] {
    45000, 35000, 200000, 30000, 20000, 50000, 50000
};
int jml = 7; 

// untuk customer
string NamaPelanggan[maxp];
int IdPelanggan[maxp];
int nmrpesanan[maxp][maxx]; 
int Jumlahlayanan[maxp];
int JumlahPelanggan = 0;

// untuk login
string adminUsername = "admin";
string adminPassword = "1234";
bool mengulang;
int x;

void muatLayananDariFile() {
    ifstream file("layanan.txt");
    if (!file) {
        cout << "File layanan.txt tidak ditemukan. Menggunakan data default.\n";
        return;
    }

    jml = 0;
    while (getline(file, layanan[jml])) {
        getline(file, deskripsi[jml]);
        file >> harga[jml];
        file.ignore(); 
        jml++;
    }
    file.close();
}

// Fungsi untuk menyimpan layanan ke file
void simpanLayananKeFile() {
    ofstream file("layanan.txt");
    for (int i = 0; i < jml; i++) {
        file << layanan[i] << endl;
        file << deskripsi[i] << endl;
        file << harga[i] << endl;
    }
    file.close();
}

//1
void daftarlayanan() {
    cout << "\nDAFTAR LAYANAN\n" << endl;
    cout << string(111, '-') << endl;
    cout << "| " << left << setw(3) << "NO." << " | " << setw(20) << "Jenis Layanan" << " | " << setw(15) << "Harga" << " | " << setw(60) << "Deskripsi" << " | " << endl;
    cout << string(111, '-') << endl;
    for (int i = 0; i < jml; i++) {
        cout << "| " << left << setw(3) << i + 1 << " | " << setw(20) << layanan[i] << " | " << setw(15) << harga[i] << " | " << setw(60) << deskripsi[i] << " | " << endl;
    }
    cout << string(111, '-') << endl;
}

//FUNGSI BAGIAN ADMIN========================================================================================
void tambahlayanan() {
    if (jml <= maxx) {
        cout << "Masukkan Nama Layanan      : ";
        cin.ignore();
        getline(cin, layanan[jml]);
        cout << "Masukkan Harga Layanan     : ";
        cin >> harga[jml];
        cout << "Masukkan Deskripsi Layanan : ";
        cin.ignore();
        getline(cin, deskripsi[jml]);
        jml++;
        simpanLayananKeFile();
        cout << "Data layanan berhasil ditambahkan!\n";
    } else {
        cout << "Kapasitas datat layanan penuh!\n";
    }
}

void editlayanan() {

    int nomor ;
    daftarlayanan();
    cout << "Masukkan nomor layanan yang ingin di edit : ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jml) {
        cout << "Masukkan Layanan Yang Baru      : ";
        cin.ignore();
        getline(cin, layanan[nomor - 1]);
        cout << "Masukkan Harga Layanan Baru     : ";
        cin >> harga[nomor - 1];
        cout << "Masukkan Deskripsi Layanan Baru : ";
        cin.ignore();
        getline(cin, deskripsi[nomor - 1]);
        simpanLayananKeFile();
        cout << "Data layanan berhasil diperbarui!\n";
    } else {
        cout << "Nomor layanan tidak valid!\n";
    }
}

void hapuslayanan() {
    int nomor;
    daftarlayanan();
    cout << "Masukkan nomor layanan yang ingin dihapus: ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jml) {
        for (int i = nomor - 1; i < jml - 1; i++) {
            layanan[i] = layanan[i + 1];
            harga[i] = harga[i + 1];
            deskripsi[i] = deskripsi[i + 1];
        }
        jml--;
        simpanLayananKeFile();
        cout << "Data Layanan berhasil dihapus!\n";
    } else {
        cout << "Nomor Layanan tidak valid!\n";
    }
}
//============================================================================================================

//FUNGSI BAGIAN CUSTOMER======================================================================================
//2
void memilihmenu() {
    int Pelanggan;
    char tambahan;

    cout << "Pemesanan untuk berapa orang? ";
    cin >> Pelanggan;
    //cout << endl;
    JumlahPelanggan += Pelanggan;

    for (int x = JumlahPelanggan - Pelanggan; x < JumlahPelanggan; x++) {
        cout << "\nID Pelanggan: " << x + 1 << endl;
        IdPelanggan[x] = x + 1; 

        cout << "Nama pelanggan ke-" << x + 1 << ": ";
        cin.ignore(); 
        getline(cin, NamaPelanggan[x]); 

        daftarlayanan();
        cout << "\nMau Pesan Berapa Layanan? "; 
        cin >> Jumlahlayanan[x];

        for(int y = 0; y < Jumlahlayanan[x]; y++){
            cout << "Masukkan nomor layanan yang ingin dipesan : ";
            cin >> nmrpesanan[x][y];             // Simpan nomor layanan yang dipilih
            if (nmrpesanan[x][y] < 1 || nmrpesanan[x][y] > jml) {
                cout << "Nomor layanan tidak valid! Coba lagi.\n";
                continue;                        // Meminta input ulang
            }
        }
    }
    cout << "Pemesanan berhasil ditambahkan!\n";
}

//3
void melihatpesanan(){
if(JumlahPelanggan==0){
    cout << "Belum Ada Pesanan Yang Diinput. Silahkan Input Terlebih Dahulu!!\n";
    system("pause");
    return;
}

for(int x = 0; x < JumlahPelanggan; x++){
    cout << "\nID Pelanggan        : " << IdPelanggan[x] << endl;
    cout << "Nama Pelanggan       : " << NamaPelanggan[x] << endl;
    cout << "Layanan Yang Dipesan : \n";
    for(int y = 0; y < Jumlahlayanan[x]; y++){
        cout << "\t=>" << layanan[nmrpesanan[x][y]-1] << "\t\tHarga : " << harga[nmrpesanan[x][y]-1] << endl;
    }
}

}
//4
void checkoutpesanan() {    
    int idPelanggan;
    if (JumlahPelanggan == 0) {
        cout << "Belum ada Pesanan yang terdaftar..\n";
        system("pause");
        return;
    }

    do{
    cout << "Mau membayar untuk pelanggan ke berapa? (1-" << JumlahPelanggan << "): ";
    cin >> idPelanggan;
    mengulang=false;

    if (idPelanggan < 1 || idPelanggan > JumlahPelanggan) {
        cout << "ID Pelanggan tidak valid!\n";
        mengulang=true;
    }
    }while(mengulang==true);

    idPelanggan--; // Mengubah dari indeks 1 ke indeks 0
    int totalBayar = 0;

    cout << "\n=========== STRUK PEMBAYARAN ===========" << endl;
    cout << "               BARBER PIRRAZ \n";
    cout << "          Jl. Tambak Bayan, No. 69\n";
    cout << string(40,'=') << endl;
    cout << "Nama Pelanggan       : " << NamaPelanggan[idPelanggan] << endl;
    cout << string(40,'=') << endl;
    cout << "Layanan Yang Dipesan : \n";
    
    for (int y = 0; y < Jumlahlayanan[idPelanggan]; y++) {
        cout << "=>" << layanan[nmrpesanan[idPelanggan][y] - 1] << "\t\t\t" << harga[nmrpesanan[idPelanggan][y] - 1] << endl;
        totalBayar += harga[nmrpesanan[idPelanggan][y] - 1];
    }
    cout << string(40,'=') << endl;

    // Menanyakan apakah pelanggan adalah member
    char isMember;
    
    cout << "Apakah pelanggan adalah member? (Y/N): ";
    cin >> isMember;

    while(isMember != 'y' && isMember != 'Y' && isMember != 'n'&& isMember != 'N'){
        cout << "Input anda tidak valid, silahkan input kembali\n";
        cout << "Apakah pelanggan adalah member? (Y/N): ";
        cin >> isMember;
    }

    cout << "Total (sebelum diskon) : \t" << totalBayar << endl;
    // Menghitung diskon jika member
    if (isMember == 'Y' || isMember == 'y') {
        totalBayar *= 0.95; // Diskon 5%
        cout << "Anda mendapatkan diskon 5%\n";
    }

    cout << "Total (sesudah diskon) : \t" << totalBayar << endl;

    int uang;
    while (true){
        cout << "Masukkan nominal uang: ";
        cin >> uang;

        if (uang < totalBayar) {
            cout << "Uang tidak mencukupi, silakan masukkan uang kembali.\n";
        } else {
            cout << "Pembayaran berhasil! Kembalian: " << uang - totalBayar << endl;
            break;
        }
    }

    // Menghapus ID Pelanggan setelah pembayaran berhasil
    for (int i = idPelanggan; i < JumlahPelanggan - 1; i++) {
        IdPelanggan[i] = IdPelanggan[i + 1];
        NamaPelanggan[i] = NamaPelanggan[i + 1];
        Jumlahlayanan[i] = Jumlahlayanan[i + 1];
        for (int j = 0; j < Jumlahlayanan[i + 1]; j++) {
            nmrpesanan[i][j] = nmrpesanan[i + 1][j];
        }
    }
    JumlahPelanggan--; // Mengurangi jumlah pelanggan
    
}

void admin() {
    char kembali;
    int pilihan;
    string username, password;

    x=3;
    do{
    cout << "\n=== LOGIN ADMIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Validasi login
    if (username == adminUsername && password == adminPassword) {
        cout << "\nLogin berhasil! Selamat datang, Admin.\n";
        mengulang=false;
    } else {
        x--;mengulang=true;
        cout << "\nLogin gagal! Username atau password salah.\n";
        cout << "Anda memiliki "<<x<<" kesempatan lagi\n";
    }
    if(x==0){
        cout<<"KESEMPATAN ANDA TELAH HABIS, KELUAR DARI PROGRAM!!!!!!\n";
        exit(0);
    }
    }while(mengulang==true);


    do {
        cout << "\nMENU ADMIN\n";
        cout << "1. Lihat Daftar Layanan\n2. Tambah layanan\n3. Edit layanan\n4. Hapus layanan\n5. Kembali ke Menu Utama\n>> ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: daftarlayanan(); break;
            case 2: tambahlayanan(); break;
            case 3: editlayanan(); break;
            case 4: hapuslayanan(); break;
            case 5: return;
            default: cout << "Pilihan tidak valid!\n"; break;
        }

        do{
        cout << "Apakah mau kembali ke menu admin (y/n)? ";
        cin >> kembali;
        if(kembali=='y'||kembali=='Y'){
            mengulang=false;
        }
        else if(kembali == 'n'||kembali == 'N'){
            cout<<"Kembali ke menu utama";
            mengulang=false;
        }
        else{
            mengulang=true;
        }
        }while(mengulang==true);
    } while (kembali == 'Y' || kembali == 'y');
}

void customer() {
    char kembali;
    int pilihan;
    do {
        system("cls");
        cout << "\nMENU CUSTOMER\n";
        cout << "1. Lihat Daftar Layanan\n2. Memilih menu layanan \n3. Melihat pesanan\n4. Checkout Pesanan\n5. Kembali ke Menu Utama\n>> ";
        cin >> pilihan; 

        switch (pilihan) {
        case 1: daftarlayanan(); break;
        case 2: memilihmenu(); break;
        case 3: melihatpesanan(); break;
        case 4: checkoutpesanan(); break;
        case 5:
            return; //kembali ke menu utama
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        do{
        cout << "\nApakah mau kembali ke menu customer (Y/N)? ";
        cin >> kembali;
        if(kembali=='y'||kembali=='Y'){
            mengulang=false;
        }
        else if(kembali == 'n'||kembali == 'N'){
            cout<<"Kembali ke menu utama";
            mengulang=false;
        }
        else{
            mengulang=true;
        }
        }while(mengulang==true);
    } while (kembali == 'Y' || kembali == 'y');
}

int main() {
    muatLayananDariFile();

    int pilihan;
    do {
        cout<<"\n       MAIN MENU\n";
        cout << "PILIH LOGIN SEBAGAI APA\n";
        cout << "1. Admin\n2. Customer\n3. Exit\n>> ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            admin();
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

delete[] layanan;
delete[] deskripsi;
delete[] harga;

    return 0;
}
