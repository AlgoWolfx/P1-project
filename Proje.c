#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// board size
#define ROWS 6
#define COLS 7

// cell symbols
#define EMPTY '.'
#define PLAYER1 'X'
#define PLAYER2 'O'

// how many in a row to win
#define WIN_LENGTH 4

// Board struct - keeps the game board data
typedef struct
{
    int rows;
    int cols;
    char cells[ROWS][COLS];
} Board;

// Game struct - keeps all game info
typedef struct
{
    Board board;       // the board
    int currentPlayer; // who plays now (1 or 2)
    int mode;          // 1 = human vs human, 2 = human vs machine
    int moves;
    int p1undos;
    int p2undos;
    int his[100];
} Game;

int countInDirection(Board b, int row, int col, int dRow, int dCol, char piece);
int checkWin(Board b, int row, int col, char piece);
int checkDraw(Board b);
void initBoard(Board *b);
void printBoard(Board b);
int isColumnValid(Board b, int col);
int isColumnFull(Board b, int col);
int makeMove(Board *b, int col, char piece, int *row);
void clearBuffer(void);
int showMainMenu(void);
int showModeMenu(void);
int save(Game *g);
int getHumanMove(Game g);
int getMachineMove(Game g);
int load(Game *g);
void playGame(Game *g);

// Counts the amount of times the piece appears in a direction
int countInDirection(Board b, int row, int col, int dRow, int dCol, char piece)
{
    int count = 0;
    int r = row + dRow;
    int c = col + dCol;

    while (r >= 0 && r < b.rows && c >= 0 && c < b.cols)
    {
        if (b.cells[r][c] == piece)
        {
            count++;
            r += dRow;
            c += dCol;
        }
        else
        {
            break;
        }
    }

    return count;
}

// checks after every play if it wins the game
int checkWin(Board b, int row, int col, char piece)
{
    int total;

    total = 1;
    total += countInDirection(b, row, col, 0, -1, piece);
    total += countInDirection(b, row, col, 0, 1, piece);
    if (total >= WIN_LENGTH)
    {
        return 1; // horizontal
    }

    total = 1;
    total += countInDirection(b, row, col, -1, 0, piece);
    total += countInDirection(b, row, col, 1, 0, piece);
    if (total >= WIN_LENGTH)
    {
        return 1; // vertical
    }

    total = 1;
    total += countInDirection(b, row, col, -1, -1, piece);
    total += countInDirection(b, row, col, 1, 1, piece);
    if (total >= WIN_LENGTH)
    {
        return 1; // diagonal
    }

    total = 1;
    total += countInDirection(b, row, col, -1, 1, piece);
    total += countInDirection(b, row, col, 1, -1, piece);
    if (total >= WIN_LENGTH)
    {
        return 1; // diagonal
    }

    return 0;
}

// checks Draw after every play
int checkDraw(Board b)
{
    int col;

    for (col = 0; col < b.cols; col++)
    {
        if (b.cells[0][col] == EMPTY)
        {
            return 0;
        }
    }

    return 1;
}

// Initializes the board with EMPTY
void initBoard(Board *b)
{

    b->rows = ROWS;
    b->cols = COLS;

    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            b->cells[i][j] = EMPTY;
        }
    }
}

