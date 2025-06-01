#include "../include/game_of_life.h"

int main() {
    // Allocate memory for the matrix
    char **matrix = (char **)malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        matrix[i] = (char *)malloc(WIDTH * sizeof(char));
    }

    int num_datasets;
    printf("Input number of datasets (1-5): ");
    scanf("%d", &num_datasets);
    
    if (num_datasets < 1 || num_datasets > 5) {
        printf("Invalid dataset number\n");
        return 1;
    }

    char path[256];
    snprintf(path, sizeof(path), "datasets/%d.txt", num_datasets);

    if (setup(matrix, path)) {
        printf("Error loading dataset\n");
        return 1;
    }

    int speed = 100; // Initial speed in milliseconds
    int running = 1;

    clear_screen();
    while (running) {
        print(matrix);
        printf("\nSpeed: %dms | A/Z - speed up/down | Space - exit\n", speed);
        
        if (handle_input(&speed)) {
            running = 0;
        } else {
            update(matrix);
            sleep_ms(speed);
            clear_screen();
        }
    }

    // Cleanup
    for (int i = 0; i < HEIGHT; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

void print(char **matrix) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(matrix[i][j]);
        }
        putchar('\n');
    }
}

void update(char **matrix) {
    char new_matrix[HEIGHT][WIDTH];
    
    // Copy borders
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                new_matrix[i][j] = matrix[i][j];
            }
        }
    }

    // Update cells
    for (int i = 1; i < HEIGHT-1; i++) {
        for (int j = 1; j < WIDTH-1; j++) {
            int neighbors = 0;
            
            // Count neighbors (with wrapping)
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (x == 0 && y == 0) continue;
                    
                    int ny = (i + y + HEIGHT - 2) % (HEIGHT - 2) + 1;
                    int nx = (j + x + WIDTH - 2) % (WIDTH - 2) + 1;
                    
                    if (matrix[ny][nx] == '*') neighbors++;
                }
            }
            
            // Apply rules
            if (matrix[i][j] == '*') {
                new_matrix[i][j] = (neighbors == 2 || neighbors == 3) ? '*' : ' ';
            } else {
                new_matrix[i][j] = (neighbors == 3) ? '*' : ' ';
            }
        }
    }
    
    // Copy back
    for (int i = 1; i < HEIGHT-1; i++) {
        for (int j = 1; j < WIDTH-1; j++) {
            matrix[i][j] = new_matrix[i][j];
        }
    }
}

int setup(char **matrix, char *path) {
    FILE *file = fopen(path, "r");
    if (!file) return 1;

    char ch;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1) {
                matrix[i][j] = '=';
            } else if (j == 0 || j == WIDTH-1) {
                matrix[i][j] = '|';
            } else {
                do {
                    ch = fgetc(file);
                } while (ch == '\n');
                
                if (ch == EOF) {
                    matrix[i][j] = ' ';
                } else {
                    matrix[i][j] = (ch == '1') ? '*' : ' ';
                }
            }
        }
    }

    fclose(file);
    return 0;
}

void clear_screen(void) {
    printf("\033[2J\033[H");
}

int handle_input(int *speed) {
#ifdef _WIN32
    if (_kbhit()) {
        char c = _getch();
#else
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0) {
#endif
        if (c == ' ') return 1;
        if (c == 'A' || c == 'a') *speed = (*speed > 10) ? *speed - 10 : *speed;
        if (c == 'Z' || c == 'z') *speed += 10;
    }
    return 0;
}

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}