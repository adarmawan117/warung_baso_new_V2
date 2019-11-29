#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <ctype.h>

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
    long long int harga;
} Data_Makanan;

typedef struct {
    char id[MAX];
    char nama[MAX];
    long long int harga;
} Data_Minuman;

typedef struct {
    char nama[MAX];
    long long int jumlah_belanja;
} Data_Pelanggan;

typedef struct {
    char id[MAX];
    char tanggal[MAX];
    char nama_pelanggan[MAX];
    char jenis_orderan[MAX][20]; // makanan atau minuman
    char nama_orderan[MAX][MAX]; // nama makanan atau minuman yang dipesan
    long long int harga_orderan[MAX];
    long long bayar_pelanggan;
    char metode[MAX]; // metode yang dipakai untuk membayar (Tunai atau Non Tunai)
    char status_bayar[MAX];
} Data_Order;

Data_Makanan data_makanan;
Data_Minuman data_minuman;
Data_Pelanggan data_pelanggan;
Data_Order data_order;

FILE *f_makanan, *f_minuman;

void buka_makanan() {
    if((f_makanan = fopen("File_Makanan.txt","a+")) == NULL){
        clrscr();
        printf("Data Makanan Tidak Bisa Dibuka Euy...\n");
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

void input_makanan_manual(){
    buka_makanan();
    strcpy(data_makanan.id,   "MK-0001");
    strcpy(data_makanan.nama, "Bakso Kuah Biasa");
    data_makanan.harga        = 14000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MK-0002");
    strcpy(data_makanan.nama,  "Bakso Kuah Spesial");
    data_makanan.harga         = 20000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MK-0003");
    strcpy(data_makanan.nama,  "Bakso Yamin Biasa");
    data_makanan.harga         = 15000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MK-0004");
    strcpy(data_makanan.nama,  "Bakso Yamin Spesial");
    data_makanan.harga         = 21000;
    fwrite(&data_makanan, sizeof(data_makanan), 1, f_makanan);

    strcpy(data_makanan.id,    "MK-0005");
    strcpy(data_makanan.nama,  "Bakso Kuah Beranak");
    data_makanan.harga         = 27000;
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
        if(ukuran_file == 0) {
            input_makanan_manual();
            buka_makanan();
        }

        printf("||==============||======================||==============================||==============||\n");
        printf("||\tNo\t||\tKode Makanan\t||\tNama Makanan\t\t||\tHarga\t||\n");
        printf("||==============||======================||==============================||==============||\n");

        while(fread(&data_makanan, sizeof(data_makanan), 1, f_makanan))
            printf("||\t%i.\t||\t%s\t\t||\t%s\t||\t%lli\t||\n",++i, data_makanan.id, data_makanan.nama, data_makanan.harga);
        printf("==========================================================================================\n");
    }
    fclose(f_makanan);
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
        if(ukuran_file == 0) {
            input_minuman_manual();
            buka_minuman();
        }

        printf("\n\n"
               "||==============||======================||==============================||==============||\n");
        printf("||\tNo\t||\tKode Minuman\t||\tNama Minuman\t\t||\tHarga\t||\n");
        printf("||==============||======================||==============================||==============||\n");

        while(fread(&data_minuman, sizeof(data_minuman), 1, f_minuman))
            printf("||\t%i.\t||\t%s\t\t||\t%s\t\t||\t%lli\t||\n",++i, data_minuman.id, data_minuman.nama, data_minuman.harga);
        printf("==========================================================================================\n");
    }
    fclose(f_minuman);
}

/* ================================================ AWAL METHOD MENU USER ===================================================*/
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
/* ================================================ AKHIR METHOD MENU USER ===================================================*/

/*
 * Menu admin => Data Pelanggan
 */
FILE *f_pelanggan, *f_temp;
void buka_pelanggan() {
    if((f_pelanggan = fopen("File_Pelanggan.txt","a+")) == NULL){
        clrscr();
        printf("Data Pelanggan Tidak Bisa Dibuka Euy...\n");
        exit(1);
    }
}

