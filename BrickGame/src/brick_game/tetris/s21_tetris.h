#ifndef TETRIS_FUNCTIONS_H
#define TETRIS_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20
#define BLOCK_SIZE 4

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int x, y;
  int block[BLOCK_SIZE][BLOCK_SIZE];
} Block;

void free_memory(GameInfo_t *game);
void initGame(GameInfo_t *game);
GameInfo_t updateCurrentState(GameInfo_t *game, int score);
void newBlock(Block *block);
int checkCollision(GameInfo_t *game, Block *block, int y, int x);
void mergeBlock(GameInfo_t *game, Block *block);
void rotateBlock(Block *block, GameInfo_t *game, int y, int x);
void clearLines(GameInfo_t *game);
int gameOverCheck(GameInfo_t *game);
void userInput(UserAction_t action, GameInfo_t *game, Block *figure, bool hold);
void writeHighScore(int high_score);
int readHighScore();

#ifdef __cplusplus
}
#endif

#endif  // TETRIS_FUNCTIONS_H
