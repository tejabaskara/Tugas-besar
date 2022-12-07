#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;

struct pengenal
{
    char username[20];
    char password[8];
};

int check(char nama[20], char password[8])
{
    char temp[255];
    char const *temp1;
    int i = 1, a = 0;

    fptr = fopen("database_user.txt", "r");
    // if (fptr == NULL)
    // {
    //     printf("text not found");
    // }

    while ((temp1 = fgets(temp, sizeof(temp), fptr)) != NULL)
    {
        // printf("%d\n", i);

        // printf("%s\n", nama);
        // printf("%s\n", temp);

        if ((i % 2) == 1 && strcmp(temp1, nama) == 0)
        {
            // printf("same\n");
            a++;
        }
        else if ((i % 2) == 0 && strcmp(temp1, password) == 0)
        {
            // printf("same %d", i);
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
    fptr = fopen("database_user.txt", "w+");
    struct pengenal masuk;
    printf("Masukkan username: ");
    fgets(masuk.username, sizeof(masuk.username), stdin);
    printf("Masukkan password anda: ");
    fgets(masuk.password, sizeof(masuk.password), stdin);
    fprintf(fptr, "%s", masuk.username);
    fprintf(fptr, "%s", masuk.password);
    fclose(fptr);
    // printf("%s", masuk.username);
    // printf("%s", masuk.password);
    system("clear||cls");
    int hasilPengecekan = check(masuk.username, masuk.password);
    // printf("%d", hasilPengecekan);
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

    return 0;
}