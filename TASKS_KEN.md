# Tareas de Ken - Connect Four

## Importante

**Todo el código debe estar en inglés:**
- Nombres de variables en inglés
- Comentarios en inglés
- Mensajes de error en inglés

---

## Tus Funciones

Ken, necesitas implementar estas 7 funciones:

| Función | Descripción |
|---------|-------------|
| clearBuffer() | Limpiar el buffer de entrada |
| showMainMenu() | Mostrar menú principal |
| showModeMenu() | Mostrar menú de modo de juego |
| getHumanMove() | Obtener movimiento del jugador humano |
| getMachineMove() | Obtener movimiento aleatorio para la máquina |
| playGame() | Bucle principal del juego |
| main() | Punto de entrada del programa |

---

## 1. clearBuffer()

Esta función limpia el buffer de entrada después de usar scanf.

```c
void clearBuffer(void) {
    int ch;
    // read characters until newline or end of file
    while ((ch = getchar()) != '\n' && ch != EOF);
}
```

---

## 2. showMainMenu()

Muestra el menú principal y devuelve la elección del usuario.

**Qué debe mostrar:**
```
Welcome to Connect Four!
1 - New Game
0 - Exit
Choice:
```

**Cómo implementar:**
```c
int showMainMenu(void) {
    int choice;
    int result;
    
    // print menu
    printf("\nWelcome to Connect Four!\n");
    printf("1 - New Game\n");
    printf("0 - Exit\n");
    printf("Choice: ");
    
    // loop until valid input
    while (1) {
        result = scanf("%d", &choice);
        
        // check if input was a number
        if (result != 1) {
            clearBuffer();
            printf("Please enter a number!\n");
            printf("Choice: ");
            continue;
        }
        
        // check if choice is valid
        if (choice == 0 || choice == 1) {
            return choice;
        }
        
        printf("Invalid option!\n");
        printf("Choice: ");
    }
}
```

---

## 3. showModeMenu()

Muestra el menú de selección de modo de juego.

**Qué debe mostrar:**
```
Select game mode:
1 - Human vs Human
2 - Human vs Machine
0 - Back
Choice:
```

**Cómo implementar:**
```c
int showModeMenu(void) {
    int choice;
    int result;
    
    // print mode menu
    printf("\nSelect game mode:\n");
    printf("1 - Human vs Human\n");
    printf("2 - Human vs Machine\n");
    printf("0 - Back\n");
    printf("Choice: ");
    
    // loop until valid input
    while (1) {
        result = scanf("%d", &choice);
        
        if (result != 1) {
            clearBuffer();
            printf("Please enter a number!\n");
            printf("Choice: ");
            continue;
        }
        
        // valid choices are 0, 1, or 2
        if (choice >= 0 && choice <= 2) {
            return choice;
        }
        
        printf("Invalid option!\n");
        printf("Choice: ");
    }
}
```

---

## 4. getHumanMove()

Obtiene un movimiento válido del jugador humano.

**Lo que debe hacer:**
1. Pedir al jugador que elija una columna (1-7)
2. Validar que la entrada sea un número
3. Convertir de 1-7 a 0-6 (restar 1)
4. Verificar que la columna exista
5. Verificar que la columna no esté llena
6. Si es inválido, pedir de nuevo

**Cómo implementar:**
```c
int getHumanMove(Game *g) {
    int input;
    int result;
    int col;
    
    printf("Player %d - Choose column (1-%d): ", 
           g->currentPlayer, g->board.cols);
    
    while (1) {
        result = scanf("%d", &input);
        
        // check if input is a number
        if (result != 1) {
            clearBuffer();
            printf("Please enter a number!\n");
            printf("Player %d - Choose column: ", g->currentPlayer);
            continue;
        }
        
        // convert from 1-based to 0-based
        col = input - 1;
        
        // check if column exists
        if (!isColumnValid(&g->board, col)) {
            printf("Invalid move! (Column does not exist)\n");
            printf("Player %d - Choose column: ", g->currentPlayer);
            continue;
        }
        
        // check if column is full
        if (isColumnFull(&g->board, col)) {
            printf("Invalid move! (Column is full)\n");
            printf("Player %d - Choose column: ", g->currentPlayer);
            continue;
        }
        
        return col;  // valid column
    }
}
```

---

## 5. getMachineMove()

