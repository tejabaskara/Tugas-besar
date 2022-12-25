#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
=======================================================================================||
    TEMPAT UNTUK MENARUH STRUCT (MULAI)
*/
struct Mahasiswa
{
    char nama[20];
    int nilai;
};
struct pengenal // untuk membuat variabel menjadi lebih mudah untuk dimengerti
{
    char username[80];
    char password[8];
};
struct barang // untuk membuat variabel barang
{
    char namaBarang[100];
    int stokBarang;
    int hargaBarang;
};
/*
    TEMPAT UNTUK MENARUH STRUCT (SELESAI)
=======================================================================================||
*/

/*
=======================================================================================||
    TEMPAT UNTUK VARIABEL GLOBAL (MULAI)
*/
char adminPassword[] = {"admin123"};
char adminUsername[] = {"admin"};
char huruf_ulang[1];
/*
    TEMPAT UNTUK VARIABEL GLOBAL (SELESAI)
=======================================================================================||
*/

/*
=======================================================================================||
    TEMPAT UNTUK MENARUH SEMUA FUNGSI DAN PROSEDUR YANG ADA (MULAI)
*/
void search();
void quit();
void registrasi(); // untuk registrasi pegawai
void login();      // untuk login pegawai dan admin
void scanUsername(char *username); //untuk mengambil data username
void scanPassword(char *password); // untuk mengambil data password
void CekBarang(struct barang list[]); //untuk mengecek barang yang ada di database
void ubahStok(struct barang ubah[]); // untuk mengubah database stok barang
void ubahHarga(struct barang list[]); // untuk mengubah database harga barang
void tambahBarang(struct barang list[]); // untuk menambahkan barang
void menuAdmin(); //menu yang dikhususkan untuk admin
int main(); //tempat berjalannya program utama
int cekStok(); // tempat menu untuk mengecek stok dan mengubahnya
int cekUsernameRegis(char *username); //untuk mengecek username saat registrasi atau login
int cekSuperPassword(char password[8]);          // untuk mengecek admin
int checkLogin(char nama[20], char password[8]); // untuk mengecek login yang dilakukan
int LoginMenu();                                 // menu dari login page
void menuKasir();
void search();
void quit();
void transaksi();

/*
    TEMPAT UNTUK MENARUH SEMUA FUNGSI DAN PROSEDUR YANG ADA (SELESAI)
=======================================================================================||
*/

/*
=======================================================================================||
    TEMPAT VALIDASI MULAI
*/
void scanUsername(char *username) // Validasi dan input username
{
    int salah;
    while (1)
    {
        salah = 0;
        scanf(" %[^\n]", username);
        fflush(stdin);

        if (strlen(username) < 4 || strlen(username) > 16)
            salah++;
        for (int i = 0; i < strlen(username); i++)
        {
            if (!isdigit(username[i]) && !islower(username[i]) && !isupper(username[i]))
                salah++;
        }

        if (salah > 0)
        {
            printf("Format username yang anda masukkan salah\n> ");
        }
        else
        {
            break;
        }
    }
}

void scanPassword(char *password) // Validasi dan input password
{
    int salah;
    while (1)
    {
        scanf("%[^\n]", password);
        fflush(stdin);
        getchar();

        if (strlen(password) > 8 || strlen(password) < 8)
            printf("Masukkan password 8 digit !\n:");
        else
            break;
    }
}

int cekUsernameRegis(char *username)
{
    char tempUsername[100];
    char tempPassword[100];
    int hasil = 0;

    FILE *databaseUser = fopen("akun.txt", "r");

    do
    {
        int baca = fscanf(databaseUser, "%99[^,],%99[^\n]\n", tempUsername, tempPassword);
        if (baca == 2)
        {
            if (strcmp(username, tempUsername) == 0)
            {
                hasil++;
            }
        }
    } while (!feof(databaseUser));
    fclose(databaseUser);

    return hasil;
}

int validInt(int *var)
{
    char buff[1020];
    char cek;
    fflush(stdin);
    if (fgets(buff, sizeof(buff), stdin) != NULL) // mengecek apakah pada input yang dimasukkan terdapat string jika tidak input akan lanjut
    {
        if (sscanf(buff, "%d %c", var, &cek) == 1) // mengecek ulang apakah input benar tidak ada character
        {
            return 1;
        }
    }
    return 0;
}
void inputInt(int *var, char *prompt)
{
    while (1)
    {
        printf("%s", prompt);
        if (validInt(var))
            break;
        printf("Input hanya  boleh berupa angka!! \n");
        printf("\n");
    }
}
/*
    TEMPAT VALIDASI SELESAI
=======================================================================================||
*/

