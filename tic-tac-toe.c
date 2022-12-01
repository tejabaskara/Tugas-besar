#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE *file;
char square[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int score1, score2;
int checkWin();
void drawBoard();

int main()
{
    char jawaban;
    file = fopen("Riwayat.txt", "w+");
    int player = 1, i, choice, temp;
    char mark; // X,O
    // int score1, score2;
    for (i = 1; i < 11; i++ ){
        temp = i + 48;
        square [i] = temp;
    }
    do
    {
        drawBoard();
        player = (player % 2) ? 1 : 2;
        printf("Player %d, enter the choice : ", player);
        scanf("%d", &choice);
        mark = (player == 1) ? 'X' : 'O';
        if (choice == 1 && square[1] == '1')
            square[1] = mark;
        else if (choice == 2 && square[2] == '2')
            square[2] = mark;
        else if (choice == 3 && square[3] == '3')
            square[3] = mark;
        else if (choice == 4 && square[4] == '4')
            square[4] = mark;
        else if (choice == 5 && square[5] == '5')
            square[5] = mark;
        else if (choice == 6 && square[6] == '6')
            square[6] = mark;
        else if (choice == 7 && square[7] == '7')
            square[7] = mark;
        else if (choice == 8 && square[8] == '8')
            square[8] = mark;
        else if (choice == 9 && square[9] == '9')
            square[9] = mark;

        else
        {
            printf("Invalid option !");
            player--;
            getchar();
        }
        i = checkWin();
        player++;

    } while (i == -1);

    drawBoard();
    if (i == 1)
    {
        --player;
        printf("==>Player %d won\n", player);
        if (player == 1)
        {
            score1++;
        }
        else if (player == 2)
            score2++;
    }
    else
    {
        printf("==>Game draw\n");
    }
    getchar();
    do{
        printf("Apakah ingin mengulangi permainan ?\n");
        printf("Jawab (y/n): ");
        scanf("%c", &jawaban);
        jawaban = toupper(jawaban);
        system("cls || clear");
    }while(jawaban != 'Y' && jawaban != 'N');
    if (jawaban == 'Y'){
        main();
    }else {
        printf("TERIMA KASIH SUDAH MENCOBA");
        fprintf(file,"PLAYER 1 : %d", score1);
        fprintf(file,"\tPLAYER 2 : %d", score2);
    }
    getchar();
    return 0;
}

int checkWin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

void drawBoard()
{
    printf("SKOR SEMENTARA\n");
    printf("Player 1: %d", score1);
    printf("\tPlayer 2: %d", score2);
    system("cls || clear");
    printf("\n\n\t Tic Tac Toe \n\n");
    printf("Player1 (X) - Player2 (O) \n\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", square[1], square[2], square[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", square[4], square[5], square[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", square[7], square[8], square[9]);
    printf("     |     |     \n");
}
