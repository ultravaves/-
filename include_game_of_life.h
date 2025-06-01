#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <fcntl.h>
#endif

#define WIDTH 80
#define HEIGHT 25

// Function declarations
void print(char **matrix);
void update(char **matrix);
int setup(char **matrix, char *path);
void clear_screen(void);
int handle_input(int *speed);
void sleep_ms(int milliseconds);

#endif