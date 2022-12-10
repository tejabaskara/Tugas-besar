#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;

struct barang
{
    char namaBarang[20];
    int stok;
};

int checkBuff(char buff[20])
{
    // char buffer[100];
    size_t len = strlen(buff);
    if (len > 0 && buff[len - 1] == '\n')
    {
        buff[--len] = '\0';
    }
}

void checkBarang()
{

    struct barang list;
    int i = 0;
    char temp[20];

    printf("==========================================\n");
    printf("NAMA \t\t||STOK\n");
    printf("==========================================\n");
    fptr = fopen("Barang.txt", "r");
    while ((fgets(temp, sizeof(temp), fptr)) != NULL)
    {
        checkBuff(temp);
        if ((i % 2) == 0)
        {
            printf("%s\t\t||", temp);
        }
        else if ((i % 2) == 1)
        {
            printf("%s\n", temp);
        }
        i++;
    }
    fclose(fptr);
}

int main()
{
    checkBarang();
    return 0;
}