#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

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
struct member
{
    int IDMember;
    char nama[100];
    char noKtp[16];
    char noTelp[12];
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
char NamaKasir[20];
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
void registrasi();                       // untuk registrasi pegawai
void login();                            // untuk login pegawai dan admin
void scanUsername(char *username);       // untuk mengambil data username
void scanPassword(char *password);       // untuk mengambil data password
void CekBarang(struct barang list[]);    // untuk mengecek barang yang ada di database
void ubahStok(struct barang ubah[]);     // untuk mengubah database stok barang
void ubahHarga(struct barang list[]);    // untuk mengubah database harga barang
void tambahBarang(struct barang list[]); // untuk menambahkan barang
void menuAdmin();                        // menu yang dikhususkan untuk admin
void hapusAkun();
void tampilanAkun(struct pengenal list[]);
int main();                                      // tempat berjalannya program utama
int cekStok();                                   // tempat menu untuk mengecek stok dan mengubahnya
int cekUsernameRegis(char *username);            // untuk mengecek username saat registrasi atau login
int cekSuperPassword(char password[8]);          // untuk mengecek admin
int checkLogin(char nama[20], char password[8]); // untuk mengecek login yang dilakukan
int LoginMenu();                                 // menu dari login page
void menuKasir();
int cekAkun();
void deleteLine(FILE *src, FILE *temp, const int line);
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
            if (!islower(username[i]) && !isupper(username[i]))
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
    int hasil;
    while (1)
    {
        printf("%s", prompt);
        hasil = validInt(var);
        if (hasil == 1)
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
int checkLogin(char username[20], char password[8]) // UDAH FIX SIH HARUSNYA
{
    char tempUsername[100];
    char tempPassword[100];
    int cek = 0, hasil1;

    if (strcmp(adminUsername, username) == 0)
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
                // printf("%s\n", tempUsername);
                // printf("%s\n", username);
                tempPassword[8] = '\0';
                // printf("%s\n", tempPassword);
                // printf("%s\n", password);
                int hasil = strcmp(username, tempUsername);
                // printf("%d\n", strcmp(password, tempPassword));
                if (hasil == 0)
                {

                    hasil1 = strcmp(password, tempPassword);
                    printf("%d", hasil1);
                    if (hasil1 == 0)
                    {
                        strcpy(NamaKasir, username);
                        return 2; // Username dan password sesuai
                    }
                    else
                    {
                        return 1; // Username dan password tidak sesuai
                    }
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
    system("clear||cls");
    printf("=============================================\n");
    printf("SILAHKAN UNTUK MELAKUKAN LOGIN DAN REGISTRASI\n");
    printf("=============================================\n");
    printf("[1] login\n");
    printf("[2] Register\n");
    printf("[0] exit\n");
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
    case 0:
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

// untuk mengubah database stok barang
void CekBarang(struct barang list[1000]) // untuk mengecek isi dari database stok
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

void ubahStok(struct barang ubah[1000]) // untuk mengubah stok barang yang ada pada database stok
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

void ubahHarga(struct barang list[1000]) // untuk mengubah harga barang yang ada pada database stok
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

void tambahBarang(struct barang list[1000]) // untuk menambahkan barang ke database stok barang
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

void hapusStok()
{
    struct barang list[1000];
    FILE *src;
    FILE *temp;
    int line;
    printf("Pilih barang yang akan di hapus\n");
    inputInt(&line, "==>");

    src = fopen("stok.txt", "r");
    temp = fopen("delete.tmp", "w");
    if (src == NULL || temp == NULL)
    {
        printf("FILE TAK DAPAT DIBUKA");
    }
    deleteLine(src, temp, line); // fungsi untuk menghapus baris text
    fclose(src);
    fclose(temp);
    remove("stok.txt");               // menghapus file stok.txt
    rename("delete.tmp", "stok.txt"); // mengganti nama file
}

int cekStok() // untuk menunjukkan isi database stok
{
    struct barang cek[1000];
    char namabarang[100];
    int i = 0, pilihan, banyakBarang, hargaBarang;

    CekBarang(cek);
    printf("\n\n[1] Mengubah Stok, [2] Mengubah harga\n [3] Menambah barang, [4] Hapus barang, [0]EXIT\n");
    inputInt(&pilihan, "=>");
    system("clear||cls");
    switch (pilihan)
    {
    case 0:
        menuAdmin();
        break;
    case 1: // untuk mengubah stok barang
        CekBarang(cek);
        ubahStok(cek);
        menuAdmin();
        break;
    case 2: // untuk mengubah harga barang
        CekBarang(cek);
        ubahHarga(cek);
        menuAdmin();
        break;
    case 3: // untuk menambahkan barang yang ada pada database stok
        CekBarang(cek);
        tambahBarang(cek);
        menuAdmin();
        break;
    case 4:
        CekBarang(cek);
        hapusStok();
        menuAdmin();
        break;
    default:
        cekStok();
        break;
    }
    return 0;
}
// mengubah database stok selesai

void deleteLine(FILE *src, FILE *temp, const int line)
{
    char buffer[1020];
    int count = 1;
    while ((fgets(buffer, 1020, src)) != NULL) // jika diambil nilai string tidak sama dengan nol maka program akan berjalan
    {
        if (line != count)
            fputs(buffer, temp); // untuk menulis string pada file temp
        count++;                 // untuk menghitung
    }
}

// mengubah database akun mulai
void hapusAkun()
{
    struct pengenal Akun[1000];
    FILE *src;
    FILE *temp;
    int line;
    printf("Pilih akun yang akan di hapus\n");
    inputInt(&line, "==>");

    src = fopen("akun.txt", "r");
    temp = fopen("delete.tmp", "w");
    if (src == NULL || temp == NULL)
    {
        printf("FILE TAK DAPAT DIBUKA");
    }
    deleteLine(src, temp, line); // fungsi untuk menghapus baris text
    fclose(src);
    fclose(temp);
    remove("akun.txt");               // menghapus file akun.txt
    rename("delete.tmp", "akun.txt"); // mengganti nama file
    cekAkun();
}

int cekAkun()
{
    struct pengenal Akun[1000];
    int pilihan;
    tampilanAkun(Akun);
    printf("[1]Hapus Akun [0]EXIT");
    inputInt(&pilihan, "=>");
    system("clear||cls");
    switch (pilihan)
    {
    case 1:
        tampilanAkun(Akun);
        hapusAkun();
        break;
    case 0:
        exit(1);
        break;
    default:
        cekAkun();
        break;
    }
    return 0;
}

void tampilanAkun(struct pengenal list[1000])
{
    FILE *akun = fopen("akun.txt", "r");
    char tempUsername[100], tempPassword[100];
    int i = 0, pilihan;
    system("clear||cls");
    printf("+----------------------------------------------+\n");
    printf("|                   AKUN                       |\n");
    printf("|==============================================|\n");
    printf("Username\t||Password\n");
    do
    {
        int baca = fscanf(akun, "%99[^,],%99[^\n]\n", tempUsername, tempPassword);
        fflush(stdin);
        if (baca == 2)
        {
            strcpy(list[i].username, tempUsername);
            strcpy(list[i].password, tempPassword);
        }
        printf("%d. %s\t||", i + 1, list[i].username);
        printf("%s\n", list[i].password);
        i++;
    } while (!feof(akun));
    fclose(akun);
}
// mengubah database akun selesai

// mengubah database member mulai
void cekMember(struct member list[1000])
{
    FILE *member = fopen("member.txt", "r");
    char tempNama[100], tempNoKtp[100], tempNoTelp[100], tempID[100];
    int i = 0, pilihan, banyakbarang;
    printf("+----------------------------------------------+\n");
    printf("|                   Cek Member                   |\n");
    printf("|==============================================|\n");
    do
    {
        int baca = fscanf(member, "%99[^,],%99[^,],%99[^,],%99[^\n]\n", tempID, tempNama, tempNoKtp, tempNoTelp);
        if (baca == 4)
        {
            strcpy(list[i].nama, tempNama);
            list[i].IDMember = atoi(tempID);
            strcpy(list[i].noKtp, tempNoKtp);
            strcpy(list[i].noTelp, tempNoTelp);
        }
        printf("[%d]\t||Nama \t\t:%s\n", i + 1, list[i].nama);
        printf("\t||No. KTP \t:%.16s\n", list[i].noKtp);
        printf("\t||No. Telp \t:%s\n", list[i].noTelp);
        printf("\t||ID Member \t:%d\n", list[i].IDMember);
        printf("|==============================================|\n");
        i++;
    } while (!feof(member));
    fclose(member);
}
int UbahMember()
{
    struct member cek[1000];
    int pilihan;

    FILE *src;
    FILE *temp;

    cekMember(cek);
    printf("Masukkan pilihan yang akan dihapus: ");
    inputInt(&pilihan, "");
    system("clear||cls");
    src = fopen("member.txt", "r");
    temp = fopen("delete.tmp", "w");
    deleteLine(src, temp, pilihan);
    if (src == NULL || temp == NULL)
    {
        printf("FILE TAK DAPAT DIBUKA");
    }
    fclose(src);
    fclose(temp);
    remove("member.txt");               // menghapus file akun.txt
    rename("delete.tmp", "member.txt"); // mengganti nama file
    cekMember(cek);
}
int menuUbahMember()
{
    struct member cek[1000];
    int pilihan;

    cekMember(cek);
    printf("[1]Hapus Member [0]EXIT");
    inputInt(&pilihan, "=>");
    switch (pilihan)
    {
    case 1:
        UbahMember();
        menuUbahMember();
        break;
    case 0:
        exit(1);
        break;
    default:
        printf("Masukkan angka berupa 1 dan 0\n");
        break;
    }
}
// mengubah database member selesai
void menuAdmin()
{
    int pilihan;
    system("clear||cls");
    printf("\n+--------------------------------+\n");
    printf("|           MENU ADMIN           |\n");
    printf("|================================|\n");
    printf("| [1] Cek Stok Barang            |\n");
    printf("| [2] Cek Database Akun          |\n");
    printf("| [3] Cek Member                 |\n");
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
        cekAkun();
        break;
    case 3:
        menuUbahMember();
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
void printTransaksi(struct barang list[1000], int pilihan, int banyak, int index)
{
    int harga, cek;
    pilihan -= 1;
    // printf("%s", list[pilihan].namaBarang);
    // printf("%d", banyak);
    harga = list[pilihan].hargaBarang * banyak;
    cek = strcmp(list[pilihan].namaBarang, "\0");
    if (cek == 0)
    {
        printf("Barang tidak ditemukan\n");
        transaksi();
    }

    // printf("%d", harga);
    if (index == 0)
    {
        FILE *pembelian = fopen("pembelian.txt", "w+");
        fprintf(pembelian, "%s,%d,%d\n", list[pilihan].namaBarang, banyak, harga);
        fclose(pembelian);
    }
    else
    {
        FILE *pembelian = fopen("pembelian.txt", "a");
        fprintf(pembelian, "%s,%d,%d\n", list[pilihan].namaBarang, banyak, harga);
        fclose(pembelian);
    }
}

void ubahBelanja(struct barang list[1000])
{
    int barangUbah, banyakBaru;
    inputInt(&barangUbah, "Pilih barang yang akan diubah : ");
    inputInt(&banyakBaru, "Masukkan banyak barang : ");
    barangUbah -= 1;
    banyakBaru = list[barangUbah].hargaBarang;
}

void hapusBelanja()
{
    FILE *src;
    FILE *temp;
    int line;
    printf("Pilih barang yang akan di hapus\n");
    inputInt(&line, "==>");

    src = fopen("pembelian.txt", "r");
    temp = fopen("delete.tmp", "w");
    if (src == NULL || temp == NULL)
    {
        printf("FILE TAK DAPAT DIBUKA");
    }
    deleteLine(src, temp, line); // fungsi untuk menghapus baris text
    fclose(src);
    fclose(temp);
    remove("pembelian.txt");               // menghapus file akun.txt
    rename("delete.tmp", "pembelian.txt"); // mengganti nama file
}
void printBelanja(struct barang list[1000])
{
    FILE *belanja = fopen("pembelian.txt", "r");
    char tempNamaBarang[100], tempBanyakBarang[100], tempHargaBarang[100], namabarang[100];
    int i = 0, pilihan, banyakbarang;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\n\n+----------------------------------------------------+\n");
    printf("|                     BELANJA                        |\n");
    printf("|====================================================|\n");
    printf("|TANGGAL: %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    printf("|Nama Kasir: %s\n", NamaKasir);
    printf("|====================================================|\n");
    printf("|Nama Barang\t||Banyak Pembelian\t||Harga Barang||\n");
    printf("|====================================================|\n");
    do
    {
        int baca = fscanf(belanja, "%99[^,],%99[^,],%99[^\n]\n", tempNamaBarang, tempBanyakBarang, tempHargaBarang);
        if (baca == 3)
        {
            strcpy(list[i].namaBarang, tempNamaBarang);
            list[i].stokBarang = atoi(tempBanyakBarang);
            list[i].hargaBarang = atoi(tempHargaBarang);
        }
        printf("%d. %s\t||", i + 1, list[i].namaBarang);
        printf("%d\t\t\t||", list[i].stokBarang);
        printf("Rp.%d\n", list[i].hargaBarang);
        i++;
    } while (!feof(belanja));
    fclose(belanja);
}
void printStruk(struct barang list[1000])
{
    FILE *belanja = fopen("struk.txt", "w+");
    char tempNamaBarang[100], tempBanyakBarang[100], tempHargaBarang[100], namabarang[100];
    int i = 0, pilihan, banyakbarang, hasil;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(belanja, "\n\n+----------------------------------------------------+\n");
    fprintf(belanja, "|                     BELANJA                        |\n");
    fprintf(belanja, "|====================================================|\n");
    fprintf(belanja, "|TANGGAL: %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    fprintf(belanja, "|Nama Kasir: %s\n", NamaKasir);
    fprintf(belanja, "|====================================================|\n");
    fprintf(belanja, "|Nama Barang\t||Banyak Pembelian\t||Harga Barang||\n");
    fprintf(belanja, "|====================================================|\n");
    while (1)
    {
        hasil = strcmp(list[i].namaBarang, "\0");
        if (hasil == 0)
        {
            break;
        }
        fprintf(belanja, "%d. %s\t||", i + 1, list[i].namaBarang);
        fprintf(belanja, "%d\t\t\t||", list[i].stokBarang);
        fprintf(belanja, "Rp.%d\n", list[i].hargaBarang);
        i++;
    }
    fclose(belanja);
}
void setelahPembayaran(struct barang list[1000], struct barang list1[1000])
{
    int i = 0, a = 0, akhir1, akhir2, sama;
    while (1)
    {
        akhir1 = strcmp(list[i].namaBarang, "\0");
        if (akhir1 == 0)
        {
            break;
        }
        else
        {
            for (a = 0; a < 1000; a++)
            {
                akhir2 = strcmp(list1[a].namaBarang, "\0");
                sama = strcmp(list[i].namaBarang, list1[a].namaBarang);
                if (akhir2 == 0)
                {
                    break;
                }
                else
                {
                    if (sama == 0)
                    {
                        list[i].stokBarang = list[i].stokBarang - list1[a].stokBarang;
                    }
                }
            }
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
        i++;
    }
}

int pembayaran(struct barang list[1000])
{
    int i, hasil, hargaTotal;
    while (1)
    {
        hasil = strcmp(list[i].namaBarang, "\0");
        if (hasil == 0)
        {
            break;
        }
        else
        {
            hargaTotal = hargaTotal + list[i].hargaBarang;
        }
    }
    printf("%d\n", hargaTotal);
    return hargaTotal;
}

int PembeliMember(int masuk)
{
    FILE *member = fopen("member.txt", "r");
    char tempNama[100], tempNoKtp[100], tempNoTelp[100], tempID[100];
    int i = 0, Id;
    do
    {
        int baca = fscanf(member, "%99[^,],%99[^,],%99[^,],%99[^\n]\n", tempID, tempNama, tempNoKtp, tempNoTelp);
        if (baca == 4)
        {
            Id = atoi(tempID);
            if (Id == masuk)
            {
                return 1;
            }
        }
    } while (!feof(member));
    fclose(member);
    return 0;
}

void transaksi()
{
    int pilihan, jawaban, banyakBarang, i = 0, pengulang, bayar, hargatotal = 0, kembalian, hasil, samaMember, Idmember, diskon;
    struct barang kasir[1000];
    struct barang belanja[1000];
    struct member berbelanja[1000];

    while (1)
    {
        system("clear||cls");
        CekBarang(kasir);
        inputInt(&pilihan, "\n\nPilih barang yang mau dibeli: ");
        inputInt(&banyakBarang, "Masukkan banyak barang yang mau di beli: ");
        printTransaksi(kasir, pilihan, banyakBarang, i);
        system("clear||cls");
        do
        {
            CekBarang(kasir);
            printBelanja(belanja);
            printf("\n\n[1] Tambah barang\n[2]Ubah banyak barang\n[3]Hapus barang \n[4]lanjut ke pembayaran\n[0]EXIT\n");
            inputInt(&jawaban, "=>");
            system("clear||cls");
            if (jawaban == 1)
            {
                break;
            }
            else if (jawaban == 2)
            {
                int barangUbah, banyakBaru;
                printBelanja(belanja);
                inputInt(&barangUbah, "Pilih barang yang akan diubah : ");
                inputInt(&banyakBaru, "Masukkan banyak barang : ");
                barangUbah -= 1;
                printTransaksi(kasir, pilihan, banyakBaru, barangUbah);
            }
            else if (jawaban == 3)
            {
                hapusBelanja();
            }
            else if (jawaban == 4)
            {
                // printBelanja(belanja);
                for (i = 0; i < 1000; i++)
                {
                    hasil = strcmp(belanja[i].namaBarang, "\0");
                    if (hasil == 0)
                    {
                        break;
                    }
                    else
                    {
                        // printf("%d\n", belanja[i].hargaBarang);
                        hargatotal = hargatotal + belanja[i].hargaBarang;
                    }
                }
                while (1)
                {
                    do
                    {
                        printBelanja(belanja);
                        printf("\n\nMasukkan angka 0 jika tidak ada member\n");
                        inputInt(&Idmember, "Masukkan ID Member: ");
                        samaMember = PembeliMember(Idmember);
                        if (samaMember == 1)
                        {
                            diskon = 0.25 * hargatotal;
                            hargatotal = hargatotal - diskon;
                            break;
                        }
                        else if (Idmember == 0)
                        {
                            break;
                        }
                        pengulang = 1;
                        system("clear||cls");
                    } while (pengulang == 1);

                    system("clear||cls");
                    printBelanja(belanja);
                    printf("\n\nHARGA TOTAL\t\t\tRp.%d\n", hargatotal);
                    inputInt(&bayar, "Banyak uang yang dibayarkan: ");
                    kembalian = bayar - hargatotal;
                    // printf("%d\n", kembalian);

                    if (kembalian < 0)
                    {
                        system("clear||cls");
                        printf("Uang kurang\n");
                    }
                    else if (kembalian == 0)
                    {
                        break;
                    }
                    else
                    {
                        printf("Kembalian Rp.%d", kembalian);
                        printf("Tekan enter untuk lanjut");
                        getchar();
                        break;
                    }
                }
                setelahPembayaran(kasir, belanja);
                printStruk(belanja);
                remove("pembelian.txt");
                menuKasir();
            }
            else if (jawaban == 0)
            {
                menuKasir();
            }
            pengulang = 1;
        } while (pengulang == 1);
        i++;
    }
}

void inputKTP(char *noKtp)
{
    int salah;
    while (1)
    {
        salah = 0;
        scanf("%[^\n]", noKtp);
        fflush(stdin);
        getchar();

        if (strlen(noKtp) > 16 || strlen(noKtp) < 16)
            salah++;
        else
        {
            for (int i = 0; i < strlen(noKtp); i++)
            {
                if (!isdigit(noKtp[i]))
                {
                    salah++;
                }
            }
        }

        if (salah > 0)
        {
            printf("Masukkan nomor KTP 16 digit dan harus berupa angka\n==>");
        }
        else
        {
            break;
        }
    }
}
void inputTelp(char *noTelp)
{
    int salah;
    while (1)
    {
        salah = 0;
        scanf("%[^\n]", noTelp);
        fflush(stdin);
        getchar();

        if (strlen(noTelp) > 12 || strlen(noTelp) < 12)
            salah++;
        else
        {
            for (int i = 0; i < strlen(noTelp); i++)
            {
                if (!isdigit(noTelp[i]))
                {
                    salah++;
                }
            }
        }

        if (salah > 0)
        {
            printf("Masukkan nomor Telp 12 digit dan harus berupa angka\n==>");
        }
        else
        {
            break;
        }
    }
}

int inputNomor()
{
    char tempNomor[100];
    char tempNama[100];
    char tempNoKtp[100];
    char tempNoTelp[100];
    int nomor;

    FILE *nomorMember = fopen("member.txt", "r");

    if (nomorMember == NULL)
    {
        return 1;
    }
    else
    {
        do
        {
            int baca = fscanf(nomorMember, "%99[^,],%99[^,],%99[^,],%99[^\n]\n", tempNomor, tempNama, tempNoKtp, tempNoTelp);
            if (baca == 4)
            {
                nomor = atoi(tempNomor);
            }
        } while (!feof(nomorMember));
        nomor++;
        return nomor;
        fclose(nomorMember);
    }
}

int cekKtp(char *noKtp)
{
    FILE *cekKTP = fopen("member.txt", "r");
    char tempNomor[100];
    char tempNama[100];
    char tempNoKtp[100];
    char tempNoTelp[100];
    int hasil;

    do
    {
        int baca = fscanf(cekKTP, "%99[^,],%99[^,],%99[^,],%99[^\n]\n", tempNomor, tempNama, tempNoKtp, tempNoTelp);
        if (baca == 4)
        {
            hasil = strcmp(noKtp, tempNoKtp);
            if (hasil == 0)
            {
                return 1;
            }
        }
    } while (!feof(cekKTP));
    fclose(cekKTP);
}

int tambahMember()
{
    struct member masuk;
    int hasil;

    printf("\n+--------------------------------+\n");
    printf("|          TAMBAH MEMBER         |\n");
    printf("|================================|\n");
    printf("masukkan nama: ");
    scanf("%[^\n]", masuk.nama);
    fflush(stdin);
    getchar();
    printf("Masukkan No KTP: ");
    inputKTP(masuk.noKtp);
    printf("Masukkan No Telp: ");
    inputTelp(masuk.noTelp);
    masuk.IDMember = inputNomor();
    hasil = cekKtp(masuk.noKtp);
    if (hasil == 1)
    {
        system("clear||cls");
        printf("Nomor KTP sudah pernah dipakai\n");
        tambahMember();
    }
    else
    {
        system("clear||cls");
        printf("\n+--------------------------------+\n");
        printf("|            MEMBER              |\n");
        printf("|================================|\n");
        printf("Id Member: %d\n", masuk.IDMember);
        printf("Id Member: %s\n", masuk.nama);
        printf("Id Member: %s\n", masuk.noKtp);
        printf("Id Member: %s\n", masuk.noTelp);
        FILE *tambahMember = fopen("member.txt", "a");
        fprintf(tambahMember, "%d,%s,%s,%s\n", masuk.IDMember, masuk.nama, masuk.noKtp, masuk.noTelp);
        fclose(tambahMember);
    }
    printf("\n\nTekan enter untuk melanjutkan");
    getchar();
}

// fungsi menu kasir
void menuKasir()
{
    system("clear||cls");
    int pilihan;
    struct barang list[1000];
    printf("\n+--------------------------------+\n");
    printf("|           MENU KASIR           |\n");
    printf("|================================|\n");
    printf("|                                |\n");
    printf("| [1] Cek Stok Barang            |\n");
    printf("| [2] Melakukan Transaksi        |\n");
    printf("| [3] Tambah Member              |\n");
    printf("| [0] Keluar                     |\n");
    printf("|                                |\n");
    printf("+--------------------------------+\n");
    inputInt(&pilihan, "==>");
    system("clear||cls");

    switch (pilihan)
    {
    case 1:
        CekBarang(list);
        printf("[0]EXIT\n");
        inputInt(&pilihan, "==>");
        if (pilihan == 0)
        {
            menuKasir();
        }
        break;
    case 2:
        // menuju fungsi transaksi
        transaksi();
        break;
    case 3:
        tambahMember();
        main();
    case 0:
        // menuju fungsi quit
        exit(1);
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