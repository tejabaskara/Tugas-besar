#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct Mahasiswa
{
    char nama[20];
    int nilai;
};

char huruf_ulang[1];
void search();
void quit();

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

void main()
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
