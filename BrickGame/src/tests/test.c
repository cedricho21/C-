#include <check.h>

#include "../brick_game/tetris/s21_tetris.h"

START_TEST(test_newBlock_1) {
  Block testBlock;
  newBlock(&testBlock);

  int blockFilled = 0;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (testBlock.block[i][j] == 1) {
        blockFilled = 1;
        break;
      }
    }
    if (blockFilled) {
      break;
    }
  }

  ck_assert_int_eq(testBlock.y, 0);
  ck_assert_int_eq(testBlock.x, WIDTH / 2 - 2);
  ck_assert_int_eq(blockFilled, 1);
}
END_TEST

START_TEST(test_newBlock_2) {
  Block testBlock;
  newBlock(&testBlock);

  ck_assert_int_eq(testBlock.y, 0);
  ck_assert_int_eq(testBlock.x, WIDTH / 2 - 2);
}
END_TEST

START_TEST(test_clearLines_1) {
  GameInfo_t testGame;
  initGame(&testGame);
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 1][x] = 1;
  }

  clearLines(&testGame);

  ck_assert_int_eq(testGame.score, 100);
}
END_TEST

START_TEST(test_clearLines_2) {
  GameInfo_t testGame;
  initGame(&testGame);

  clearLines(&testGame);

  ck_assert_int_eq(testGame.score, 0);
}
END_TEST

START_TEST(test_clearLines_3) {
  GameInfo_t testGame;
  initGame(&testGame);
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 1][x] = 1;
  }
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 2][x] = 1;
  }

  clearLines(&testGame);

  ck_assert_int_eq(testGame.score, 300);
}
END_TEST

START_TEST(test_clearLines_4) {
  GameInfo_t testGame;
  initGame(&testGame);
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 1][x] = 1;
  }
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 2][x] = 1;
  }
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 3][x] = 1;
  }

  clearLines(&testGame);

  ck_assert_int_eq(testGame.score, 700);
}
END_TEST

START_TEST(test_clearLines_5) {
  GameInfo_t testGame;
  initGame(&testGame);
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 1][x] = 1;
  }
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 2][x] = 1;
  }
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 3][x] = 1;
  }
  for (int x = 0; x < WIDTH; x++) {
    testGame.field[HEIGHT - 4][x] = 1;
  }

  clearLines(&testGame);

  ck_assert_int_eq(testGame.score, 1500);
}
END_TEST

START_TEST(test_checkCollision_1) {
  GameInfo_t testGame;
  initGame(&testGame);

  Block testBlock;
  newBlock(&testBlock);

  int collision = checkCollision(&testGame, &testBlock, 0, 0);

  ck_assert_int_eq(collision, 0);
}
END_TEST

START_TEST(test_checkCollision_2) {
  GameInfo_t game;
  Block block;

  initGame(&game);
  newBlock(&block);

  int y = 20;
  int x = WIDTH / 2 - BLOCK_SIZE / 2;

  int collision = checkCollision(&game, &block, y, x);

  ck_assert_int_eq(collision, 1);
}
END_TEST

START_TEST(test_checkCollision_3) {
  GameInfo_t game;
  Block block;

  initGame(&game);
  newBlock(&block);

  int y = 0;
  int x = -1;

  int collision = checkCollision(&game, &block, y, x);

  ck_assert_int_eq(collision, 1);
}
END_TEST

START_TEST(test_checkCollision_4) {
  GameInfo_t game;
  Block block;

  initGame(&game);
  newBlock(&block);
  block.block[1][1] = 1;
  game.field[1][1] = 1;

  int y = 0;
  int x = 0;

  int collision = checkCollision(&game, &block, y, x);

  ck_assert_int_eq(collision, 1);
}
END_TEST

START_TEST(test_mergeBlock) {
  GameInfo_t gameInfo;
  initGame(&gameInfo);

  Block block;
  newBlock(&block);
  block.y = 0;
  block.x = 0;

  mergeBlock(&gameInfo, &block);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (block.block[i][j] && block.y + i >= 0) {
        ck_assert_int_eq(gameInfo.field[block.y + i][block.x + j], 1);
      }
    }
  }
}

START_TEST(test_rotateBlock) {
  Block block;
  GameInfo_t gameInfo;
  initGame(&gameInfo);
  block.x = 5;
  block.y = 5;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block.block[i][j] = i * BLOCK_SIZE + j + 1;
    }
  }

  rotateBlock(&block, &gameInfo, block.y, block.x);

  int expected[BLOCK_SIZE][BLOCK_SIZE] = {
      {4, 8, 12, 16}, {3, 7, 11, 15}, {2, 6, 10, 14}, {1, 5, 9, 13}};

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      ck_assert_int_eq(block.block[i][j], expected[i][j]);
    }
  }
}
END_TEST

START_TEST(test_gameOverCheck_1) {
  GameInfo_t game;
  initGame(&game);
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      game.field[y][x] = 0;
    }
  }

  int result = gameOverCheck(&game);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_gameOverCheck_2) {
  GameInfo_t game;
  initGame(&game);
  for (int x = 0; x < WIDTH; x++) {
    game.field[0][x] = 1;
  }
  for (int y = 1; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      game.field[y][x] = 0;
    }
  }

  int result = gameOverCheck(&game);
  free_memory(&game);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_userInput_1) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  newBlock(&figure);

  userInput(Start, &game, &figure, false);

  ck_assert_int_eq(game.pause, 0);
}
END_TEST

