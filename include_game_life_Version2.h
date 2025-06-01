#ifndef GAME_LIFE_H_
#define GAME_LIFE_H_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define DEFAULT_SPEED 100
#define MIN_SPEED 10
#define SPEED_STEP 10

// Основные функции игры
void initialize_game(void);
char** create_matrix(void);
void destroy_matrix(char** matrix);
int setup(char** matrix, const char* path);
void update(char** matrix);
void print_matrix(char** matrix);
void cleanup_game(void);

// Управление игрой
int handle_input(int* speed);
void apply_speed(int speed);

// Вспомогательные функции
int count_neighbors(char** matrix, int i, int j);
void write_matrix_to_file(char** matrix, const char* path);

#endif  // GAME_LIFE_H_