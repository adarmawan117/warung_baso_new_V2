#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <io.h>

#define MAX 100

int main();
void menu_user();
void menu_admin();

COORD coord = {0,0};
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clrscr() {
    system("cls");
}

typedef struct {
    char id[MAX];
    char nama[MAX];
    long int harga;
} Data_Makanan;

typedef struct {
    char id[MAX];
    char nama[MAX];
    long int harga;
} Data_Minuman;

typedef struct {
    char nama[MAX];
    long long int jumlah_belanja;
} Data_Pelanggan;

Data_Makanan data_makanan;
Data_Minuman data_minuman;
Data_Pelanggan data_pelanggan;

FILE *f_makanan, *f_minuman;

void buka_makanan() {
    if((f_makanan = fopen("File_Makanan.txt","a+")) == NULL){
        clrscr();
        printf("Data Makanan Tidak Bisa Dibuka Euy...\n");
        exit(1);
    }
}

void baca_makanan() {
    if((f_makanan = fopen("File_Makanan.txt","r+")) == NULL){
        clrscr();
        printf("Data Makanan Tidak Ada Euy....\n");
        exit(1);
    }
}

void buka_minuman() {
    if((f_minuman = fopen("File_Minuman.txt","a+")) == NULL){
        clrscr();
        printf("Data Makanan Tidak Bisa Dibuka Euy...\n");
        exit(1);
    }
}

void baca_minuman() {
    if((f_minuman = fopen("File_Minuman.txt","r+")) == NULL){
        clrscr();
        printf("Data Makanan Tidak Ada Euy....\n");
        exit(1);
    }
}

void input_makanan_manual(){
    buka_makanan();
    strcpy(data_makanan.id,   "MN-0001");
    strcpy(data_makanan.nama, "Es Campur");
    data_makanan.harga        = 7000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MN-0002");
    strcpy(data_makanan.nama,  "Es Teh Manis");
    data_makanan.harga         = 3500;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MN-0003");
    strcpy(data_makanan.nama,  "Es Jeruk");
    data_makanan.harga         = 4000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MN-0004");
    strcpy(data_makanan.nama,  "Es Teh botol");
    data_makanan.harga         = 4000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MN-0005");
    strcpy(data_makanan.nama,  "Es Teh Gelas");
    data_makanan.harga         = 1500;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MN-0006");
    strcpy(data_makanan.nama,  "Es Fruit Tea");
    data_makanan.harga         = 4000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    fclose(f_makanan);
}

void input_minuman_manual() {

    buka_minuman();

    strcpy(data_minuman.id,    "MN-0001");
    strcpy(data_minuman.nama,  "Es Campur");
    data_minuman.harga         = 7000;
    fwrite(&data_minuman, sizeof(data_minuman), 1, f_minuman);

    strcpy(data_minuman.id,    "MN-0002");
    strcpy(data_minuman.nama,  "Es Teh Manis");
    data_minuman.harga         = 3500;
    fwrite(&data_minuman, sizeof(data_minuman), 1, f_minuman);

    strcpy(data_minuman.id,    "MN-0003");
    strcpy(data_minuman.nama,  "Es Jeruk");
    data_minuman.harga         = 4000;
    fwrite(&data_minuman, sizeof(data_minuman), 1, f_minuman);

    strcpy(data_minuman.id,    "MN-0004");
    strcpy(data_minuman.nama,  "Es Teh Botol");
    data_minuman.harga         = 4000;
    fwrite(&data_minuman, sizeof(data_minuman), 1, f_minuman);

    strcpy(data_minuman.id,    "MN-0005");
    strcpy(data_minuman.nama,  "Es Teh Gelas");
    data_minuman.harga         = 1500;
    fwrite(&data_minuman, sizeof(data_minuman), 1, f_minuman);

    strcpy(data_minuman.id,    "MN-0006");
    strcpy(data_minuman.nama,  "Es Fruit Tea");
    data_minuman.harga         = 4000;
    fwrite(&data_minuman, sizeof(data_minuman), 1, f_minuman);

    fclose(f_minuman);
}