void buka_temp() {
    if((f_temp = fopen("temp.txt", "a+")) == NULL) {
        clrscr();
        printf("Data Temp Tidak Bisa Dibuka Euy...\n");
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
    int i = 0, file_handle_pelanggan, file_handle_temp, ukuran_file_pelanggan;
    char cari_nama[MAX] = "";

    printf("===============================\n"
           "MENU UBAH DATA PELANGGAN\n"
           "===============================\n\n"
    );

    buka_pelanggan();
    buka_temp();

    file_handle_pelanggan = fileno(f_pelanggan);
    file_handle_temp      = fileno(f_temp);

    if( ((ukuran_file_pelanggan = filelength(file_handle_pelanggan)) == -1L) || ((filelength(file_handle_temp)) == -1L) ){

        printf("Tidak dapat memperoleh ukuran file :(\n");
        Sleep(1000);
        fclose(f_pelanggan);
        fclose(f_temp);
        exit(1);

    } else {
        if (ukuran_file_pelanggan == 0)
            printf("Data Pelanggan Kosong!\n");
        else {
            printf("\n\n"
                   "Masukkan nama yang ingin dirubah: ");
            scanf("%[^\n]%*c", &cari_nama);

            while(fread(&data_pelanggan, sizeof(data_pelanggan), 1, f_pelanggan)) {
                if (strcmp(cari_nama, data_pelanggan.nama) == 0) {
                    char rubah;
                    printf("Nama %s ditemukan\n", cari_nama);
                    printf("\n\n"
                           "===================================\n"
                           "DETAIL\n"
                           "===================================\n"
                           "Nama\t\t: %s\n"
                           "Jumlah Belanja\t: %lli\n", data_pelanggan.nama, data_pelanggan.jumlah_belanja);
                    printf("===================================\n\n");
                    printf("Ingin merubah? [Y/T] ");
                    rubah = (char) getchar();

                    if (rubah == 'Y') {
                        printf("Masukkan nama baru: ");
                        fflush(stdin);
                        scanf("%[^\n]%*c", &data_pelanggan.nama);
                        printf("Masukkan jumlah belanja baru: ");
                        scanf("%lli", &data_pelanggan.jumlah_belanja);
                    }
                }
                fwrite(&data_pelanggan, sizeof(data_pelanggan), 1, f_temp);
            } // end while

            fclose(f_pelanggan);
            fclose(f_temp);
            remove("File_Pelanggan.txt");
            rename("temp.txt", "File_Pelanggan.txt");
        }
    }
}

//3. Hapus Data Pelanggan
void MAP_hapus_pelanggan() {
    int i = 0, file_handle_pelanggan, file_handle_temp, ukuran_file_pelanggan;
    char hapus_nama[MAX] = "";

    printf("===============================\n"
           "MENU HAPUS DATA PELANGGAN\n"
           "===============================\n\n"
    );

    buka_pelanggan();
    buka_temp();

    file_handle_pelanggan = fileno(f_pelanggan);
    file_handle_temp      = fileno(f_temp);

    if( ((ukuran_file_pelanggan = filelength(file_handle_pelanggan)) == -1L) || ((filelength(file_handle_temp)) == -1L) ){

        printf("Tidak dapat memperoleh ukuran file :(\n");
        Sleep(1000);
        fclose(f_pelanggan);
        fclose(f_temp);
        exit(1);

    } else {
        if (ukuran_file_pelanggan == 0)
            printf("Data Pelanggan Kosong!\n");
        else {
            printf("\n\n"
                   "Masukkan nama yang ingin hapus: ");
            scanf("%[^\n]%*c", &hapus_nama);

            while(fread(&data_pelanggan, sizeof(data_pelanggan), 1, f_pelanggan)) {
                if (strcmp(hapus_nama, data_pelanggan.nama) == 0) {
                    char hapus;
                    printf("Nama %s ditemukan\n", hapus_nama);
                    printf("\n\n"
                           "===================================\n"
                           "DETAIL\n"
                           "===================================\n"
                           "Nama\t\t: %s\n"
                           "Jumlah Belanja\t: %lli\n", data_pelanggan.nama, data_pelanggan.jumlah_belanja);
                    printf("===================================\n\n");
                    printf("Yakin Ingin Menghapus? [Y/T] ");
                    hapus = (char) getchar();

                    // jika Y, maka hapus, jika selain Y maka jangan hapus
                    if (hapus != 'Y')
                        fwrite(&data_pelanggan, sizeof(data_pelanggan), 1, f_temp);
                }

            } // end while

            fclose(f_pelanggan);
            fclose(f_temp);
            remove("File_Pelanggan.txt");
            rename("temp.txt", "File_Pelanggan.txt");
        }
    }
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
                menu_admin();
                break;

            case '5':
                main();
                break;

            case '6':
                exit(0);
            default:
                printf("Pilih hanya dari 1-6\n");

        }

    } while (pilihan < 1 || pilihan > 6);
}

