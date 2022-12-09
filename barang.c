#include <stdio.h>
#include <stdlib.h>

FILE *fptr;

struct barang
{
    char namaBarang[20];
    int stok;
};


void checkBarang(){

    struct barang list;
    int i = 0;
    char temp1 [20];
    char temp [20];

    fptr = fopen("Barang.txt", "r");
    while ((temp1 = fgets(temp, sizeof(temp), fptr)) != NULL)
    {
        if ((i % 2) == 1)
        {
            list.namaBarang = temp1;
        }
        else if ((i % 2) == 0)
        {
            a += 2;
        }
        i++;
    }
}



int main(){

}