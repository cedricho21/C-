#include "s21_tetris.h"

void free_memory(GameInfo_t *game) {
  for (int i = 0; i < HEIGHT; i++) {
    free(game->field[i]);
  }
  free(game->field);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    free(game->next[i]);
  }
  free(game->next);
}

void initGame(GameInfo_t *game) {
  game->field = (int **)malloc(HEIGHT * sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game->field[i] = (int *)malloc(WIDTH * sizeof(int));
  }
  game->next = (int **)malloc(BLOCK_SIZE * sizeof(int *));
  for (int i = 0; i < BLOCK_SIZE; i++) {
    game->next[i] = (int *)malloc(BLOCK_SIZE * sizeof(int));
  }
  game->score = 0;
  game->high_score = readHighScore();
  game->level = 1;
  game->speed = 210000000;
  game->pause = 0;
}

GameInfo_t updateCurrentState(GameInfo_t *game, int score) {
  game->score += score;
  if (game->score > game->high_score) {
    game->high_score = game->score;
    writeHighScore(score);
  }
  if (game->level < 10) game->level = game->score / 600 + 1;
  game->speed = 226000000 - game->level * 16000000;
  return *game;
}

void newBlock(Block *block) {
  int shapes[7][4][4] = {
      {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
  int blockIndex = rand() % 7;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block->block[i][j] = shapes[blockIndex][i][j];
    }
  }
  block->y = 0;
  block->x = WIDTH / 2 - 2;
}

int checkCollision(GameInfo_t *game, Block *block, int y, int x) {
  int check = 0;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (block->block[i][j]) {
        if (y + i >= HEIGHT) {
          check = 1;
          break;
        }
        if (x + j < 0 || x + j >= WIDTH) {
          check = 1;
          break;
        }
        if (game->field[y + i][x + j]) {
          check = 1;
          break;
        }
      }
    }
  }
  return check;
}

void mergeBlock(GameInfo_t *game, Block *block) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (block->block[i][j] && block->y + i >= 0) {
        game->field[block->y + i][block->x + j] = 1;
      }
    }
  }
}

void rotateBlock(Block *block, GameInfo_t *game, int y, int x) {
  int temp[BLOCK_SIZE][BLOCK_SIZE];
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      temp[i][j] = block->block[i][j];
    }
  }
  int rotated[BLOCK_SIZE][BLOCK_SIZE];
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      rotated[i][j] = temp[j][BLOCK_SIZE - 1 - i];
    }
  }
  int collision = 0;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (rotated[i][j]) {
        if (y + i >= HEIGHT || x + j < 0 || x + j >= WIDTH ||
            game->field[y + i][x + j]) {
          collision = 1;
          break;
        }
      }
    }
    if (collision) break;
  }
  if (!collision) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        block->block[i][j] = rotated[i][j];
      }
    }
  }
}

void clearLines(GameInfo_t *game) {
  int linesCleared = 0;
  int score = 0;
  for (int y = HEIGHT - 1; y >= 0; y--) {
    int lineFilled = 1;
    for (int x = 0; x < WIDTH; x++) {
      if (game->field[y][x] == 0) {
        lineFilled = 0;
        break;
      }
    }
    if (lineFilled) {
      linesCleared++;
      for (int k = y; k > 0; k--) {
        for (int x = 0; x < WIDTH; x++) {
          game->field[k][x] = game->field[k - 1][x];
        }
      }
      y++;
    }
  }
  switch (linesCleared) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
    default:
      score = 0;
      break;
  }

  *game = updateCurrentState(game, score);
}

int gameOverCheck(GameInfo_t *game) {
  int check = 0;
  for (int x = 0; x < WIDTH; x++) {
    if (game->field[0][x] == 1) {
      check = 1;
    }
  }
  return check;
}

void userInput(UserAction_t action, GameInfo_t *game, Block *figure,
               bool hold) {
  switch (action) {
    case Start:
      break;
    case Pause:
      if (game->pause == 0)
        game->pause = 1;
      else
        game->pause = 0;
      break;
    case Terminate:
      //  free_memory(game);
      break;
    case Left:
      if (!game->pause) {
        if (!checkCollision(game, figure, figure->y, figure->x - 1))
          figure->x--;
      }
      break;
    case Right:
      if (!game->pause) {
        if (!checkCollision(game, figure, figure->y, figure->x + 1))
          figure->x++;
      }
      break;
    case Up:
      if (!game->pause) {
        rotateBlock(figure, game, figure->y, figure->x);
        if (checkCollision(game, figure, figure->y, figure->x))
          rotateBlock(figure, game, figure->y, figure->x);
      }
      break;
    case Down:
      if (!game->pause) {
        if (hold) {
          while (!checkCollision(game, figure, figure->y + 1, figure->x)) {
            figure->y++;
          }
        }
      }
      break;
    case Action:
      if (!game->pause) {
        rotateBlock(figure, game, figure->y, figure->x);
        if (checkCollision(game, figure, figure->y, figure->x))
          rotateBlock(figure, game, figure->y, figure->x);
        break;
      }
    default:
      break;
  }
}

void writeHighScore(int high_score) {
  FILE *file = fopen("high_score_tetris.txt", "w");
  fprintf(file, "%d", high_score);
  fclose(file);
}

int readHighScore() {
  int high_score = 0;
  FILE *file = fopen("high_score_tetris.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}