/* ======================================= AKHIR FUNCTION MENU ADMIN DATA PELANGGAN =============================================================*/

/*
 * MENU ADMIN MAKANAN
 * Ubah Data Makanan
 */
void MAMAK_ubah_makanan() {

    int ketemu = 0;
    char cari_id[MAX] = "";

    tampil_makanan();

    buka_makanan();
    buka_temp();

    printf("\n\n"
           "Masukkan id makanan yang ingin dirubah: ");
    scanf("%[^\n]%*c", &cari_id);

    printf("\n\n"
           "=================================\n"
           "MENAMPILKAN HASIL PENCARIAN\n"
           "=================================\n"
    );
    while(fread(&data_makanan, sizeof(data_makanan), 1, f_makanan)) {
        if (strcmp(cari_id, data_makanan.id) == 0) {

            ++ketemu;

            printf("%i. "
                   "\tKode Makanan\t: %s\n"
                   "\tNama Makanan\t: %s\n"
                   "\tHarga\t: %lli\n",

                   ketemu,
                   data_makanan.id,
                   data_makanan.nama,
                   data_makanan.harga
            );

            char rubah;
            printf("===================================\n\n");
            printf("Ingin merubah? [Y/T] ");
            rubah = (char) getchar();

            if (rubah == 'Y') {

                printf("\n"
                       "==========================\n"
                       "UPDATE DATA\n"
                       "==========================\n"
                       "ID : "
                );
                fflush(stdin);
                gets(data_makanan.id);
                printf("Nama Makanan: ");
                fflush(stdin);
                gets(data_makanan.nama);
                printf("Harga: ");
                scanf("%lli", &data_makanan.harga);

            }
        }
        fwrite(&data_makanan, sizeof(data_makanan), 1, f_temp);
    }

    fclose(f_makanan);
    fclose(f_temp);
    remove("File_Makanan.txt");
    rename("temp.txt", "File_Pelanggan.txt");
}

// Hapus Data Makanan
void MAMAK_hapus_makanan() {

    int ketemu = 0;
    char cari_id[MAX] = "";

    tampil_makanan();

    buka_makanan();
    buka_temp();

    printf("\n\n"
           "Masukkan id makanan yang ingin dihapus: ");
    scanf("%[^\n]%*c", &cari_id);

    printf("\n\n"
           "=================================\n"
           "MENAMPILKAN HASIL PENCARIAN\n"
           "=================================\n"
    );
    while(fread(&data_makanan, sizeof(data_makanan), 1, f_makanan)) {
        if (strcmp(cari_id, data_makanan.id) == 0) {

            ++ketemu;

            printf("%i. "
                   "\tKode Makanan\t: %s\n"
                   "\tNama Makanan\t: %s\n"
                   "\tHarga\t: %lli\n",

                   ketemu,
                   data_makanan.id,
                   data_makanan.nama,
                   data_makanan.harga
            );

            char hapus;
            printf("===================================\n\n");
            printf("Yakin ingin menghapus? [Y/T] ");
            hapus = (char) getchar();

            if (hapus != 'Y')
                fwrite(&data_makanan, sizeof(data_makanan), 1, f_temp);
        }
    }

    fclose(f_makanan);
    fclose(f_temp);
    remove("File_Makanan.txt");
    rename("temp.txt", "File_Makanan.txt");
}

/*
 * Menu admin
 * 2. Data Makanan
 */