void tampil_makanan() {
    int i = 0, file_handle, ukuran_file;

    //baca_makanan();
    buka_makanan();
    file_handle = fileno(f_makanan);
    if((ukuran_file = filelength(file_handle)) == -1L){
        printf("Tidak dapat memperoleh ukuran file :(\n");
        Sleep(1000);
        fclose(f_makanan);
        exit(1);
    } else {
        if(ukuran_file == 0)
            input_makanan_manual();

        printf("||==============||======================||==============================||==============||\n");
        printf("||\tNo\t||\tKode Makanan\t||\tNama Makanan\t\t||\tHarga\t||\n");
        printf("||==============||======================||==============================||==============||\n");

        while(fread(&data_makanan, sizeof(data_makanan), 1, f_makanan))
            printf("||\t%i.\t||\t%s\t\t||\t%s\t\t||\t%li\t||\n",++i, data_makanan.id, data_makanan.nama, data_makanan.harga);
        printf("==========================================================================================\n");
    }
    fclose(f_makanan);

    /*
    if(strcmp(data_makanan[0].id, "") == 0)
        input_makanan_manual();

    printf("===================================\n"
           "DATA MAKANAN\n"
           "===================================\n");
    while(strcmp(data_makanan[i].id, "") != 0){
        printf("Data Makanan %d:\n", i+1);
        printf("ID\t: %s\n",        data_makanan[i].id);
        printf("Nama\t: %s\n",      data_makanan[i].nama);
        printf("Harga\t: %d\n\n\n", data_makanan[i].harga);

        i++;
    }
     */
}

void tampil_minuman() {
    int i = 0, file_handle, ukuran_file;

    //baca_minuman();
    buka_minuman();
    file_handle = fileno(f_minuman);
    if((ukuran_file = filelength(file_handle)) == -1L){
        printf("Tidak dapat memperoleh ukuran file :(\n");
        Sleep(1000);
        fclose(f_minuman);
        exit(1);
    } else {
        if(ukuran_file == 0)
            input_minuman_manual();

        printf("\n\n"
               "||==============||======================||==============================||==============||\n");
        printf("||\tNo\t||\tKode Minuman\t||\tNama Makanan\t\t||\tHarga\t||\n");
        printf("||==============||======================||==============================||==============||\n");

        while(fread(&data_minuman, sizeof(data_minuman), 1, f_minuman))
            printf("||\t%i.\t||\t%s\t\t||\t%s\t\t||\t%li\t||\n",++i, data_minuman.id, data_minuman.nama, data_minuman.harga);
        printf("==========================================================================================\n");
    }
    fclose(f_minuman);


    /*
    int i = 0;

    if(strcmp(data_minuman[0].id, "") == 0)
        input_minuman_manual();

    printf("===================================\n"
           "DATA MINUMAN\n"
           "===================================\n");
    while(strcmp(data_minuman[i].id, "") != 0){
        printf("Data Minuman %d:\n", i+1);
        printf("ID\t: %s\n",        data_minuman[i].id);
        printf("Nama\t: %s\n",      data_minuman[i].nama);
        printf("Harga\t: %d\n\n\n", data_minuman[i].harga);

        i++;
    }
     */
}

// menu 1
void tampil_menu() {

    char pilih_menu;
    do {
        clrscr();
        fflush(stdin);
        printf("=========================\n"
               "TAMPIL MENU WARUNG\n"
               "=========================\n"
               "1. Menu Makanan\n"
               "2. Menu Minuman\n"
               "3. Kembali ke menu utama\n"
        );
        pilih_menu = (char) getchar();
        switch (pilih_menu) {
            case '1':
                tampil_makanan();
                break;

            case '2':
                tampil_minuman();
                break;

            case '3':
              goto beres;

            default:
                printf("Pilih hanya menu 1, 2 atau 3!\n");
                _getch();
        }
        beres:
        printf("");
    } while ((pilih_menu < '1') || (pilih_menu > '3'));
}

void menu_user() {

    char pilih_menu;

    do
    {
        fflush(stdin);
        clrscr();
        printf("===================\n"
               "MENU USER\n"
               "===================\n"
               "1. Tampilkan Menu Warung\n"
               "2. Pesan\n"
               "3. Tentang Toko\n"
               "4. Kembali Ke Menu Utama\n"
               "5. Keluar\n"
               "===================\n"
               "Pilihan Anda : "
        );
        pilih_menu = (char) getchar();

        switch (pilih_menu)
        {
            case '1':
                tampil_menu();
                break;

            case '2':

                break;

            case '3':

                break;

            case '4':
                goto ke_menu_utama;

            case '5':
                exit(0);

            default: {
                printf("Pilih hanya dari 1-4\n");
            }
        }

        printf("Tekan sembarang untuk kembali ke MENU USER");
        getch();

    } while(pilih_menu != '4');
    ke_menu_utama:
    printf("");
}

/*
"2. Data Pemesanan\n"
"3. Tampil Data Pelanggan\n"
"4. Cari Data\n"
"5. Edit Data\n"
 */

