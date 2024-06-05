#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char EMPTY = '*';
const char PLAYER = 'O';
const char COMPUTER = 'X';

//const int PLAYER_WIN = -1;
#define PLAYER_WIN -1
//const int COMPUTER_WIN = 1;
#define COMPUTER_WIN 1
// const int GAME_OVER = 2;
#define GAME_OVER 2
//const int GAME_CONTINUE = 0;
#define GAME_CONTINUE 0;

const int SIZE = 3;

void printBoard(int board[SIZE][SIZE]){
    for(int r = 0; r < SIZE; r++){
        for(int c = 0; c < SIZE; c++){
            int v = board[r][c];
            switch(v){
                case -1: printf("%2c",PLAYER); break;
                case 0: printf("%2c",EMPTY); break;
                case 1: printf("%2c",COMPUTER); break;
            }
        }
        printf("\n");
    }
}

int playerMove(int board[SIZE][SIZE], int r, int c){
    if (r<0 || r>=SIZE || c<0 || c>=SIZE) return 0;
    if (board[r][c]!=0) return 0;
    board[r][c] = -1;
    return 1;
}

int checkWin(int board[SIZE][SIZE],int player){
    int win = 2 * player;
    for (int r = 0; r<SIZE; r++) {
        for (int c = 0; c<SIZE; c++) {
            if (board[r][c]!=0) continue;
            int s1 = board[r][0]+board[r][1]+board[r][2];
            int s2 = board[0][c]+board[1][c]+board[2][c];
            int d1 = (r==c) ? board[0][0] + board[1][1] + board[2][2] : 0;
            int d2 = (r==2-c) ? board[0][2] + board[1][1] + board[2][0]: 0;
            if (s1==win || s2==win || d1==win || d2==win){
                board[r][c] = 1;
                return 1;
            }
        }
    }
    return 0;
}

void computerMove(int board[SIZE][SIZE]) {
    if (checkWin(board, COMPUTER_WIN)) return;
    if (checkWin(board, PLAYER_WIN)) return;
    //printf("Random move...\n");
    int count = 0;
    for (int r = 0; r<SIZE; r++)
        for (int c = 0; c<SIZE; c++)
            if (board[r][c]==0) count++;
    if (count==8 && board[1][1]==0){
        board[1][1]=1;
        return;
    }
    int mark = rand() % count;
    for (int r = 0; r<SIZE; r++) {
        for (int c = 0; c<SIZE; c++) {
            if (board[r][c]!=0) continue;
            if (mark==0) {
                board[r][c] = 1;
                return;
            }
            mark--;
        }
    }

}

int isGameOver(int board[SIZE][SIZE]){
    for (int r = 0; r<SIZE; r++) {
        int s = board[r][0]+board[r][1]+board[r][2];
        if (s==3) return COMPUTER_WIN;
        if (s==-3) return PLAYER_WIN;
    }
    for (int c = 0; c<SIZE; c++) {
        int s = board[0][c]+board[1][c]+board[2][c];
        if (s==3) return COMPUTER_WIN;
        if (s==-3) return PLAYER_WIN;
    }
    int s = board[0][0] + board[1][1] + board[2][2];
    if (s==3) return COMPUTER_WIN;
    if (s==-3) return PLAYER_WIN;
    s = board[0][2] + board[1][1] + board[2][0];
    if (s==3) return COMPUTER_WIN;
    if (s==-3) return PLAYER_WIN;
    for (int r = 0; r<SIZE; r++) {
        for (int c = 0; c<SIZE; c++) {
            if (board[r][c]==0) return GAME_CONTINUE;
        }
    }
    return GAME_OVER;
}

int handleGameOver(int board[SIZE][SIZE]){
    int gameOver = isGameOver(board);
    switch(gameOver){
        case COMPUTER_WIN:
            printf("You lose.");
            break;
        case PLAYER_WIN:
            printf("You win.");
            break;
        case GAME_OVER:
            printf("Game over.");
            break;
    }
    return gameOver;
}

int main()
{
    int board[SIZE][SIZE];
    srand(time(NULL));
    for (int r = 0; r<SIZE; r++) {
        for (int c = 0; c<SIZE; c++) {
            board[r][c]=0;
        }
    }
    while(1){
        int r,c;
        printf("row (0,1,2): ");
        scanf("%d",&r);
        printf("column (0,1,2): ");
        scanf("%d",&c);
        if (!playerMove(board, r, c)){
            printf("Invalid move. Try again...\n");
            continue;
        }
        printf("\n");
        printBoard(board);
        printf("\n");
        if (handleGameOver(board)) return 0;
        computerMove(board);
        printf("\n");
        printBoard(board);
        printf("\n");
        if (handleGameOver(board)) return 0;
    }
}