void MA_makanan() {

    char pilihan;

    do {
        fflush(stdin);
        clrscr();
        printf("=============================\n"
               "MENU DATA MAKANAN\n"
               "=============================\n"
               "1. Tampil Data Makanan\n"
               "2. Ubah Data Makanan\n"
               "3. Hapus Data Makanan\n"
               "4. Kembali Ke MENU ADMIN\n"
               "5. Kembali Ke MENU UTAMA\n"
               "6. Keluar\n"
               "=============================\n"
               "Pilihan: "
        );
        pilihan = (char) getchar();

        switch(pilihan) {
            // 1.  tampil data makanan
            case '1': {
                printf("===========================\n"
                       "MENU TAMPIL MAKANAN\n"
                       "===========================\n\n"
                );
                tampil_makanan();
                _getch();
            }
                break;

            // 2. ubah data makanan
            case '2': {
                printf("===========================\n"
                       "MENU UBAH MAKANAN\n"
                       "===========================\n\n"
                );

                tampil_makanan();
                MAMAK_ubah_makanan();
                _getch();
            }
                break;

            case '3': {
                printf("===========================\n"
                       "MENU HAPUS MAKANAN\n"
                       "===========================\n\n"
                );

                tampil_makanan();
                MAMAK_hapus_makanan();
                _getch();
            }
                break;

            case '4':
                menu_admin();
                break;

            case '5':
                main();
                break;

            case '6':
                exit(0);
            default:
                printf("Pilih hanya dari 1-6\n");

        }

    } while (pilihan < 1 || pilihan > 6);
}

/* ======================================= AKHIR FUNCTION MENU ADMIN DATA MAKANAN =============================================================*/

/*
 * MENU ADMIN MAKANAN
 * Ubah Data Makanan
 */
void MAMAK_ubah_minuman() {

    int ketemu = 0;
    char cari_id[MAX] = "";

    tampil_minuman();

    buka_minuman();
    buka_temp();

    printf("\n\n"
           "Masukkan id minuman yang ingin dirubah: ");
    scanf("%[^\n]%*c", &cari_id);

    printf("\n\n"
           "=================================\n"
           "MENAMPILKAN HASIL PENCARIAN\n"
           "=================================\n"
    );
    while(fread(&data_minuman, sizeof(data_minuman), 1, f_minuman)) {
        if (strcmp(cari_id, data_minuman.id) == 0) {

            ++ketemu;

            printf("%i. "
                   "\tKode Minuman\t: %s\n"
                   "\tNama Minuman\t: %s\n"
                   "\tHarga\t: %lli\n",

                   ketemu,
                   data_minuman.id,
                   data_minuman.nama,
                   data_minuman.harga
            );

            char rubah;
            printf("===================================\n\n");
            printf("Yakin ingin merubah? [Y/T] ");
            rubah = (char) getchar();

            if (rubah == 'Y') {

                printf("\n"
                       "==========================\n"
                       "UPDATE DATA\n"
                       "==========================\n"
                       "ID : "
                );
                fflush(stdin);
                gets(data_minuman.id);
                printf("Nama Minuman: ");
                fflush(stdin);
                gets(data_minuman.nama);
                printf("Harga: ");
                scanf("%lli", &data_minuman.harga);

            }
        }
        fwrite(&data_minuman, sizeof(data_minuman), 1, f_temp);
    }

    fclose(f_minuman);
    fclose(f_temp);
    remove("File_Minuman.txt");
    rename("temp.txt", "File_Minuman.txt");
}

// Hapus Data Makanan
void MAMAK_hapus_minuman() {

    int ketemu = 0;
    char cari_id[MAX] = "";

    tampil_minuman();

    buka_minuman();
    buka_temp();

    printf("\n\n"
           "Masukkan id minuman yang ingin dihapus: ");
    scanf("%[^\n]%*c", &cari_id);

    printf("\n\n"
           "=================================\n"
           "MENAMPILKAN HASIL PENCARIAN\n"
           "=================================\n"
    );
    while(fread(&data_minuman, sizeof(data_minuman), 1, f_minuman))
        if (strcmp(cari_id, data_minuman.id) == 0) {

            ++ketemu;

            printf("%i. "
                   "\tKode Minuman\t: %s\n"
                   "\tNama Minuman\t: %s\n"
                   "\tHarga\t: %lli\n",

                   ketemu,
                   data_minuman.id,
                   data_minuman.nama,
                   data_minuman.harga
            );

            char hapus;
            printf("===================================\n\n");
            printf("Yakin ingin menghapus? [Y/T] ");
            hapus = (char) getchar();

            if (hapus != 'Y')
                fwrite(&data_minuman, sizeof(data_minuman), 1, f_temp);
        }

    fclose(f_minuman);
    fclose(f_temp);
    remove("File_Minuman.txt");
    rename("temp.txt", "File_Minuman.txt");
}