/*
 * Menu admin => Data Pelanggan
 *
 */
FILE *f_pelanggan;
void buka_pelanggan() {
    if((f_pelanggan = fopen("File_Data_Pelanggan.txt","a+")) == NULL){
        clrscr();
        printf("Data Pelanggan Tidak Bisa Dibuka Euy...\n");
        exit(1);
    }
}

//1. Tampil Data Pelanggan
void MAP_tampil_pelanggan() {
    int i = 0, file_handle, ukuran_file;

    printf("===============================\n"
           "MENU TAMPIL DATA PELANGGAN\n"
           "===============================\n\n"
           );
    buka_pelanggan();
    file_handle = fileno(f_pelanggan);
    if((ukuran_file = filelength(file_handle)) == -1L){
        printf("Tidak dapat memperoleh ukuran file :(\n");
        Sleep(1000);
        fclose(f_pelanggan);
        exit(1);
    } else {
        if(ukuran_file == 0)
            printf("Data Pelanggan Kosong!\n");
        else {
            printf("||==============||======================||==============================||\n");
            printf("||\tNo\t||\tNama Pelanggan\t||\tTotal Belanja\t\t||\n");
            printf("||==============||======================||==============================||\n");

            while (fread(&data_pelanggan, sizeof(data_pelanggan), 1, f_pelanggan))
                printf("||\t%i.\t||\t%s\t\t||\t%lli\t\t||\n", ++i, data_pelanggan.nama, data_pelanggan.jumlah_belanja);
            printf("==========================================================================================\n");
        }
    }
    fclose(f_pelanggan);
    _getch();

}

//2. Ubah Data Pelanggan
void MAP_ubah_pelanggan() {

}

//3. Hapus Data Pelanggan
void MAP_hapus_pelanggan() {

}

/*
 * Menu admin
 * 1. Data Pelanggan
 */
void MA_pelanggan() {

    char pilihan;

    do {
        fflush(stdin);
        clrscr();
        printf("=============================\n"
               "MENU DATA PELANGGAN\n"
               "=============================\n"
               "1. Tampil Data Pelanggan\n"
               "2. Ubah Data Pelanggan\n"
               "3. Hapus Data Pelanggan\n"
               "4. Kembali Ke MENU ADMIN\n"
               "5. Kembali Ke MENU UTAMA\n"
               "6. Keluar\n"
               "=============================\n"
               "Pilihan: "
        );
        pilihan = (char) getchar();

        switch(pilihan) {
            case '1':
                MAP_tampil_pelanggan();
                break;

            case '2':
                MAP_ubah_pelanggan();
                break;

            case '3':
                MAP_hapus_pelanggan();
                break;

            case '4':
                break;

            case '5':
                break;

            case '6':
                exit(0);
            default:
                printf("Pilih hanya dari 1-6\n");

        }

    } while (pilihan < 1 || pilihan > 6);
}

void menu_admin() {
    char pilihan;
    do
    {
        fflush(stdin);
        clrscr();
        printf("===========================\n"
               "MENU ADMIN\n"
               "===========================\n"
               "1. Data Pelanggan\n"
               "2. Data Makanan\n"
               "3. Data Minuman\n"
               "4. Data Order\n"
               "5. Kembali Ke Menu Utama\n"
               "6. Keluar\n"
               "===========================\n"
               "Pilihan: "
               );
        pilihan = (char) getchar();

        switch(pilihan) {
            case '1':
                MA_pelanggan();
                break;

            case '2':
                break;

            case '3':
                break;

            case '4':
                break;

            case '5':
                goto ke_menu_utama;

            case'6':
                exit(0);

            default:
                printf("Pilih hanya dari 1-6\n");
        }
        printf("Tekan sembarang untuk kembali ke MENU ADMIN");
        getch();

    } while((pilihan < 1) || (pilihan > 6));

    ke_menu_utama:
    printf("");
}

int main() {

    char pilihan;

    do
    {
        fflush(stdin);
        clrscr();
        printf("============\n"
               "MENU UTAMA\n"
               "============\n"
               "1. Menu User\n"
               "2. Menu Admin\n"
               "3. Keluar\n"
               "=============\n"
               "Pilihan: "
        );
        pilihan = (char) getchar();
        switch (pilihan) {
            case '1':
                menu_user();
                break;

            case '2':
                menu_admin();
                break;

            case '3':
                exit(0);

            default:
                printf("Pilih hanya dari 1-3\n");

        }
    } while((pilihan < 1) || (pilihan > 3));
    return 0;
}