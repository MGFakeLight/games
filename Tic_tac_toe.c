#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define you 'O'
#define ai 'X'

char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
typedef struct position
{
    int x;
    int y;
}position;

position player={0,0};

int is_empty(int a,int b)
{
    return board[a][b]==' '?  1:0;
}


void printboard(void)
{
    printf("您是'%c'\t电脑是'%c'\n",you,ai);

    printf("   0   1   2\n");
    for(int i=0;i<3;i++)
    {
        printf("%d ",i);
        for(int j=0;j<3;j++)
        {
            printf(" %c ",board[i][j]);
            if(j<2) printf("|");
        }
        putchar('\n');
        if(i<2) printf("  ——-|—-—|—-—\n");
    }
}



void print_and_input(void)
{
    printboard();
    printf("请输入下一步的坐标(用空格隔开):");
    scanf("%d %d",&player.x,&player.y);
    while(player.x<0 || player.x>2 || player.y<0 || player.y>2 || is_empty(player.x,player.y)==0)
    {
        printf("非法输入，请重新输入坐标:");
        scanf("%d %d",&player.x,&player.y);
    }
    board[player.x][player.y]='O';
}


int is_win(char c)
{
    for(int column=0;column<3;column++)
    {
        if(board[0][column]==c && board[1][column]==c && board[2][column]==c) return 1;
    }
    for(int line=0;line<3;line++)
    {
        if(board[line][0]==c && board[line][1]==c && board[line][2]==c) return 1;
    }
    if(board[0][0]==c && board[1][1]==c && board[2][2]==c) return 1;
    if(board[2][0]==c && board[1][1]==c && board[0][2]==c) return 1;
    return 0;
}



int can_left(void)
{
    if(is_win(you)) 
    {
        printboard();
        printf("你赢了，你真棒!\n");
        return 0;
    }

    if(is_win(ai)) 
    {
        printboard();
        printf("你输了，到底谁是人机?\n");
        return 0;
    }

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ') return 1;
        }
    }
    
    return 0;
}


int evaluate() 
{

    if (is_win('X')) return 10;

    if (is_win('O')) return -10;

    return 0;
}

int minimax(int depth, int isMaximizing, int alpha, int beta) 
{
    int score = evaluate();

    if (score == 10 || score == -10) return score;
    if (!can_left()) return 0;

    if (isMaximizing) 
    {
        int best = -1000;
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                if (board[i][j] == ' ') 
                {
                    board[i][j] = 'X';
                    best = (best > minimax(depth + 1, 0, alpha, beta)) ? best : minimax(depth + 1, 0, alpha, beta);
                    board[i][j] = ' ';

                    alpha = (alpha > best) ? alpha : best;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    } 
    else 
    {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) 
            {
                if (board[i][j] == ' ') 
                {
                    board[i][j] = 'O';
                    best = (best < minimax(depth + 1, 1, alpha, beta)) ? best : minimax(depth + 1, 1, alpha, beta);
                    board[i][j] = ' ';

                    beta = (beta < best) ? beta : best;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

void ai_round(char c) 
{
    int bestVal = -1000;
    int moveX = -1, moveY = -1;

    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (board[i][j] == ' ') 
            {
                board[i][j] = c;
                int moveVal = minimax(0, 0, -1000, 1000);
                board[i][j] = ' ';

                if (moveVal > bestVal) 
                {
                    bestVal = moveVal;
                    moveX = i;
                    moveY = j;
                }
            }
        }
    }

    if (moveX == -1 || moveY == -1) 
    {
        printboard();
        printf("平局\n");
        return;
    }

    board[moveX][moveY] = c;
    player.x=moveX;
    player.y=moveY;
    printf("\nAI moved to (%d %d)\n\n", moveX, moveY);
}




int main()
{
    while(can_left())
    {
        print_and_input();
        ai_round(ai);
        //printf("\nAI moved to (%d,%d)\n\n", player.x, player.y);
    }
    printf("game over!");
    return 0;
}