#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


FILE *riwayat;

struct boardScore
{
    char nama[10];
    int score;
    int banyakMain;
};

int checkWin(int pilihan1, int pilihan2){
    if (pilihan1 == 1 && pilihan2 == 2)
        {
            printf("player 1 menang");
            return 1;
        }
        else if (pilihan1 == 2 && pilihan2 == 3)
        {
            printf("player 1 menang");
            return 1;
        }
        else if (pilihan1 == 3 && pilihan2 == 1)
        {
            printf("player 2 menang");
            return 2;
        }
        else if (pilihan2 == 1 && pilihan1 == 2)
        {
            printf("player 2 menang");
            return 2;
        }
        else if (pilihan2 == 2 && pilihan1 == 3)
        {
            printf("player 2 menang");
            return 2;
        }
        else if (pilihan2 == 3 && pilihan1 == 1)
        {
            printf("player 1 menang");
            return 1;
        }
        else{
            return -1;
        }
}

int main()
{
    struct boardScore player1;
    struct boardScore player2;
    player1.score = 0;
    player2.score = 0;
    player1.banyakMain = 0;
    int pilihan1, pilihan2;
    char jawaban = 'Y';
    int player;
    int w;


    printf("Masukkan nama Player 1: ");
    fgets(player1.nama, sizeof(player1.nama), stdin);
    printf("Masukkan nama Player 2: ");
    fgets(player2.nama, sizeof(player2.nama), stdin);
    system("cls||clear");

    while (jawaban == 'Y')
    {
        printf("%s", player1.nama);
        printf("GAME GUNTING BATU KERTAS\n");
        printf("1. gunting\n");
        printf("2. batu\n");
        printf("3. kertas\n");
        printf("==> ");
        scanf("%d", &pilihan1);
        system("cls||clear");
        printf("%s", player2.nama);
        printf("GAME GUNTING BATU KERTAS\n");
        printf("1. gunting\n");
        printf("2. batu\n");
        printf("3. kertas\n");
        printf("==> ");
        scanf("%d", &pilihan2);

        w = checkWin(pilihan1,pilihan2);
        
        if (w == 1)
        {
            player1.score++;
        }else if (w == 2){
            player2.score++;
        }

        getchar();
        printf("\nApakah ingin mengulang kembali? \n");
        printf("Jawab (y/n): ");
        scanf("%c", &jawaban);
        jawaban = toupper(jawaban);
        
        player1.banyakMain++;
        system("cls||clear");
    }

    
    printf("Nama: %s", player1.nama);
    printf("score :%d\n", player1.score);
    // printf("alamat data :%p\n", &player1.score);
    printf("Nama :%s", player2.nama);
    printf("Score: %d\n", player2.score);
    // printf("alamat data :%p\n", &player2.score);
    printf("banyak main: %d\n", player1.banyakMain);
    // printf("alamat data :%p\n", &player1.banyakMain);
    riwayat = fopen("a.txt", "a");
    fprintf(riwayat, "\n%s%d\n%s%d", player1.nama, player1.score, player2.nama, player2.score);
    if ((riwayat = fopen("a.txt", "r")) == NULL)
    {
        printf("error");
        exit(1);
    }
    fclose(riwayat);
    

    return 0;
}