Elige una columna aleatoria para la máquina.

**Lo que debe hacer:**
1. Encontrar todas las columnas que no están llenas
2. Elegir una aleatoriamente con rand()
3. Imprimir qué columna eligió la máquina

**Cómo implementar:**
```c
int getMachineMove(Game *g) {
    int validCols[COLS];  // array to store valid columns
    int count = 0;        // how many valid columns
    int i;
    int randomIndex;
    int selected;
    
    // find all columns that are not full
    for (i = 0; i < g->board.cols; i++) {
        if (!isColumnFull(&g->board, i)) {
            validCols[count] = i;
            count++;
        }
    }
    
    // pick random column from valid ones
    randomIndex = rand() % count;
    selected = validCols[randomIndex];
    
    printf("Machine chose column %d.\n", selected + 1);
    
    return selected;
}
```

---

## 6. playGame()

El bucle principal del juego.

**Algoritmo:**
1. Inicializar el tablero
2. Establecer currentPlayer = 1
3. Bucle hasta que termine el juego:
   - Imprimir el tablero
   - Obtener movimiento (humano o máquina)
   - Realizar el movimiento
   - Verificar victoria → imprimir ganador, salir
   - Verificar empate → imprimir empate, salir
   - Cambiar de jugador

**Cómo implementar:**
```c
void playGame(Game *g) {
    int gameOver = 0;
    int col;
    int row;
    char piece;
    
    // initialize board
    initBoard(&g->board);
    g->currentPlayer = 1;
    
    // game loop
    while (!gameOver) {
        // print current board
        printBoard(&g->board);
        
        // determine current piece
        if (g->currentPlayer == 1) {
            piece = PLAYER1;
        } else {
            piece = PLAYER2;
        }
        
        // get move based on mode and player
        if (g->currentPlayer == 1 || g->mode == 1) {
            // human player
            col = getHumanMove(g);
        } else {
            // machine player
            col = getMachineMove(g);
        }
        
        // make the move
        makeMove(&g->board, col, piece, &row);
        
        // check for win
        if (checkWin(&g->board, row, col, piece)) {
            printBoard(&g->board);
            
            if (g->mode == 2 && g->currentPlayer == 2) {
                printf("Machine wins!\n");
            } else {
                printf("Player %d wins!\n", g->currentPlayer);
            }
            gameOver = 1;
            continue;
        }
        
        // check for draw
        if (checkDraw(&g->board)) {
            printBoard(&g->board);
            printf("Draw! Board is full.\n");
            gameOver = 1;
            continue;
        }
        
        // switch player
        if (g->currentPlayer == 1) {
            g->currentPlayer = 2;
        } else {
            g->currentPlayer = 1;
        }
    }
}
```

---

## 7. main()

El punto de entrada del programa.

**Algoritmo:**
1. Inicializar generador de números aleatorios
2. Bucle del menú principal:
   - Mostrar menú principal
   - Si elige salir (0), terminar
   - Si elige nuevo juego (1), mostrar menú de modo
   - Si elige modo, crear juego y jugar

**Cómo implementar:**
```c
int main(void) {
    int running = 1;
    int menuChoice;
    int modeChoice;
    Game game;
    
    // seed random number generator
    srand(time(NULL));
    
    // main menu loop
    while (running) {
        menuChoice = showMainMenu();
        
        if (menuChoice == 0) {
            // exit
            printf("Thanks for playing!\n");
            running = 0;
        } else if (menuChoice == 1) {
            // new game
            modeChoice = showModeMenu();
            
            if (modeChoice == 0) {
                // go back
                continue;
            }
            
            // start game
            game.mode = modeChoice;
            playGame(&game);
        }
    }
    
    return 0;
}
```

---

## Mensajes de Error (en inglés)

| Situación | Mensaje |
|-----------|---------|
| Opción inválida | "Invalid option!" |
| No es un número | "Please enter a number!" |
| Columna no existe | "Invalid move! (Column does not exist)" |
| Columna llena | "Invalid move! (Column is full)" |
| Jugador gana | "Player X wins!" |
| Máquina gana | "Machine wins!" |
| Empate | "Draw! Board is full." |

---

## Recordatorio

- Todo el código en **inglés**
- Comentarios en **inglés**
- Nombres de variables en **inglés**

¡Buena suerte Ken!