/*
=======================================================================================||
    KODE LOGIN DAN REGISTRASI MULAI
*/
int checkLogin(char nama[20], char password[8]) // untuk mengecek username dan password (UDAH FIX SIH HARUSNYA)
{
    char tempUsername[100];
    char tempPassword[100];
    int cek = 0;

    if (strcmp(adminUsername, nama) == 0)
    {
        if (strcmp(adminPassword, password) == 0)
        {
            menuAdmin();
        }
        else
        {
            printf("password anda salah");
        }
    }
    else
    {
        FILE *logincek = fopen("akun.txt", "r");

        do
        {
            int read = fscanf(logincek, "%99[^,],%99[^\n]\n", tempUsername, tempPassword);
            if (read == 2)
            {
                printf("%s\n", tempUsername);
                printf("%s\n", nama);
                printf("%s\n", tempPassword);
                printf("%s\n", password);
                int hasil = strcmp(nama, tempUsername);
                printf("%d\n", strcmp(nama, tempUsername));
                if (hasil == 0)
                {
                    if (strcmp(password, tempPassword) == 0)
                    {
                        return 2; // Username dan password sesuai
                    }
                    else
                    {
                        return 1; // Username dan password tidak sesuai
                    }
                }
                else
                {
                    return 0; // Username tidak ada
                }
            }
        } while (!feof(logincek));
        fclose(logincek);

        return cek;
    }
}

void registrasi() // untuk melakukan registrasi (UDAH FIX SIH HARUSNYA)
{
    struct pengenal admin;
    struct pengenal registrasiPegawai;

    printf("Masukkan password ADMIN: ");
    scanPassword(admin.password);
    int hasil = strcmp(admin.password, adminPassword);

    system("clear||cls");

    FILE *regisAkun = fopen("akun.txt", "a+");

    if (hasil == 0)
    {
        printf("===================================================\n");
        printf("\tPassword ADMIN yang anda masukkan benar\n");
        printf("===================================================\n\n");
        printf("Masukkan username: ");
        scanUsername(registrasiPegawai.username);
        printf("Masukkan password anda: ");
        getchar();
        scanPassword(registrasiPegawai.password);

        int cek = cekUsernameRegis(registrasiPegawai.username);
        // printf("%d", cek);
        while (cek == 1)
        {
            printf("USERNAME ANDA SUDAH TERDAFTAR\n\n");
            printf("Masukkan username: ");
            scanUsername(registrasiPegawai.username);
            printf("Masukkan password anda: ");
            getchar();
            scanPassword(registrasiPegawai.password);
            cek = cekUsernameRegis(registrasiPegawai.username);
        }
        fprintf(regisAkun, "%s,%s\n", registrasiPegawai.username, registrasiPegawai.password);
        fclose(regisAkun);
        system("clear||cls");
    }
    else
    {
        printf("===================================================\n");
        printf("\tPassword yang anda masukkan salah\n");
        printf("===================================================\n");
    }
}

void login() // belum mau fix masih dalam proses
{
    struct pengenal login;

    printf("===================================================\n");
    printf("Masukkan username: ");
    scanUsername(login.username);
    // printf("%s", login.username);
    printf("Masukkan password anda: ");
    getchar();
    scanPassword(login.password);

    int hasilPengecekan = checkLogin(login.username, login.password);

    // printf("%d", hasilPengecekan);
    if (hasilPengecekan == 2)
    {
        printf("===================================================\n");
        printf("\tLogin berhasil\n");
        printf("===================================================\n");
        system("pause");
        menuKasir();
    }
    else if (hasilPengecekan == 1)
    {
        printf("===================================================\n");
        printf("\tPassword anda salah\n");
        printf("===================================================\n");
    }
    else if (hasilPengecekan == 0)
    {
        printf("===================================================\n");
        printf("\tUsername tidak berhasil ditemukan\n");
        printf("===================================================\n");
    }
}

int LoginMenu()
{
    int pilihan; // variabel untuk memilih nilai untuk pilihan yang dilakukan
    FILE *fptr = fopen("akun.txt", "r");
    if (fptr == NULL)
    {
        printf("=======================================================================================\n");
        printf("Anda belum memiliki data untuk melakukan registrasi\n");
        printf("=======================================================================================\n");
        printf("Tekan enter untuk melanjutkan ");
        getchar();
        system("clear||cls");
        registrasi();
    }

    printf("=============================================\n");
    printf("SILAHKAN UNTUK MELAKUKAN LOGIN DAN REGISTRASI\n");
    printf("=============================================\n");
    printf("1. login\n");
    printf("2. Register\n");
    printf("9. exit\n");
    inputInt(&pilihan, "==>");

    system("clear||cls");
    switch (pilihan)
    {
    case 1: // untuk login
        login();
        break;
    case 2: // untuk melakukan registrasi
        registrasi();
        LoginMenu();
        break;
    case 9:
        exit(1);
    }

    printf("Terimakasih sudah mencoba");
    return 0;
}
/*
    KODE LOGIN DAN REGISTRASI SELESAI
=======================================================================================||
*/

