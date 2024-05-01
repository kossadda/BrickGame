/**
 * @file colors_gui.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-05-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../include/common_gui.h"

void color_attribut(int cell, int mode) {
  switch (cell) {
  case RED:
    (mode) ? attron(COLOR_PAIR(RED)) : attroff(COLOR_PAIR(RED));
    break;
  case ORANGE:
    (mode) ? attron(COLOR_PAIR(ORANGE)) : attroff(COLOR_PAIR(ORANGE));
    break;
  case YELLOW:
    (mode) ? attron(COLOR_PAIR(YELLOW)) : attroff(COLOR_PAIR(YELLOW));
    break;
  case GREEN:
    (mode) ? attron(COLOR_PAIR(GREEN)) : attroff(COLOR_PAIR(GREEN));
    break;
  case PURPLE:
    (mode) ? attron(COLOR_PAIR(PURPLE)) : attroff(COLOR_PAIR(PURPLE));
    break;
  case BLUE:
    (mode) ? attron(COLOR_PAIR(BLUE)) : attroff(COLOR_PAIR(BLUE));
    break;
  case PINK:
    (mode) ? attron(COLOR_PAIR(PINK)) : attroff(COLOR_PAIR(PINK));
  }
}

void change_theme(short theme) {
  bkgd(COLOR_PAIR(theme));

  init_pair(RED, COLOR_RED, theme);
  init_pair(ORANGE, COLOR_ORANGE, theme);
  init_pair(YELLOW, COLOR_YELLOW, theme);
  init_pair(PINK, COLOR_PINK, theme);
  init_pair(GREEN, COLOR_GREEN, theme);
  init_pair(BLUE, COLOR_BLUE, theme);
  init_pair(PURPLE, COLOR_MAGENTA, theme);
}