# Connect Four - Project Status

## Point Distribution

| Feature | Points |
|---------|--------|
| Base Requirements | 11 |
| Save/Load | 2.5 |
| Undo | 2.5 |
| Custom Board Size | 1.5 |
| Dynamic Memory (Bonus) | 1.5 |
| Technical Report | 2.5 |
| **TOTAL** | **21.5** |

---

## Yigit's Part (Data Structures + Game Logic)

### Completed

- [x] Constants (ROWS, COLS, EMPTY, PLAYER1, PLAYER2, WIN_LENGTH)
- [x] Board struct definition
- [x] Game struct definition
- [x] countInDirection() function
- [x] checkWin() function
- [x] checkDraw() function

---

## Tavez's Part (Board Functions)

### To Do

- [ ] initBoard() - Initialize board with empty cells
- [ ] printBoard() - Display board on screen
- [ ] isColumnValid() - Check if column number is valid
- [ ] isColumnFull() - Check if column is full
- [ ] makeMove() - Drop piece into column (gravity effect)

---

## Ken's Part (Menu + Game Loop)

### To Do

- [ ] clearBuffer() - Clear input buffer
- [ ] showMainMenu() - Display main menu
- [ ] showModeMenu() - Display game mode menu
- [ ] getHumanMove() - Get move from human player
- [ ] getMachineMove() - Get random move for machine
- [ ] playGame() - Main game loop
- [ ] main() - Program entry point

---

## Extra Features

### Save/Load (2.5 points)

- [ ] Save game when player types "guardar"
- [ ] Add "Resume Saved Game" option to main menu
- [ ] Load game from file
- [ ] Delete save file when game ends

### Undo (2.5 points)

- [ ] Undo last 2 moves when player types "anular"
- [ ] Each player has 2 undo chances
- [ ] Keep move history

### Custom Board Size (1.5 points)

- [ ] Add "Configure Board" option to main menu
- [ ] Allow custom rows and columns
- [ ] Minimum 6 rows and 7 columns

### Dynamic Memory - Bonus (1.5 points)

- [ ] Use malloc/calloc for board
- [ ] Free all memory before exit
- [ ] No memory leaks

---

## Technical Report (2.5 points)

- [ ] Technical decisions documentation
- [ ] AI assistance documentation
- [ ] Data structures and algorithms used
- [ ] Compilation and execution instructions

---

## Project Files

| File | Description | Status |
|------|-------------|--------|
| proje.c | Main source code | In Progress |
| README.md | Project description | Done |
| TASKS_KEN.md | Ken's tasks (Spanish) | Done |
| TASKS_TAVEZ.md | Tavez's tasks (Portuguese) | Done |
| PROJECT_STATUS.md | This file | Done |