START_TEST(test_userInput_2) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  newBlock(&figure);

  userInput(Pause, &game, &figure, false);

  ck_assert_int_eq(game.pause, 1);
}
END_TEST

START_TEST(test_userInput_3) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  newBlock(&figure);

  userInput(Terminate, &game, &figure, false);

  ck_assert_int_eq(game.pause, 0);
}
END_TEST

START_TEST(test_userInput_4) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  figure.y = 5;
  figure.x = 3;

  userInput(Left, &game, &figure, false);

  ck_assert_int_eq(figure.x, 2);
}
END_TEST

START_TEST(test_userInput_5) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  figure.y = 5;
  figure.x = 3;

  userInput(Right, &game, &figure, false);

  ck_assert_int_eq(figure.x, 4);
}
END_TEST

START_TEST(test_userInput_6) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  newBlock(&figure);

  figure.y = 5;
  figure.x = 3;

  userInput(Up, &game, &figure, false);

  ck_assert_int_ge(figure.x, 0);
  ck_assert_int_le(figure.x, WIDTH - BLOCK_SIZE);
  ck_assert_int_ge(figure.y, 0);
  ck_assert_int_le(figure.y, HEIGHT - BLOCK_SIZE);
}
END_TEST

START_TEST(test_userInput_7) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  newBlock(&figure);

  figure.y = 5;
  figure.x = 3;

  userInput(Action, &game, &figure, false);

  ck_assert_int_ge(figure.x, 0);
  ck_assert_int_le(figure.x, WIDTH - BLOCK_SIZE);
  ck_assert_int_ge(figure.y, 0);
  ck_assert_int_le(figure.y, HEIGHT - BLOCK_SIZE);
}
END_TEST

START_TEST(test_userInput_8) {
  GameInfo_t game;
  Block figure;

  initGame(&game);
  newBlock(&figure);

  figure.y = 5;
  figure.x = 3;

  userInput(Down, &game, &figure, true);

  ck_assert_int_ge(figure.y, 0);
  ck_assert_int_le(figure.y, HEIGHT - 1);
}
END_TEST

START_TEST(test_writeHighScore) {
  int high_score = 1000;

  writeHighScore(high_score);

  FILE *file = fopen("high_score_tetris.txt", "r");
  int read_high_score;
  fscanf(file, "%d", &read_high_score);
  fclose(file);

  ck_assert_int_eq(read_high_score, high_score);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("\033[1;3;5;42;31m-=CHECK TETRIS=-\033[0m");

  TCase *tс_newBlock;
  TCase *tc_checkCollision;
  TCase *tc_clearLines;
  TCase *tc_mergeBlock;
  TCase *tc_rotateBlock;
  TCase *tc_gameOver;
  TCase *tc_input;
  TCase *tc_write;

  tс_newBlock = tcase_create("newBlock");
  suite_add_tcase(s, tс_newBlock);
  tcase_add_test(tс_newBlock, test_newBlock_1);
  tcase_add_test(tс_newBlock, test_newBlock_2);

  tc_checkCollision = tcase_create("checkCollison");
  suite_add_tcase(s, tc_checkCollision);
  tcase_add_test(tc_checkCollision, test_checkCollision_1);
  tcase_add_test(tc_checkCollision, test_checkCollision_2);
  tcase_add_test(tc_checkCollision, test_checkCollision_3);
  tcase_add_test(tc_checkCollision, test_checkCollision_4);

  tc_clearLines = tcase_create("clearLines");
  suite_add_tcase(s, tc_clearLines);
  tcase_add_test(tc_clearLines, test_clearLines_1);
  tcase_add_test(tc_clearLines, test_clearLines_2);
  tcase_add_test(tc_clearLines, test_clearLines_3);
  tcase_add_test(tc_clearLines, test_clearLines_4);
  tcase_add_test(tc_clearLines, test_clearLines_5);

  tc_mergeBlock = tcase_create("mergeBlock");
  suite_add_tcase(s, tc_mergeBlock);
  tcase_add_test(tc_mergeBlock, test_mergeBlock);

  tc_rotateBlock = tcase_create("rotateBlock");
  suite_add_tcase(s, tc_rotateBlock);
  tcase_add_test(tc_rotateBlock, test_rotateBlock);

  tc_gameOver = tcase_create("gameOver");
  suite_add_tcase(s, tc_gameOver);
  tcase_add_test(tc_gameOver, test_gameOverCheck_1);
  tcase_add_test(tc_gameOver, test_gameOverCheck_2);

  tc_input = tcase_create("input");
  suite_add_tcase(s, tc_input);
  tcase_add_test(tc_input, test_userInput_1);
  tcase_add_test(tc_input, test_userInput_2);
  tcase_add_test(tc_input, test_userInput_3);
  tcase_add_test(tc_input, test_userInput_4);
  tcase_add_test(tc_input, test_userInput_5);
  tcase_add_test(tc_input, test_userInput_6);
  tcase_add_test(tc_input, test_userInput_7);
  tcase_add_test(tc_input, test_userInput_8);

  tc_write = tcase_create("writeHighScore");
  suite_add_tcase(s, tc_write);
  tcase_add_test(tc_write, test_writeHighScore);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;

  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}