# Tarefas do Tavez - Connect Four

## Importante

**Todo o código deve estar em inglês:**
- Nomes de variáveis em inglês
- Comentários em inglês
- Mensagens em inglês

---

## As Tuas Funções

Tavez, precisas de implementar estas 5 funções:

| Função | Descrição |
|--------|-----------|
| initBoard() | Inicializar o tabuleiro |
| printBoard() | Imprimir o tabuleiro |
| isColumnValid() | Verificar se a coluna é válida |
| isColumnFull() | Verificar se a coluna está cheia |
| makeMove() | Colocar uma peça no tabuleiro |

---

## 1. initBoard()

Esta função inicializa o tabuleiro com células vazias.

**O que deve fazer:**
1. Definir rows = ROWS (6)
2. Definir cols = COLS (7)
3. Preencher todas as células com EMPTY ('.')

**Como implementar:**
```c
void initBoard(Board *b) {
    int row;
    int col;
    
    // set board dimensions
    b->rows = ROWS;
    b->cols = COLS;
    
    // fill all cells with empty
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            b->cells[row][col] = EMPTY;
        }
    }
}
```

---

## 2. printBoard()

Esta função imprime o tabuleiro no ecrã.

**Exemplo de saída:**
```
   1  2  3  4  5  6  7
  +--+--+--+--+--+--+--+
  |. |. |. |. |. |. |. |
  |. |. |. |. |. |. |. |
  |. |. |. |X |. |. |. |
  |. |. |O |X |. |. |. |
  |. |. |X |O |O |. |. |
  |X |O |X |O |X |. |. |
  +--+--+--+--+--+--+--+
```

**Como implementar:**
```c
void printBoard(Board *b) {
    int row;
    int col;
    
    printf("\n");
    
    // print column numbers
    printf("   ");
    for (col = 0; col < b->cols; col++) {
        printf("%d  ", col + 1);
    }
    printf("\n");
    
    // print top border
    printf("  +");
    for (col = 0; col < b->cols; col++) {
        printf("--+");
    }
    printf("\n");
    
    // print each row
    for (row = 0; row < b->rows; row++) {
        printf("  |");
        for (col = 0; col < b->cols; col++) {
            printf("%c |", b->cells[row][col]);
        }
        printf("\n");
    }
    
    // print bottom border
    printf("  +");
    for (col = 0; col < b->cols; col++) {
        printf("--+");
    }
    printf("\n\n");
}
```

---

## 3. isColumnValid()

Esta função verifica se o número da coluna é válido.

**O que deve fazer:**
- Verificar se col >= 0 E col < cols
- Retornar 1 se válido
- Retornar 0 se inválido

**Como implementar:**
```c
int isColumnValid(Board *b, int col) {
    // check if column is in range
    if (col >= 0 && col < b->cols) {
        return 1;  // valid
    }
    return 0;  // invalid
}
```

---

## 4. isColumnFull()

Esta função verifica se uma coluna está cheia.

**O que deve fazer:**
- Verificar se a célula do topo (linha 0) não está vazia
- Se não está vazia, a coluna está cheia

**Como implementar:**
```c
int isColumnFull(Board *b, int col) {
    // check if top cell is not empty
    if (b->cells[0][col] != EMPTY) {
        return 1;  // column is full
    }
    return 0;  // column has space
}
```

---

## 5. makeMove()

Esta função coloca uma peça numa coluna (efeito de gravidade).

**O que deve fazer:**
1. Começar da linha inferior (ROWS-1)
2. Subir até encontrar uma célula vazia
3. Colocar a peça nessa célula
4. Guardar o número da linha em *row
5. Retornar 1 se sucesso, 0 se coluna cheia

**Como implementar:**
```c
int makeMove(Board *b, int col, char piece, int *row) {
    int r;
    
    // start from bottom, go up
    for (r = b->rows - 1; r >= 0; r--) {
        // found empty cell
        if (b->cells[r][col] == EMPTY) {
            b->cells[r][col] = piece;  // place piece
            *row = r;                   // save row number
            return 1;                   // success
        }
    }
    
    return 0;  // column was full
}
```

---

## Como Funciona a Gravidade

No Connect Four, as peças caem para a posição mais baixa disponível:

```
Antes:           Depois de colocar X na coluna 3:
|. |. |. |       |. |. |. |
|. |. |. |       |. |. |. |
|. |. |. |   ->  |. |. |. |
|. |. |. |       |. |. |. |
|. |. |. |       |. |. |. |
|. |. |O |       |. |. |X |  <- X cai até ao fundo
```

Se já houver peças:
```
Antes:           Depois de colocar X na coluna 3:
|. |. |. |       |. |. |. |
|. |. |. |       |. |. |. |
|. |. |. |   ->  |. |. |. |
|. |. |. |       |. |. |X |  <- X para em cima do O
|. |. |O |       |. |. |O |
```

---

## Constantes Disponíveis

Podes usar estas constantes no teu código:

```c
#define ROWS 6        // número de linhas
#define COLS 7        // número de colunas
#define EMPTY '.'     // célula vazia
#define PLAYER1 'X'   // peça do jogador 1
#define PLAYER2 'O'   // peça do jogador 2
```

---

## Estrutura Board

Esta é a estrutura que vais usar:

```c
typedef struct {
    int rows;                // número de linhas
    int cols;                // número de colunas
    char cells[ROWS][COLS];  // células do tabuleiro
} Board;
```

Para aceder aos elementos:
- `b->rows` - número de linhas
- `b->cols` - número de colunas
- `b->cells[row][col]` - célula na posição (row, col)

---

## Lembrete

- Todo o código em **inglês**
- Comentários em **inglês**
- Nomes de variáveis em **inglês**

Boa sorte Tavez!