/*
=======================================================================================||
    MENU ADMIN
*/
void CekBarang(struct barang list[1000])
{
    FILE *stok = fopen("stok.txt", "r");
    char tempNamaBarang[100], tempStokBarang[100], tempHargaBarang[100], namabarang[100];
    int i = 0, pilihan, banyakbarang;
    printf("+----------------------------------------------+\n");
    printf("|                   Cek Stok                   |\n");
    printf("|==============================================|\n");
    printf("Nama Barang\t||Stok Barang\t||Harga Barang||\n");
    do
    {
        int baca = fscanf(stok, "%99[^,],%99[^,],%99[^\n]\n", tempNamaBarang, tempStokBarang, tempHargaBarang);
        if (baca == 3)
        {
            strcpy(list[i].namaBarang, tempNamaBarang);
            list[i].stokBarang = atoi(tempStokBarang);
            list[i].hargaBarang = atoi(tempHargaBarang);
        }
        printf("%d. %s\t||", i + 1, list[i].namaBarang);
        printf("%d\t\t||", list[i].stokBarang);
        printf("Rp.%d\n", list[i].hargaBarang);
        i++;
    } while (!feof(stok));
    fclose(stok);
}

void ubahStok(struct barang ubah[1000])
{
    char namabarang[100];
    int banyakBarang, i = 0;
    printf("\n\n           Mengubah Stok        \n");
    printf("Masukkan nama barang: ");
    scanf("%[^\n]", namabarang);
    fflush(stdin);
    getchar();
    inputInt(&banyakBarang, "Banyak stok:");
    fflush(stdin);
    system("clear||cls");
    for (i = 0; i < 1000; i++)
    {
        int hasil = strcmp(ubah[i].namaBarang, "\0");
        int hasilBarang = strcmp(ubah[i].namaBarang, namabarang);
        if (hasil == 0)
        {
            break;
        }
        else
        {
            if (hasilBarang == 0)
            {
                if (i == 0)
                {
                    ubah[i].stokBarang = banyakBarang;
                    FILE *ganti = fopen("stok.txt", "w");
                    fprintf(ganti, "%s,%d,%d\n", ubah[i].namaBarang, ubah[i].stokBarang, ubah[i].hargaBarang);
                    fclose(ganti);
                }
                else
                {
                    ubah[i].stokBarang = banyakBarang;
                    FILE *ganti = fopen("stok.txt", "a");
                    fprintf(ganti, "%s,%d,%d\n", ubah[i].namaBarang, ubah[i].stokBarang, ubah[i].hargaBarang);
                    fclose(ganti);
                }
            }
            else
            {
                if (i == 0)
                {
                    FILE *ganti = fopen("stok.txt", "w");
                    fprintf(ganti, "%s,%d,%d\n", ubah[i].namaBarang, ubah[i].stokBarang, ubah[i].hargaBarang);
                    fclose(ganti);
                }
                else
                {
                    FILE *ganti = fopen("stok.txt", "a");
                    fprintf(ganti, "%s,%d,%d\n", ubah[i].namaBarang, ubah[i].stokBarang, ubah[i].hargaBarang);
                    fclose(ganti);
                }
            }
        }
    }
    cekStok();
}

void ubahHarga(struct barang list[1000])
{
    char namabarang[100];
    int hargaBarang, i = 0;
    printf("\n\n          Mengubah Harga       \n");
    printf("Masukkan nama barang: ");
    scanf("%[^\n]", namabarang);
    fflush(stdin);
    getchar();
    inputInt(&hargaBarang, "Harga barang:");
    fflush(stdin);
    system("clear||cls");
    for (i = 0; i < 1000; i++)
    {
        int hasil = strcmp(list[i].namaBarang, "\0");
        int hasilBarang = strcmp(list[i].namaBarang, namabarang);
        if (hasil == 0)
        {
            break;
        }
        else
        {
            if (hasilBarang == 0)
            {
                if (i == 0)
                {
                    list[i].hargaBarang = hargaBarang;
                    FILE *ganti = fopen("stok.txt", "a");
                    fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
                    fclose(ganti);
                }
                else
                {
                    list[i].hargaBarang = hargaBarang;
                    FILE *ganti = fopen("stok.txt", "a");
                    fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
                    fclose(ganti);
                }
            }
            else
            {
                if (i == 0)
                {
                    FILE *ganti = fopen("stok.txt", "w");
                    fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
                    fclose(ganti);
                }
                else
                {
                    FILE *ganti = fopen("stok.txt", "a");
                    fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
                    fclose(ganti);
                }
            }
        }
    }
    cekStok();
}

