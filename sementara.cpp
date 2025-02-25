#include <iostream>
using namespace std;

void caribuku(){
    string bukuCari;
    bool ditemukan = false;

    cout << "Masukan judul buku yang dicari : ";
    getline(cin>> ws, bukuCari );

    for (int i = 0; i < 100; i++)
    {
        if (jenisBuku[i].buku == bukuCari ){
            cout << "Buku dengan judul " <<   bukuCari << " berada pada urutan ke-" 
            << i +1 << endl;
            cout << "Harga     : " << jenisBuku[i].harga << endl;
            cout << "Deskripsi : " << jenisBuku[i].deskripsi << endl;
        
            ditemukan = true;
        }
    }
    if(!ditemukan){
        cout << "Buku tidak ditemukan" << endl;
    }

}