#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
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
/*
    TEMPAT UNTUK MENARUH STRUCT (SELESAI)
=======================================================================================||
*/

char adminPassword[] = {"admin123"};
char adminUsername[] = {"admin"};

/*
=======================================================================================||
    TEMPAT UNTUK MENARUH SEMUA FUNGSI DAN PROSEDUR YANG ADA (MULAI)
*/
char huruf_ulang[1];
void search();
void quit();
void registrasi();                               // untuk registrasi pegawai
void login();                                    // untuk login pegawai dan admin
int cekSuperPassword(char password[8]);          // untuk mengecek admin
int checkLogin(char nama[20], char password[8]); // untuk mengecek login yang dilakukan
int LoginMenu();                                 // menu dari login page
int menuKasir();
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
    int salah = 1;
    while (salah > 0)
    {
        scanf("%[^\n]", username);
        fflush(stdin);

        if (strlen(username) < 4 || strlen(username) > 16)
            salah++;
        for (int i = 0; i < strlen(username); i++)
        {
            if (!isdigit(username[i]) && !islower(username[i]) && !isupper(username[i]))
                salah++;
        }

        if (salah > 1)
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
    int salah = 1;
    while (salah > 0)
    {
        scanf("%[^\n]", password);
        fflush(stdin);

        if (strlen(password) < 8 || strlen(password) > 8) salah++;

        if (salah > 1)
        {
            printf("Masukkan password 8 digit !\n:");
        }
        else
        {
            break;
        }
    }
}

int cekUsernameRegis(char *username)
{
    char tempUsername[100];
    char tempPassword[100];
    int hasil;

    FILE *databaseUser = fopen("database.txt", "r");

    do
    {
        int baca = fscanf(databaseUser, "%99[^,],%99[^\n]\n", tempUsername, tempPassword);
        if (baca == 2)
        {
            if (strcmp(username, tempUsername) == 0)
            {
                hasil = 1;
            }
            else
            {
                hasil = 0;
            }
        }
    } while (!feof(databaseUser));
    fclose(databaseUser);

    return hasil;
}

/*
    TEMPAT VALIDASI SELESAI
=======================================================================================||
*/



/*
=======================================================================================||
    KODE LOGIN MULAI
*/
int checkLogin(char nama[20], char password[8]) // untuk mengecek username dan password (UDAH FIX SIH HARUSNYA)
{
    char temp[255];
    int i = 1, a = 0;

    if (strcmp(adminUsername, nama) == 0)
    {
        if (strcmp(adminPassword, password) == 0)
        {
            // menuAdmin();
            printf("anda admin");
        }
        else
        {
            printf("password anda salah");
        }
    }
    else
    {
        FILE *fptr = fopen("database.txt", "r");

        while ((fgets(temp, sizeof(temp), fptr)) != NULL)
        {
            if ((i % 2) == 1 && strcmp(temp, nama) == 0)
            {
                a++;
            }
            else if ((i % 2) == 0 && strcmp(temp, password) == 0)
            {
                a += 2;
            }
            i++;
            fflush(stdin);
        }
        fclose(fptr);
        return a;
    }
}

void registrasi() // untuk melakukan
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
        getchar();
        scanUsername(registrasiPegawai.username);
        printf("Masukkan password anda: ");
        getchar();
        scanPassword(registrasiPegawai.password);
        fprintf(regisAkun, "%s,%s\n", registrasiPegawai.username, registrasiPegawai.password);
        fclose(regisAkun);
    }
    else
    {
        printf("===================================================\n");
        printf("\tPassword yang anda masukkan salah\n");
        printf("===================================================\n");
    }
}

void login()
{
    struct pengenal login;

    printf("===================================================\n");
    printf("Masukkan username: ");
    scanUsername(login.username);
    printf("Masukkan password anda: ");
    scanPassword(login.password);

    int hasilPengecekan = checkLogin(login.username, login.password);

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
    else if (hasilPengecekan == 0 || hasilPengecekan == 2)
    {
        printf("===================================================\n");
        printf("\tUsername anda salah\n");
        printf("===================================================\n");
    }
    else if (hasilPengecekan == -1)
    {
        printf("===================================================\n");
        printf("\tAnda belum membuat username dan password\n");
        printf("===================================================\n");
    }
    fflush(stdin);
}

int LoginMenu()
{
    int pilihan; // variabel untuk memilih nilai untuk pilihan yang dilakukan

    fflush(stdin);

    FILE *fptr = fopen("database_user.txt", "r");
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
    printf("==>");
    scanf("%d", &pilihan);

    system("clear||cls");
    getchar();
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
    fflush(stdin);

    printf("Terimakasih sudah mencoba");
    return 0;
}
/*
    KODE LOGIN SELESAI
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