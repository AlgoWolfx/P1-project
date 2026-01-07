#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int rows;               // number of rows
    int cols;               // number of columns
    char cells[ROWS][COLS]; // the board cells
} Board;

// Game struct - keeps all game info
typedef struct
{
    Board board;       // the board
    int currentPlayer; // who plays now (1 or 2)
    int mode;          // 1 = human vs human, 2 = human vs machine
} Game;

// Yigit's functions (game logic)
int countInDirection(Board *b, int row, int col, int dRow, int dCol, char piece);
int checkWin(Board *b, int row, int col, char piece);
int checkDraw(Board *b);

// Tavez's functions (board)
void initBoard(Board *b);
void printBoard(Board *b);
int isColumnValid(Board *b, int col);
int isColumnFull(Board *b, int col);
int makeMove(Board *b, int col, char piece, int *row);

// Ken's functions (menu and game)
void clearBuffer(void);
int showMainMenu(void);
int showModeMenu(void);
int getHumanMove(Game *g);
int getMachineMove(Game *g);
void playGame(Game *g);

/*
 * countInDirection - counts pieces in one direction
 *
 * b = pointer to board
 * row, col = starting position
 * dRow, dCol = direction to check (like -1,0 means go up)
 * piece = what piece to count ('X' or 'O')
 *
 * returns: how many same pieces in that direction
 */
int countInDirection(Board *b, int row, int col, int dRow, int dCol, char piece)
{
    int count = 0;
    int r = row + dRow; // start from next cell
    int c = col + dCol;

    // keep going while inside board and same piece
    while (r >= 0 && r < b->rows && c >= 0 && c < b->cols)
    {
        if (b->cells[r][c] == piece)
        {
            count++;
            r = r + dRow; // move to next cell
            c = c + dCol;
        }
        else
        {
            break; // different piece, stop counting
        }
    }

    return count;
}

/*
 * checkWin - checks if player won after their move
 *
 * b = pointer to board
 * row, col = where the piece was placed
 * piece = the piece that was placed
 *
 * returns: 1 if win, 0 if no win
 */
int checkWin(Board *b, int row, int col, char piece)
{
    int total;

    // check horizontal (left + right + 1)
    total = 1;
    total = total + countInDirection(b, row, col, 0, -1, piece); // left
    total = total + countInDirection(b, row, col, 0, 1, piece);  // right
    if (total >= WIN_LENGTH)
    {
        return 1; // horizontal win!
    }

    // check vertical (up + down + 1)
    total = 1;
    total = total + countInDirection(b, row, col, -1, 0, piece); // up
    total = total + countInDirection(b, row, col, 1, 0, piece);  // down
    if (total >= WIN_LENGTH)
    {
        return 1; // vertical win!
    }

    // check diagonal \ (top-left + bottom-right + 1)
    total = 1;
    total = total + countInDirection(b, row, col, -1, -1, piece); // top-left
    total = total + countInDirection(b, row, col, 1, 1, piece);   // bottom-right
    if (total >= WIN_LENGTH)
    {
        return 1; // diagonal win!
    }

    // check diagonal / (top-right + bottom-left + 1)
    total = 1;
    total = total + countInDirection(b, row, col, -1, 1, piece); // top-right
    total = total + countInDirection(b, row, col, 1, -1, piece); // bottom-left
    if (total >= WIN_LENGTH)
    {
        return 1; // diagonal win!
    }

    return 0; // no win yet
}

/*
 * checkDraw - checks if board is full (draw)
 *
 * b = pointer to board
 *
 * returns: 1 if draw (board full), 0 if not full
 */
int checkDraw(Board *b)
{
    int col;

    // check top row - if any cell empty, not a draw
    for (col = 0; col < b->cols; col++)
    {
        if (b->cells[0][col] == EMPTY)
        {
            return 0; // found empty cell, not draw
        }
    }

    return 1; // all top cells full = draw
}

// ============ TAVEZ - BOARD FUNCTIONS ============

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
void printBoard(Board *b)
{

    int i, j;
    int rows, cols;

    rows = b->rows;
    cols = b->cols;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%c ", b->cells[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < cols; i++)
    {
        printf("--");
    }
    printf("\n");

    for (i = 0; i < cols; i++)
    {
        printf("%d ", i + 1);
    }
}

