#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// read
// cek di dataabase apakah ada yang sama
//

struct member
{
    int noMember;
    char nama[100];
    char noKtp[16];
    char noTelp[12];
};

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

int main()
{
    struct member masuk;
    int hasil;

    printf("masukkan nama: ");
    scanf("%[^\n]", masuk.nama);
    fflush(stdin);
    getchar();
    printf("Masukkan No KTP: ");
    inputKTP(masuk.noKtp);
    printf("Masukkan No Telp: ");
    inputTelp(masuk.noTelp);
    masuk.noMember = inputNomor();
    hasil = cekKtp(masuk.noKtp);
    if (hasil == 1)
    {
        system("clear||cls");
        printf("Nomor KTP sudah pernah dipakai\n");
        main();
    }
    else
    {
        FILE *tambahMember = fopen("member.txt", "a+");
        fprintf(tambahMember, "%d,%s,%s,%s\n", masuk.noMember, masuk.nama, masuk.noKtp, masuk.noTelp);
        fclose(tambahMember);
    }
}