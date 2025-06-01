#include "../include/game_life.h"
#include "../include/hash.h"

int main(void) {
    initialize_game();
    
    char** matrix = create_matrix();
    if (!matrix) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    int num_datasets;
    char path[256];
    printf("Введите номер набора данных (1-5): ");
    if (scanf("%d", &num_datasets) != 1 || num_datasets < 1 || num_datasets > 5) {
        fprintf(stderr, "Неверный номер набора данных\n");
        destroy_matrix(matrix);
        return 1;
    }

    snprintf(path, sizeof(path), "datasets/%d.txt", num_datasets);
    
    if (setup(matrix, path)) {
        fprintf(stderr, "Ошибка загрузки данных\n");
        destroy_matrix(matrix);
        return 1;
    }

    int speed = DEFAULT_SPEED;
    int running = 1;

    while (running) {
        clear();
        print_matrix(matrix);
        refresh();

        if (handle_input(&speed)) {
            running = 0;
        }

        update(matrix);
        apply_speed(speed);
    }

    destroy_matrix(matrix);
    cleanup_game();
    return 0;
}

void initialize_game(void) {
    initscr();              // Инициализация ncurses
    cbreak();              // Отключение буферизации ввода
    noecho();              // Отключение отображения ввода
    keypad(stdscr, TRUE);  // Включение специальных клавиш
    curs_set(0);           // Скрытие курсора
    timeout(0);            // Неблокирующий ввод
}

char** create_matrix(void) {
    char** matrix = (char**)malloc(HEIGHT * sizeof(char*));
    if (!matrix) return NULL;

    for (int i = 0; i < HEIGHT; i++) {
        matrix[i] = (char*)malloc(WIDTH * sizeof(char));
        if (!matrix[i]) {
            while (--i >= 0) free(matrix[i]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void destroy_matrix(char** matrix) {
    if (matrix) {
        for (int i = 0; i < HEIGHT; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

int handle_input(int* speed) {
    int ch = getch();
    switch (ch) {
        case 'A':
        case 'a':
            *speed = (*speed > MIN_SPEED) ? *speed - SPEED_STEP : *speed;
            break;
        case 'Z':
        case 'z':
            *speed += SPEED_STEP;
            break;
        case ' ':
            return 1;
    }
    return 0;
}

void apply_speed(int speed) {
    usleep(speed * 1000);
}

void cleanup_game(void) {
    endwin();  // Завершение работы ncurses
}

// Остальные функции из оригинального кода остаются без изменений