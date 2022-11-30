#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

char square[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int checkWin();
void board();

int main()
{
    int player = 1;
    int i, pilihan;
    char mark;
    do
    {
        board();
        player = (player % 2) ? 1 : 2;
        printf("player %d, masukkan pilihan: ", player);
        scanf("%d", &pilihan);
        if (pilihan == 1 && square[1] == '1')
            square[1] = mark;
        else if (pilihan == 2 && square[2] == '2')
            square[2] = mark;
        else if (pilihan == 3 && square[3] == '3')
            square[3] = mark;
        else if (pilihan == 4 && square[4] == '4')
            square[4] = mark;
        else if (pilihan == 5 && square[5] == '5')
            square[5] = mark;
        else if (pilihan == 6 && square[6] == '6')
            square[6] = mark;
        else if (pilihan == 7 && square[7] == '7')
            square[7] = mark;
        else if (pilihan == 8 && square[8] == '8')
            square[8] = mark;
        else if (pilihan == 9 && square[9] == '9')
            square[9] = mark;
        else
        {
            printf("invalid");
            player--;
            getchar();
        }
        i = checkWin();
        player++;

    } while (i == -1);

    board();
}
int checkWin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[7] && square[7] == square[1])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] !=  '1' && square[2] != '2' && square[3] != '3' && square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

void board(){
    system ("cls || clear");
    printf("Tic Tac Toe\n\n");
    printf()
}