/*
 * Menu admin
 * 3. Data Minuman
 */
void MA_minuman() {

    char pilihan;

    do {
        fflush(stdin);
        clrscr();
        printf("=============================\n"
               "MENU DATA MINUMAN\n"
               "=============================\n"
               "1. Tampil Data Minuman\n"
               "2. Ubah Data Minuman\n"
               "3. Hapus Data Minuman\n"
               "4. Kembali Ke MENU ADMIN\n"
               "5. Kembali Ke MENU UTAMA\n"
               "6. Keluar\n"
               "=============================\n"
               "Pilihan: "
        );
        pilihan = (char) getchar();

        switch(pilihan) {
            // 1.  tampil data minuman
            case '1': {
                printf("===========================\n"
                       "MENU TAMPIL MINUMAN\n"
                       "===========================\n\n"
                );
                tampil_minuman();
                _getch();
            }
                break;

                // 2. ubah data minuman
            case '2': {
                printf("===========================\n"
                       "MENU UBAH MINUMAN\n"
                       "===========================\n\n"
                );

                tampil_minuman();
                MAMAK_ubah_minuman();
                _getch();
            }
                break;

            //3. hapus data minuman
            case '3': {
                printf("===========================\n"
                       "MENU HAPUS MINUMAN\n"
                       "===========================\n\n"
                );

                tampil_minuman();
                MAMAK_hapus_minuman();
                _getch();
            }
                break;

                // kembali ke menu admin
            case '4':
                menu_admin();
                break;

                // kembali ke menu utama
            case '5':
                main();
                break;

                // keluar dari program
            case '6':
                exit(0);
            default:
                printf("Pilih hanya dari 1-6\n");

        }

    } while (pilihan < 1 || pilihan > 6);
}

/* ======================================= AKHIR FUNCTION MENU ADMIN DATA MINUMAN =============================================================*/

FILE *f_order;
void buka_order() {
    if((f_order = fopen("File_Order.txt", "a+")) == NULL) {
        clrscr();
        printf("Data Order Tidak Bisa Dibuka Euy...\n");
        exit(1);
    }
}

void tambah_order_manual() {

    buka_order();

    strcpy(data_order.id, "AD-JAN-MK");
    strcpy(data_order.tanggal, "12-JANUARI-2019");
    strcpy(data_order.nama_pelanggan, "Agus Darmawan");

    strcpy(data_order.jenis_orderan[0], "Minuman");
    strcpy(data_order.nama_orderan[0], "Es-Campur");
    data_order.harga_orderan[0] = 12000;

    strcpy(data_order.jenis_orderan[1], "Makanan");
    strcpy(data_order.nama_orderan[1], "Nasi Goreng");
    data_order.harga_orderan[1] = 10000;

    strcpy(data_order.jenis_orderan[2], "Minuman");
    strcpy(data_order.nama_orderan[2], "Es-Doger");
    data_order.harga_orderan[2] = 9000;

    strcpy(data_order.jenis_orderan[3], "Makanan");
    strcpy(data_order.nama_orderan[3], "Sate Ayam");
    data_order.harga_orderan[3] = 20000;

    strcpy(data_order.jenis_orderan[4], "Makanan");
    strcpy(data_order.nama_orderan[4], "Pepes Ikan");
    data_order.harga_orderan[4] = 16000;

    data_order.bayar_pelanggan = 100000;
    strcpy(data_order.metode, "Tunai");
    strcpy(data_order.status_bayar, "Lunas");

    fwrite(&data_order, sizeof(data_order), 1, f_order);
    fclose(f_order);
}
/*
 * MENU ADMIN ORDERAN
 */