// Checks if the column is between the normal values
int isColumnValid(Board *b, int col)
{
    int cols = b->cols;
    if (col < 0 || col > cols - 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Checks if the column is already full
int isColumnFull(Board *b, int col)
{

    if (b->cells[0][col] != EMPTY)
        return 1;

    return 0;
}

// Finds the lowest row, places the piece , and updates the row value
int makeMove(Board *b, int col, char piece, int *row)
{
    int i = 0;

    do
    {
        i++;
    } while (i < b->rows && b->cells[i][col] == EMPTY);

    b->cells[i - 1][col] = piece;
    *row = (i - 1);

    return 1;
}

// ============ KEN - MENU AND GAME FUNCTIONS ============

// TODO: clearBuffer - read characters until newline or EOF
void clearBuffer(void)
{
    while (getchar() != '\n')
        ;
}

// TODO: showMainMenu - show menu, return 1 for new game, 0 for exit
int showMainMenu(void)
{

    int i;

    do
    {
        i = -1;

        printf("Bem-vindo ao Jogo Quatro-em-linha!\n");
        printf("Por favor digite a opção que prentede: \n");
        printf("1 - Iniciar Novo Jogo\n");
        printf("2 - Retomar Jogo Guardado\n");
        printf("3 - Configurar Tabuleiro\n");
        printf("0 - Sair\n");

        scanf("%d", &i);

        clearBuffer();

        if (i < 0 || i > 3)
            printf("Opção do menu inválida!");

    } while (i < 0 || i > 3);
    return i;
}

// TODO: showModeMenu - show mode menu, return 1, 2, or 0
int showModeMenu(void)
{
    int j;

    do
    {
        j = -1;

        printf("Por favor digite o modo que pretende: \n");
        printf("1 - Humano x Humano\n");
        printf("2 - Humano x Máquina\n");
        printf("0 - Voltar ao menu anterior\n");

        scanf("%d", &j);

        clearBuffer();

        if (j < 0 || j > 2)
            printf("\nOpção do menu inválida!");

    } while (j < 0 || j > 2);
    return j;
}

// TODO: getHumanMove - ask player for column, validate, return column index

int getHumanMove(Game *g)
{
    int col;
    int input;

    do
    {
        printf("\nJogador: %d - Escolha a coluna(1-%d) ", g->currentPlayer, g->board.cols);

        input = scanf("%d", &col);
        clearBuffer();

        if (input != 1)
        {
            printf("\nEscreva um número inteiro positivo!");
            continue;
        }
        col--;

        if (isColumnValid(&g->board, col) != 1)
        {
            printf("\nJogada inválida! (Coluna inexistente)\n");
            continue;
        }
        if (isColumnFull(&g->board, col) == 1)
        {
            printf("Jogada inválida! (Coluna cheia)\n");
            continue;
        }
        return col;

    } while (1);
}
// TODO: getMachineMove - pick random valid column for machine
int getMachineMove(Game *g)
{
    int col;

    do
    {
        col = rand() % g->board.cols;

    } while (isColumnFull(&g->board, col));

    printf("A Maquina jogou na coluna %d\n", col + 1);

    return col;
}

// TODO: playGame - main game loop

void playGame(Game *g)
{

    int turn = 0;
    int col, row;
    int game = 1;

    printf("INICIO DO JOGO");
    printBoard(&g->board);

    while (game == 1)
    {
        if (g->currentPlayer == 1)
        {
            col = getHumanMove(g);
        }
        else
        {
            if (g->mode == 1)
            {
                col = getHumanMove(g);
            }
            else
            {   
                col = getMachineMove(g);
            }
        }

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

        printBoard(&g->board);

        if (checkWin(&g->board, row, col, piece))
        {
            printf("Parabens! O jogador %d ganhou!\n", g->currentPlayer);
            game = 0;
        }
        else if (checkDraw(&g->board))
        {
            printf("O jogo terminou empatado");
            game = 0;
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
int main(){
    Game game;
    int opcao;

    do{
        opcao = showMainMenu();

        if(opcao == 1){
            int modo = showModeMenu();

            if(modo != 0){
                game.mode = modo;
                game.currentPlayer = 1;
                initBoard(&game.board);

                playGame(&game);
            }
        }
        else if (opcao == 2) {
            printf("Funcionalidade de retomar jogo (Fase 2)...\n");
        }
        else if (opcao == 3) {
            printf("Funcionalidade de configurar tabuleiro (Fase 2)...\n");
        }
    }while(opcao != 0);
return 0;
}
