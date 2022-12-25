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
int menuKasir();
int cekAkun();
void deleteLine(FILE *src, FILE *temp, const int line);
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
    int cek = 0;

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
                // printf("%s\n", tempPassword);
                // printf("%s\n", password);
                int hasil = strcmp(username, tempUsername);
                // printf("%d\n", strcmp(password, tempPassword));
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
    printf("[1] login\n");
    printf("[2]Register\n");
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
void CekBarang(struct barang list[1000]) //untuk mengecek isi dari database stok
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

void ubahStok(struct barang ubah[1000]) //untuk mengubah stok barang yang ada pada database stok
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

void ubahHarga(struct barang list[1000])//untuk mengubah harga barang yang ada pada database stok
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

void tambahBarang(struct barang list[1000]) //untuk menambahkan barang ke database stok barang
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

int cekStok() //untuk menunjukkan isi database stok
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
    inputInt(&pilihan,"");
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
int menuUbahMember(){
    struct member cek[1000];
    int pilihan;

    cekMember(cek);
    printf("[1]Hapus Member [0]EXIT");
    inputInt(&pilihan,"=>");
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
        menuAdmin();
        break;
    }
}

/*
    MENU ADMIN
=======================================================================================||
*/

/*
=======================================================================================||
    KODE APA ???
*/
void sort()
{
    char str[255];

    FILE *fp;
    fp = fopen("stok.txt", "r");
    while (fgets(str, 255, fp) != NULL)
    {
        printf("%s", str);
        fclose(fp);
    }
}

void search()
{
    int kode, jmlh;

    typedef char *string;
    string nama[11] = {"a", "[1] Roti", "[2] Susu", "[3] Beras", "[4] Sabun", "[5] Fanta"};
    string urutan[11] = {"a", "Pertama", "Kedua", "Ketiga", "Keempat", "Kelima"};
    int jumlah = 0, t, i, n[1000], y, x, kembali, nobeli, nomor[1000], tt[1000], u;
    int harga[] = {1, 12000, 7000, 30000, 15000, 6000}, d[1000], tot[1000];
    double total = 0, uang;

awal:
    system("clear");
    i = 0, x = 0, y = 0, nobeli = 0, kembali = 0, uang = 0, total = 0;
    printf("\n Transaksi\n\n");
    printf("================================================================================");
    printf("\n No.|     Nama Barang   |  Harga Barang(Rupiah) |\n");
    printf("----+-------------------+-----------------------+\n");
    for (i = 1; i < 6; i++)
    {
        printf("%3d |%13s      |      Rp.%5d.00      |\n", i, nama[i], harga[i]);
    }
    printf("===============================================================================\n");
    do
    {
        printf("Jumlah Jenis barang yang anda beli  : ");
        scanf("%d", &x);
        if (x > 5)
        {
            printf("\nInput Salah! Barang hanya dari 1 sampai 5!  \n\tSilahkan Ulangi lagi!\n\n");
        }
    } while (x > 5);
    for (i = 1; i <= x; i++)
    {
        do
        {
            printf("\nMasukkan Nomor barang %s : ", urutan[i]);
            scanf("%d", &d[i]);
            y = d[i];
            if (y > 5)
            {
                printf("Maaf nomor barang hanya sampai 5");
            }
        } while (y > 5);
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
    for (i = 1; i <= x; i++)
    {
        y = d[i];
        tt[i] = n[i] * harga[y];
        nobeli = d[i];
        printf("%3d      %8s           Rp.%2d.00            %4d        Rp. %d.00\t  \n", i, nama[nobeli], harga[nobeli], n[i], tt[i]);
    }
    printf("===============================================================================\n");
    printf("\n");
    printf("Totalnya yang anda bayar adalah     : Rp. %.2lf\n\n", total);
    u = 0;
    do
    {
        printf("Masukkan uang anda                  : Rp. ");
        scanf("%lf", &uang);
        if (uang < total)
            if (u == 0)
            {
                printf("\a\n\tMaaf uang anda kurang silahkan ulangi proses transaksi\n \t Silahkan masukkan lagi uang anda!\n\n");
            }
            else
            {
                continue;
            }
        u++;
    } while (uang < total);
    kembali = uang - total;
    printf("\nKembalian anda                      : Rp. %d.00", kembali);
    printf("\n\n                     Terima Kasih Telah Bertransaksi              \n");
    printf("\n_________________________________________________________________________\n\n");

pilihan_ulang:
    printf("\n  Ingin Melakukan Transaksi Lagi?");
    printf("\n  {1} Iya \n");
    printf("  {2} Tidak \n");
    printf("\n  Masukkan Pilihan : ");
    scanf("%s", &huruf_ulang);
    fflush(stdin);

    if ((strcmp(huruf_ulang, "1") != 0) && (strcmp(huruf_ulang, "2") != 0))
    {
        printf("    Input Invalid ! Masukan Input Yang Benar\n");
        goto pilihan_ulang;
    }
    else if ((strcmp(huruf_ulang, "1") == 0))
    {
        system("clear");
        goto awal;
    }
    else
    {
        goto end;
    }
end:
    printf("Program Berakhir");
}

void quit()
{
    printf("Program Berakhir");
}

int menuKasir()
{
    int pilihan, karakter;

    system("clear");
    printf("\n+--------------------------------+\n");
    printf("|                                |\n");
    printf("| [1] Cek Stok Barang            |\n");
    printf("| [2] Melakukan Transaksi        |\n");
    printf("| [3] Keluar                     |\n");
    printf("|                                |\n");
    printf("+--------------------------------+\n");

    while (1)
    {
        fflush(stdin);
        printf("\n\nMasukkan pilihan: ");
        if (scanf("%c%c", &pilihan, &karakter) != 2 || karakter != '\n')
        {
            printf("\nInput Salah! Mohon masukkan angka 1, 2, atau 3!\n");
            fflush(stdin);
        }
        else
        {
            if (pilihan == '1')
            {
                sort();
                break;
            }
            else if (pilihan == '2')
            {
                search();
                break;
            }
            else if (pilihan == '3')
            {
                quit();
                break;
            }
            else
            {
                printf("\nInput Invalid! Mohon memasukkan angka 1 sampai 3!\n");
            }
        }
    }
    return 0;
}
/*
    KODE APA ???
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