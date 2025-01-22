#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdbool.h>
#include "libs/ssd1306/ssd1306.h"

// --- Definições de Configuração ---
#define CELL_SIZE 2
#define GRID_WIDTH 64
#define GRID_HEIGHT 32

#define BUZZER_A 10
#define BUZZER_B 21

#define BUTTON_A 5
#define BUTTON_B 6

#define LED_RED 13

// --- Funções de Inicialização ---
void initialize_grid(bool grid[GRID_HEIGHT][GRID_WIDTH]);
void setup_gpios(void);
void init_game(ssd1306_t *display, bool grid[GRID_HEIGHT][GRID_WIDTH]);

// --- Funções de Jogo ---
void reset_grid(bool grid[GRID_HEIGHT][GRID_WIDTH]);
void update_grid(bool grid[GRID_HEIGHT][GRID_WIDTH], bool next_grid[GRID_HEIGHT][GRID_WIDTH]);
bool life_ended(bool grid[GRID_HEIGHT][GRID_WIDTH]);

// --- Funções de Exibição ---
void splash_animation(ssd1306_t *display);
void draw_grid(ssd1306_t *display, bool grid[GRID_HEIGHT][GRID_WIDTH]);
void show_message_center(ssd1306_t *disp, const char *s, int time);

// --- Funções de Som ---
void make_course_logo_sound();
void make_intro_sound();
void make_sounds();

// --- Funções de Finalização ---
void end_game(ssd1306_t *disp);

#endif