void MAO_tampil_order() {
    int ketemu = 0, file_handle, ukuran_file;

    buka_order();

    printf("||==============||==============================||==============================||==============================||==============================||\n");
    printf("||\tNo\t"
           "||\tID\t\t\t"
           "||\t\tTanggal\t\t"
           "||\tNama Pelanggan\t\t"
           "||\tTotal Belanja\t\t||\n");
    printf("||==============||==============================||==============================||==============================||==============================||\n");

    file_handle = fileno(f_order);
    if((ukuran_file = filelength(file_handle)) == -1L){
        printf("Tidak dapat memperoleh ukuran file :(\n");
        Sleep(1000);
        fclose(f_order);
        exit(1);
    } else {
        if(ukuran_file == 0) {
            tambah_order_manual();
            buka_order();
        }

        while (fread(&data_order, sizeof(data_order), 1, f_order)) {
            long long int total_bayar = 0;
            int i = 0;

            ++ketemu;

            while(data_order.harga_orderan[i] != '\0') {
                total_bayar += data_order.harga_orderan[i];
                i++;
            }

            printf("||\t%i\t"
                   "||\t%s\t\t"
                   "||\t%s\t\t"
                   "||\t%s\t\t"
                   "||\t%lli\t\t\t||\n",

                   ketemu,
                   data_order.id,
                   data_order.tanggal,
                   data_order.nama_pelanggan,
                   total_bayar
            );
        }
        printf("||==============||==============================||==============================||==============================||==============================||\n");

    }
    fclose(f_order);
}

void input_order() {

    memset(&data_order, 0, sizeof(data_order));

    printf("ID Order: ");
    fflush(stdin); gets(data_order.id);

    printf("Tanggal: ");
    fflush(stdin); gets(data_order.tanggal);

    printf("Nama Pelanggan: ");
    fflush(stdin); gets(data_order.nama_pelanggan);

    printf("\n");


    char pilih_jenis = '4'; // menampilkan makanan dan atau minuman
    char pilih_lagi; // untuk memilih menu lagi
    int i = 0; // untuk indexing pesanan (banyak pesanan)

    do {
        fflush(stdin);
        printf("1. Makanan\n"
               "2. Minuman\n"
        );
        pilih_jenis = (char) getchar();

        switch (pilih_jenis) {

            // jika yang dipilih adalah makanan
            case '1': {
                int pilih_menu;

                // tampilkan data makanan
                tampil_makanan();
                printf("\n"
                       "Pilih Menu No: ");
                scanf("%i", &pilih_menu);
                fflush(stdin);

                // buka file makanan, agar bisa diakses isinya
                buka_makanan();

                // isikan jenis orderan dengan makanan
                strcpy(data_order.jenis_orderan[i], "Makanan");

                int j = 0;
                while (fread(&data_makanan, sizeof(data_makanan), 1, f_makanan)) {
                    j++;

                    /*
                     * jika yang dipilih sama dengan menu:
                     * - maka masukkan nama makanan kedalam nama orderan
                     * - masukkan harga makanan kedalam harga orderan
                     */
                    if(pilih_menu == j){
                        strcpy(data_order.nama_orderan[i], data_makanan.nama);
                        data_order.harga_orderan[i] = data_makanan.harga;
                        // jika data makanan ditemukan, maka tambahkan index di data orderan makanan menjadi 2
                        i++;
                        break;
                    } // end if pilih_menu == j
                } // end while fread(data_makanan)
                fclose(f_makanan);

            } // end case '1'
                break;

                // jika yang dipilih adalah minuman
            case '2': {
                int pilih_menu;

                // tampilkan data minuman
                tampil_minuman();
                printf("\n"
                       "Pilih Menu No: ");
                scanf("%i", &pilih_menu);
                fflush(stdin);

                // buka file minuman, agar bisa diakses isinya
                buka_minuman();

                // isikan jenis orderan dengan minuman
                strcpy(data_order.jenis_orderan[i], "Minuman");

                int j = 0;
                while (fread(&data_minuman, sizeof(data_minuman), 1, f_minuman)) {
                    j++;

                    /*
                     * jika yang dipilih sama dengan menu:
                     * - maka masukkan nama minuman kedalam nama orderan
                     * - masukkan harga minuman kedalam harga orderan
                     */
                    if(pilih_menu == j){
                        strcpy(data_order.nama_orderan[i], data_minuman.nama);
                        data_order.harga_orderan[i] = data_minuman.harga;
                        // jika data minuman ditemukan, maka tambahkan index di data orderan minuman menjadi 2
                        i++;
                        break;
                    } // end if pilih_menu == j
                } // end while fread(data_minuman)
                fclose(f_minuman);
            }
                break;

            default: {
                printf("Pilih hanya makanan dan minuman saja!\n");
            }
        } // switch pilih_jenis (makanan atau minuman)

        printf("Ingin memilih lagi? [Y/T]");
        pilih_lagi = (char) getchar();
        pilih_lagi = (char) toupper(pilih_lagi);

        printf("\n");
    } while(pilih_jenis < '1' || pilih_jenis > '2' || pilih_lagi == 'Y');

    /*
     long long bayar_pelanggan;
    char metode[MAX]; // metode yang dipakai untuk membayar (Tunai atau Non Tunai)
    char status_bayar[MAX];
     */
    printf("Pelanggan bayar: ");
    scanf("%lli", &data_order.bayar_pelanggan);

    // jenis pembayaran (Tunai atau Non-Tunai)
    fflush(stdin);
    char bayar;
    do {
        printf("Metode Pembayaran\n"
               "1. Tunai\n"
               "2. Non-Tunai\n"
               "pilihan: ");
        bayar = (char) getchar();
        if(bayar == '1')
            strcpy(data_order.metode, "Tunai");
        else if(bayar == '2')
            strcpy(data_order.metode, "Non-Tunai");
        else
            printf("Pilih hanya Tunai atau Non-tunai!\n");
    } while(bayar < '1' || bayar > '2');

    // status pembyaran (Lunas atau Tidak Lunas)
    fflush(stdin);
    char status;
    do {
        printf("Status Pembayaran\n"
               "1. Lunas\n"
               "2. Tidak Lunas\n"
               "pilihan: ");
        status = (char) getchar();
        if(status == '1')
            strcpy(data_order.status_bayar, "Lunas");
        else if(status == '2')
            strcpy(data_order.status_bayar, "Tidak Lunas");
        else
            printf("Pilih hanya Lunas atau Tidak Lunas!\n");
    } while(status < '1' || status > '2');

}

