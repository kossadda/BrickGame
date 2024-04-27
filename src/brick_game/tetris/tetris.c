/**
 * @file tetris.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../../gui/cli/include/field_gui.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

// temp
#include "./../../gui/cli/include/fsm_gui.h"
#include "./../../gui/cli/include/objects_gui.h"

void init_game(GameInfo_t *info);
void set_high_score(GameInfo_t *info);

int main() {
  GameInfo_t info;

  init_game(&info);

  
  // init_screen();
  // print_field();

  // while(getch() != 'q') {
    
  // }
  
  // endwin();

  // return 0;
}

void game_loop() {

}

void init_game(GameInfo_t *info) {
  info->field = (int **)calloc(ROWS, sizeof(int *));
  for(int i = 0; i < ROWS; i++) {
    info->field[i] = (int *)calloc(COLS, sizeof(int));
  }

  info->score = 0;
  set_high_score(info);
  info->level = 0;
  info->speed = 1;
  info->speed = 0;
}

void next_figure() {
  srand(time(NULL));
  int blocks_count = rand() % BLOCK_CNT;
  printf("Random value = %d\n", blocks_count);
}

void set_high_score(GameInfo_t *info) {
  char *filename = "score.txt";
  char path[strlen(__FILE__) + 1];
  strcpy(path, __FILE__);
  char *last_slash_ptr = strrchr(path, '/');
  *(++last_slash_ptr) = '\0';
  char path_score[strlen(path) + strlen(filename) + 1];
  sprintf(path_score, "%s%s", path, filename);

  FILE *f_score = fopen(path_score, "rw");
  char str_score[15];

  if(fgets(str_score, 15, f_score)) {
    info->high_score = atoi(str_score);
  } else {
    info->high_score = 0;
  }

  if(f_score) {
    fclose(f_score);
  }
}