void tambahBarang(struct barang list[1000])
{
    char namabarang[100];
    int hargaBarang, banyakBarang, i = 0;
    printf("\n\n         Menambah Stok         \n");
    printf("Masukkan nama barang: ");
    scanf("%[^\n]", namabarang);
    fflush(stdin);
    getchar();
    inputInt(&banyakBarang, "Stok Barang: ");
    fflush(stdin);
    inputInt(&hargaBarang, "Harga barang: ");
    fflush(stdin);
    system("clear||cls");

    for (i = 0; i < 1000; i++)
    {
        int hasil = strcmp(list[i].namaBarang, "\0");
        int hasilBarang = strcmp(list[i].namaBarang, namabarang);
        if (hasil == 0)
        {
            break;
        }
        else
        {
            if (hasilBarang == 0)
            {
                printf("BARANG SUDAH TERDAPAT PADA NOMOR %d\n", i + 1);
                cekStok();
                break;
            }
        }
    }

    for (i = 0; i < 1000; i++)
    {
        int hasil = strcmp(list[i].namaBarang, "\0");
        if (hasil == 0)
        {
            strcpy(list[i].namaBarang, namabarang);
            list[i].stokBarang = banyakBarang;
            list[i].hargaBarang = hargaBarang;
            FILE *ganti = fopen("stok.txt", "a");
            fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
            fclose(ganti);
            break;
        }
        else
        {
            if (i == 0)
            {
                FILE *ganti = fopen("stok.txt", "w");
                fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
                fclose(ganti);
            }
            else
            {
                FILE *ganti = fopen("stok.txt", "a");
                fprintf(ganti, "%s,%d,%d\n", list[i].namaBarang, list[i].stokBarang, list[i].hargaBarang);
                fclose(ganti);
            }
        }
    }
    cekStok();
}

int cekStok()
{
    struct barang cek[1000];
    char namabarang[100];
    int i = 0, pilihan, banyakBarang, hargaBarang;

    CekBarang(cek);
    printf("\n\n[1] Mengubah Stok, [2] Mengubah harga, [3] Menambah barang, [0]EXIT ");
    inputInt(&pilihan, "=>");
    system("clear||cls");
    switch (pilihan)
    {
    case 0:
        main();
        break;
    case 1: // untuk mengubah stok barang
        CekBarang(cek);
        ubahStok(cek);
        break;
    case 2: // untuk mengubah harga barang
        CekBarang(cek);
        ubahHarga(cek);
        break;
    case 3: // untuk menambahkan barang yang ada pada database stok
        CekBarang(cek);
        tambahBarang(cek);
        break;
    }
    return 0;
}

void menuAdmin()
{
    int pilihan;
    system("clear||cls");
    printf("\n+--------------------------------+\n");
    printf("|           MENU ADMIN           |\n");
    printf("|================================|\n");
    printf("| [1] Cek Stok Barang            |\n");
    printf("| [2] Cek Database Akun          |\n");
    printf("| [3] Cek Discount               |\n");
    printf("| [4] Cek Member                 |\n");
    printf("| [0] EXIT                       |\n");
    printf("|                                |\n");
    printf("+--------------------------------+\n");
    inputInt(&pilihan, "==>");
    system("clear||cls");

    switch (pilihan)
    {
    case 1:
        cekStok();
        break;
    case 2:
        // cekAkun();
        printf("Under Maintenence");
        break;
    case 3:
        // cekDiscount();
        printf("Under Maintenence");
        break;
    case 4:
        // cekMember();
        printf("Under Maintenence");
        break;
    case 0:
        exit(1);
        break;
    }
}

/*
    MENU ADMIN
=======================================================================================||
*/

/*
=======================================================================================||
    KODE KASIR
*/

