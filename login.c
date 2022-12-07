#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr; //file pointer sebagai alat yang digunakan untuk membuka dan mengubah database yang berupa file text

struct pengenal //untuk membuat variabel menjadi lebih mudah untuk dimengerti
{
    char username[20];
    char password[8];
};


int login(){

}

int registrasi(){

}

int adminCheck(char password[8]) //untuk mengecek password admin
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

int check(char nama[20], char password[8])// untuk mengecek username dan password 
{
    char temp[255];
    char const *temp1;
    int i = 1, a = 0;

    fptr = fopen("database_user.txt", "r");
    if (fptr == NULL)
    {
        a = -1;
    }

    while ((temp1 = fgets(temp, sizeof(temp), fptr)) != NULL)
    {
        if ((i % 2) == 1 && strcmp(temp1, nama) == 0)
        {
            a++;
        }
        else if ((i % 2) == 0 && strcmp(temp1, password) == 0)
        {
            a += 2;
        }
        else
        {
            printf("username not found");
        }
        i++;
    }
    fclose(fptr);
    return a;
}

int main()
{
    struct pengenal masuk; //nama  struct untuk username dan password yang akan dimasukkan
    struct pengenal admin; //nama struct untuk admin
    struct pengenal cek; //nama struct untuk mengecek password

    int pilihan; // variabel untuk memilih nilai untuk pilihan yang dilakukan

    printf("Selamat datang di Minimarket\n");
    printf("1. login\n");
    printf("2. Register\n");
    printf("9. exit\n");
    scanf("%d", &pilihan);

    system("clear||cls");
    getchar();
    switch (pilihan)
    {
    case 1:
        printf("Masukkan username: ");
        fgets(masuk.username, sizeof(masuk.username), stdin);
        printf("Masukkan password anda: ");
        fgets(masuk.password, sizeof(masuk.password), stdin);
        int hasilPengecekan = check(masuk.username, masuk.password);
        if (hasilPengecekan == 3)
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
        break;
    case 2:
        printf("Masukkan password ADMIN: ");
        fgets(admin.password, sizeof(admin.password), stdin);
        int hasil = adminCheck(admin.password);
        system("clear||cls");
        fptr = fopen("database_user.txt", "a");
        if (hasil == 1)
        {
            getchar();
            printf("Password yang anda masukkan benar\n");
            printf("Masukkan username: ");
            fgets(masuk.username, sizeof(masuk.username), stdin);
            printf("Masukkan password anda: ");
            fgets(masuk.password, sizeof(masuk.password), stdin);
            // printf("Konfirmasi password anda: ");
            // fgets(cek.password, sizeof(cek.password), stdin);
            
            // hasil
            // while (strcmp(cek.password, masuk.password) == 0)
            // {
            //     printf("Konfirmasi password anda: ");
            //    fgets(cek.password, sizeof(cek.password), stdin);
            // }
            // if (strcmp(cek.password, masuk.password) == 0)
            // {
            //     fprintf(fptr, "%s", masuk.username);
            //     fprintf(fptr, "%s", masuk.password);
            // }
            // else if (strcmp(cek.password, masuk.password) == 0)
            // {
            //     printf("Konfirmasi password anda salah");
            //     printf("Silahkan ulangi lagi");
            // }
            fprintf(fptr, "%s", masuk.username);
            fprintf(fptr, "%s", masuk.password);
        }
        else if (hasil == -1)
        {
            printf("Password yang anda masukkan salah\n");
        }
        break;
    case 3:
        exit(1);
    }

    printf("Terimakasih sudah mencoba");

    return 0;
}