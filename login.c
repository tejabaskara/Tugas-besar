#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr; // file pointer sebagai alat yang digunakan untuk membuka dan mengubah database yang berupa file text

struct pengenal// untuk membuat variabel menjadi lebih mudah untuk dimengerti
{
    char username[80];
    char password[8];
};

int cekRegis(char username[20]){
    fptr = fopen("database_user.txt", "r");
    
    char temp[80];
    int i;

    while ( fgets(temp, sizeof(temp), fptr)!= NULL)
    {
        if ((i % 2) == 0 && strcmp(temp, username) == 0)
        {
            return 1;
        }
        i++;
    }
    fclose(fptr);

    return 0;
}

int adminCheck(char password[8]) // untuk mengecek password admin
{
    char adminPassword[8] = {"admin12"};
    int hasil;
    hasil = strcmp(password, adminPassword);
    if (hasil == 0)
    {
        return 1;
    }
    else if (hasil == 1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int check(char nama[20], char password[8]) // untuk mengecek username dan password
{
    char temp[255];
    int i = 1, a = 0;

    fptr = fopen("database_user.txt", "r");
    if (fptr == NULL)
    {
        a = -1;
    }

    while ( (fgets(temp, sizeof(temp), fptr)) != NULL)
    {

        if ((i % 2) == 1 && strcmp(temp, nama) == 0)
        {
            a++;
        }
        else if ((i % 2) == 0 && strcmp(temp, password) == 10)
        {
            a += 2;
        }
        i++;
        fflush(stdin);
    }
    fclose(fptr);
    return a;
}

void registrasi()
{
    struct pengenal admin;
    struct pengenal registrasiPegawai;
    fflush(stdin);

    printf("Masukkan password ADMIN: ");
    fgets(admin.password, sizeof(admin.password), stdin);
    int hasil = adminCheck(admin.password);
    system("clear||cls");
    fptr = fopen("database_user.txt", "a");
    if (hasil == 1)
    {
        printf("Password yang anda masukkan benar\n");
        printf("Masukkan username: ");
        getchar();
        scanf("%[^\n]s", registrasiPegawai.username);
        printf("Masukkan password anda: ");
        getchar();
        scanf("%[^\n]s", registrasiPegawai.password);
        fprintf(fptr, "%s\n", registrasiPegawai.username);
        fprintf(fptr, "%s\n", registrasiPegawai.password);
        fclose(fptr);
    }
    else if (hasil == -1)
    {
        printf("Password yang anda masukkan salah\n");
    }
}

void login()
{
    struct pengenal login;

    printf("Masukkan username: ");
    fgets(login.username, sizeof(login.username), stdin);
    printf("Masukkan password anda: ");
    fgets(login.password, sizeof(login.password), stdin);

    int hasilPengecekan = check(login.username, login.password);

    if (hasilPengecekan == 2)
    {
        printf("Login berhasil");
    }
    else if (hasilPengecekan == 1)
    {
        printf("Password anda salah");
    }
    else if (hasilPengecekan == 0 || hasilPengecekan == 2)
    {
        printf("Username anda salah");
    }
    else if (hasilPengecekan == -1)
    {
        printf("Anda belum membuat username dan password");
    }
    fflush(stdin);
}

int main()
{
    int pilihan; // variabel untuk memilih nilai untuk pilihan yang dilakukan

    fflush(stdin);

    printf("Selamat datang di Minimarket\n");
    printf("1. login\n");
    printf("2. Register\n");
    printf("9. exit\n");
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
        main();
        break;
    case 9:
        exit(1);
    }
    fflush(stdin);

    printf("Terimakasih sudah mencoba");

    return 0;
}