//Ubah Data Orderan
void MAO_ubah_order() {

    int ketemu = 0;
    char cari_id[MAX] = "";

    buka_order();
    buka_temp();

    printf("\n\n"
           "Masukkan id orderan yang ingin dirubah: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &cari_id);

    printf("\n\n"
           "=================================\n"
           "MENAMPILKAN HASIL PENCARIAN\n"
           "=================================\n"
    );
    while(fread(&data_order, sizeof(data_order), 1, f_order)) {
        if (strcmp(cari_id, data_order.id) == 0) {

            ++ketemu;

            printf("%i. "
                   "\tID Order\t: %s\n"
                   "\tTanggal\t\t: %s\n"
                   "\tNama Pelanggan\t: %s\n",

                   ketemu,
                   data_order.id,
                   data_order.tanggal,
                   data_order.nama_pelanggan
            );

            printf("\n");

            // menampilkan makanan dan atau minuman
            int i = 0;
            while((strcmp(data_order.jenis_orderan[i],"")) != 0) {
                printf("\t%i."
                       "\t\t%s \t=> %s \t=> %lld\n"
                        , i,
                       data_order.jenis_orderan[i],
                       data_order.nama_orderan[i],
                       data_order.harga_orderan[i]
                );
                i++;
            }

            printf("\n");

            // menampilkan data setelah data makanan dan minuman
            printf("\tBayar Pelanggan\t: %lld\n"
                   "\tMetode\t\t: %s\n"
                   "\tStatus Bayar\t: %s\n",

                   data_order.bayar_pelanggan,
                   data_order.metode,
                   data_order.status_bayar
            );

            char rubah;
            printf("===================================\n\n");
            printf("Yakin ingin merubah? [Y/T] ");
            rubah = (char) getchar();
            rubah = (char) toupper(rubah);

            if (rubah == 'Y') {

                printf("\n"
                       "==========================\n"
                       "UPDATE DATA\n"
                       "==========================\n"
                );
                input_order();
            }

        }

        fwrite(&data_order, sizeof(data_order), 1, f_temp);
    }

    fclose(f_order);
    fclose(f_temp);
    remove("File_Order.txt");
    rename("temp.txt", "File_Order.txt");
}

// Hapus Data Orderan
void MAO_hapus_order() {

    int ketemu = 0;
    char cari_id[MAX] = "";

    buka_order();
    buka_temp();

    printf("\n\n"
           "Masukkan id orderan yang ingin dihapus: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &cari_id);

    printf("\n\n"
           "=================================\n"
           "MENAMPILKAN HASIL PENCARIAN\n"
           "=================================\n"
    );
    while(fread(&data_order, sizeof(data_order), 1, f_order)) {
        if (strcmp(cari_id, data_order.id) == 0) {

            ++ketemu;

            printf("%i. "
                   "\tID Order\t: %s\n"
                   "\tTanggal\t\t: %s\n"
                   "\tNama Pelanggan\t: %s\n",

                   ketemu,
                   data_order.id,
                   data_order.tanggal,
                   data_order.nama_pelanggan
            );

            printf("\n");

            // menampilkan makanan dan atau minuman
            int i = 0;
            while((strcmp(data_order.jenis_orderan[i],"")) != 0) {
                printf("\t%i."
                       "\t\t%s \t=> %s \t=> %lld\n"
                        , i,
                       data_order.jenis_orderan[i],
                       data_order.nama_orderan[i],
                       data_order.harga_orderan[i]
                );
                i++;
            }

            printf("\n");

            // menampilkan data setelah data makanan dan minuman
            printf("\tBayar Pelanggan\t: %lld\n"
                   "\tMetode\t\t: %s\n"
                   "\tStatus Bayar\t: %s\n",

                   data_order.bayar_pelanggan,
                   data_order.metode,
                   data_order.status_bayar
            );

            char rubah;
            printf("===================================\n\n");
            printf("Yakin ingin menghapus? [Y/T] ");
            rubah = (char) getchar();
            rubah = (char) toupper(rubah);

            if (rubah != 'Y')
                fwrite(&data_order, sizeof(data_order), 1, f_temp);

        }
    }

    fclose(f_order);
    fclose(f_temp);
    remove("File_Order.txt");
    rename("temp.txt", "File_Order.txt");
}

/*
 * Menu admin
 * 4. Data Order
 */
void MA_order() {

    char pilihan;

    do {
        fflush(stdin);
        clrscr();
        printf("=============================\n"
               "MENU DATA ORDERAN\n"
               "=============================\n"
               "1. Tampil Data Order\n"
               "2. Ubah Data Order\n"
               "3. Hapus Data Order\n"
               "4. Kembali Ke MENU ADMIN\n"
               "5. Kembali Ke MENU UTAMA\n"
               "6. Keluar\n"
               "=============================\n"
               "Pilihan: "
        );
        pilihan = (char) getchar();

        switch(pilihan) {
            // 1.  tampil data order
            case '1': {
                printf("===========================\n"
                       "MENU TAMPIL ORDERAN\n"
                       "===========================\n\n"
                );
                MAO_tampil_order();
                _getch();
            }
                break;

                // 2. ubah data order
            case '2': {
                printf("===========================\n"
                       "MENU UBAH ORDERAN\n"
                       "===========================\n\n"
                );

                MAO_tampil_order();
                MAO_ubah_order();
                _getch();
            }
                break;

                //3. hapus data order
            case '3': {
                printf("===========================\n"
                       "MENU HAPUS ORDERAN\n"
                       "===========================\n\n"
                );

                MAO_tampil_order();
                MAO_hapus_order();
                _getch();
            }
                break;

                // kembali ke menu admin
            case '4':
                menu_admin();
                break;

                // kembali ke menu utama
            case '5':
                main();
                break;

                // keluar dari program
            case '6':
                exit(0);
            default:
                printf("Pilih hanya dari 1-6\n");

        }

    } while (pilihan < 1 || pilihan > 6);
}

/* ======================================= AKHIR FUNCTION MENU ADMIN DATA MINUMAN =============================================================*/

void menu_admin() {
    char pilihan;
    do {
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
            // 1. menu admin data pelanggan
            case '1':
                MA_pelanggan();
                break;

                // 2. menu admin data makanan
            case '2':
                MA_makanan();
                break;

                // 3. menu admin data minuman
            case '3':
                MA_minuman();
                break;

                // 4. menu admin data order
            case '4':
                MA_order();
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

    do {
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