// Prints the board, and the 2 final lines
void printBoard(Board b)
{

    int i, j;

    for (i = 0; i < b.rows; i++)
    {
        for (j = 0; j < b.cols; j++)
        {
            printf("%c ", b.cells[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < b.cols; i++)
    {
        printf("--");
    }
    printf("\n");

    for (i = 0; i < b.cols; i++)
    {
        printf("%d ", i + 1);
    }
}

// Checks if the column is between the normal values
int isColumnValid(Board b, int col)
{
    if (col < 0 || col >= b.cols)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Checks if the column is already full
int isColumnFull(Board b, int col)
{
    if (b.cells[0][col] != EMPTY)
        return 1;

    else
        return 0;
}
// Finds the lowest row, places the piece , and updates the row value
int makeMove(Board *b, int col, char piece, int *row)
{
    int i = 0;

    while (i < b->rows)
    {
        if (b->cells[i][col] == EMPTY)
        {
            i++;
        }
        else
        {
            break;
        }
    }

    b->cells[i - 1][col] = piece;
    *row = i - 1;

    return 1;
}

// clearBuffer - read characters until newline
void clearBuffer(void)
{
    while (getchar() != '\n')
        ;
}

// showMainMenu - show menu, return 1 for new game, 0 for exit
int showMainMenu(void)
{

    int i;

    do
    {
        i = -1;

        printf("\nBem-vindo ao Jogo Quatro-em-linha!\n");
        printf("Por favor digite a opcao que prentende: \n");
        printf("1 - Iniciar Novo Jogo\n");
        printf("2 - Retomar Jogo Guardado\n");
        printf("3 - Configurar Tabuleiro\n");
        printf("0 - Sair\n");

        scanf("%d", &i);

        clearBuffer();

        if (i < 0 || i > 3)
            printf("\nOpcao do menu invalida!\n");

    } while (i < 0 || i > 3);
    return i;
}

//  showModeMenu - show mode menu, return 1, 2, or 0
int showModeMenu(void)
{
    int j;

    do
    {
        j = -1;

        printf("\nPor favor digite o modo que pretende: \n");
        printf("1 - Humano x Humano\n");
        printf("2 - Humano x Maquina\n");
        printf("0 - Voltar ao menu anterior\n");

        scanf("%d", &j);

        clearBuffer();

        if (j < 0 || j > 2)
            printf("\nOpcao do menu invalida!\n");

    } while (j < 0 || j > 2);
    return j;
}

// saves the game file
int save(Game *g)
{
    FILE *f = fopen("jogo.bin", "wb");

    if(f == NULL){
        printf("\nErro ao guardar o jogo.\n");
        return 0;
    }

    size_t result = fwrite(g, sizeof(Game), 1, f);

    fclose(f);

    if(result != 1){
        printf("\nErro ao escrever os dados.\n");
    }

    printf("\nJogo guardado com sucesso.\n");
    return 1;

}



//  getHumanMove - ask player for column, validate, return column index

int getHumanMove(Game g)
{
    char text[100];
    int col;
    int valido = 0;

    while (valido == 0)
    {
        printf("\nJogador: %d - Escolha a coluna(1-%d): ", g.currentPlayer, g.board.cols);

        col = -1;
        scanf("%s", text);
        clearBuffer();

        if(strcmp(text , "guardar") == 0){
            save(&g);
            return -2;
        }
        if(strcmp(text , "anular") == 0){
            return -3;
        }
        
        col = atoi(text);
        
        col--;

        if (isColumnValid(g.board, col) != 1)
        {
            printf("\nJogada invalida! (Coluna inexistente)\n");
        }
        else if (isColumnFull(g.board, col) == 1)
        {
            printf("\nJogada invalida! (Coluna cheia)\n");
        }
        else
        {
            valido = 1;
        }
    }
    return col;
}
//  getMachineMove - pick random valid column for machine
int getMachineMove(Game g)
{
    int col;

    do
    {
        col = rand() % g.board.cols;

    } while (isColumnFull(g.board, col));

    printf("\nA Maquina jogou na coluna %d\n", col + 1);

    return col;
}



int load(Game *g){

    FILE *f = fopen("jogo.bin", "rb");

    if(f == NULL){
        return 0;
    }

    size_t result = fread(g, sizeof(Game), 1, f);

    fclose(f);

    if(result != 1){
        printf("\nErro no ficheiro guardado.\n");
        return 0;
    }
    
    return 1;
}
// playGame - main game loop

int removepiece(Board *b, int col){

    int i;
    
    for(i = 0; i < b->rows; i++){
        if(b->cells[i][col] != 0){
            b->cells[i][col] = 0;
        
            return 1;
        }
    }

}

void playGame(Game *g)
{

    int turn = 0;
    int col, row;
    int game = 1;
    int undos, lastcol, prevcol;

    printf("\nINICIO DO JOGO\n");
    printBoard(g->board);

    while (game == 1)
    {
        if (g->currentPlayer == 1)
        {
            col = getHumanMove(*g);
        }
        else
        {
            if (g->mode == 1)
            {
                col = getHumanMove(*g);
            }
            else
            {
                col = getMachineMove(*g);
            }
        }

        if(col == -2){
            break;
        }
        if(col == -3){
            if(g->moves < 2 ){
                printf("Nao ha jogadas suficientes.\n");
                continue;
            }

            if(g->currentPlayer == 1){
                undos = g->p1undos;
                g->p1undos--;
            }
            else{
                undos = g->p2undos;
                g->p2undos--;
            }

            if(undos > 0){
                lastcol = g->his[g->moves - 1];
                prevcol = g->his[g->moves - 2];
            

                removepiece(&g->board, lastcol);
                removepiece(&g->board, prevcol);

                g->moves -= 2;

                printf("Jogadas anuladas com sucesso");
            }

            
            continue;
        }
        
        g->his[g->moves] = col;
        g->moves++;
        
        
        char piece;

        if (g->currentPlayer == 1)
        {
            piece = PLAYER1;
        }
        else
        {
            piece = PLAYER2;
        }
        makeMove(&g->board, col, piece, &row);

        printBoard(g->board);

        if (checkWin(g->board, row, col, piece))
        {
            printf("\nParabens! O jogador %d ganhou!\n", g->currentPlayer);
            game = 0;

            remove("jogo.bin");
        }
        else if (checkDraw(g->board))
        {
            printf("\nO jogo terminou empatado\n");
            game = 0;

            remove("jogo.bin");
        }
        else
        {
            if (g->currentPlayer == 1)
            {
                g->currentPlayer = 2;
            }
            else
            {
                g->currentPlayer = 1;
            }
        }
    }
}

// TODO: main - program entry point
int main()
{
    Game g;
    int opt, mod;

    srand(time(NULL));

    do
    {
        opt = showMainMenu();

        if (opt == 1)
        {
            mod = showModeMenu();

            if (mod != 0)
            {
                g.mode = mod;
                g.currentPlayer = 1;
                initBoard(&g.board);

                g.moves = 0;
                g.p1undos = 2;
                g.p2undos = 2;

                playGame(&g);
            }
            else
                continue;
        }
        else if (opt == 2)
        {
            if(load(&g) == 1){
                printf("\nJogo carregado.\n");

                playGame(&g);
            }
            else{
                printf("\nErro ao carregar o jogo.\n");
            }
        }
        else if (opt == 3)
        {
            printf("Funcionalidade de configurar tabuleiro (Fase 2)...\n");
        }
    } while (opt != 0);
    return 0;
}