//Kode untuk melakukan transaksi
void transaksi()
{
    int kode, jmlh;
    typedef char* string;
string nama[11]={"a","[1] Roti","[2] Susu","[3] Beras","[4] Sabun","[5] Fanta"};
string urutan[11]={"a","Pertama","Kedua","Ketiga","Keempat","Kelima"};
int jumlah = 0, t, i, n[1000], y, x, kembali, nobeli, nomor[1000], tt[1000], u;
int harga[]={1,12000,7000,30000,15000,6000}, d[1000], tot[1000];
double total = 0, uang;

    system("clear");
    i = 0, x = 0, y = 0,nobeli = 0,kembali = 0,uang = 0, total = 0;
        printf("\n Transaksi\n\n");
        printf("================================================================================");
        printf("\n No.|     Nama Barang   |  Harga Barang(Rupiah) |\n");
        printf("----+-------------------+-----------------------+\n");
    for(i = 1; i < 6 ; i++) {
        printf("%3d |%13s      |      Rp.%5d.00      |\n", i, nama[i], harga[i]);  }
        printf("===============================================================================\n");
    do{
        printf("Jumlah Jenis barang yang anda beli  : "); 
        scanf("%d", &x);
        if(x > 5){
        printf("\nInput Salah! Barang hanya dari 1 sampai 5!  \n\tSilahkan Ulangi lagi!\n\n");}
    }while(x > 5);
    
    for(i = 1; i <= x ; i++)    
    {
        do{
            printf("\nMasukkan Nomor barang %s : ", urutan[i]);scanf("%d", &d[i]);
        y = d[i];

        if (y > 5)
        {
            printf("Maaf nomor barang hanya sampai 5");
        }
        }while (y > 5);
            printf("Masukkan jumlah barang  : ");
            scanf("%d", &n[i]);
            y = d[i];
            tot[y] = n[i] * harga[y];
            total = tot[y] + total;
    }
        system("clear");
        printf("\nDaftar Pembelian Anda    :  \n");
        printf("================================================================================");
        printf("\n No. |   Nama Barang  |  Harga Barang(Rupiah) | Jumlah Barang |    Subtotal   |\n");
        printf("-----+----------------+-----------------------+---------------+---------------+\n");
    for(i = 1; i <= x ; i++)   {
    y = d[i];
    tt[i] = n[i] * harga[y];
    nobeli = d[i];
        printf("%3d      %8s           Rp.%2d.00            %4d        Rp. %d.00\t  \n",i,  nama[nobeli], harga[nobeli],n[i], tt[i]);
    }
        printf("===============================================================================\n");
        printf("\n");
        printf("Totalnya yang anda bayar adalah     : Rp. %.2lf\n\n", total);
    u = 0;
    do{
        printf("Masukkan uang anda                  : Rp. ");
        scanf("%lf", &uang);
    if (uang < total)
    if(u == 0)
    {
        printf("\a\n\tMaaf uang anda kurang silahkan ulangi proses transaksi\n \t Silahkan masukkan lagi uang anda!\n\n");
    }else
    {
    continue;
    }u++;
    }while (uang < total);
    kembali = uang - total;
        printf("\nKembalian anda                      : Rp. %d.00", kembali);
        printf("\n\n                        Terima Kasih Telah Bertransaksi              \n");
        printf("\n_________________________________________________________________________\n\n");
}

// fungsi untuk mengulangi fungsi transaksi .
void ulang()
{
    int pilihanUlang;

    printf("\n  Ingin Melakukan Transaksi Lagi?");
    printf("\n  {1} Iya \n");
    printf("  {2} Tidak \n");
    
    inputInt(&pilihanUlang, "> ");
    switch (pilihanUlang)
    {
        case 1:
            transaksi();
            break;
        case 2:
            break;
    }
    
}

//fungsi quit untuk mengakhiri program
void quit()
{
    printf("Program Berakhir");
}

//fungsi menu kasir
void menuKasir()
{
    int pilihan;

    system("clear");
    printf("\n+--------------------------------+\n");
    printf("|           MENU KASIR           |\n");
    printf("|================================|\n");
    printf("|                                |\n");
    printf("| [1] Cek Stok Barang            |\n");
    printf("| [2] Melakukan Transaksi        |\n");
    printf("| [3] Keluar                     |\n");
    printf("|                                |\n");
    printf("+--------------------------------+\n");
    inputInt(&pilihan, "==>");
    system("clear");

    switch (pilihan)
    {
        case 1:
            //cek stok barang
            cekStok();
            break;
        case 2:
            //menuju fungsi transaksi
            transaksi();
            break;
        case 3:
            //menuju fungsi quit
            quit();
            break;
    }
}
/*
    KODE KASIR BERAKHIR
=======================================================================================||
*/

/*
    MAIN MULAI
=======================================================================================||
*/
int main()
{
    LoginMenu();
}
/*
    MAIN SELESAI
=======================================================================================||
*/