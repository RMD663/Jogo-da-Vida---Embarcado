// --- Bibliotecas ---
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "GameOfLife.h"

// --- Lógica do Jogo ---
void initialize_grid(bool grid[GRID_HEIGHT][GRID_WIDTH])
{
    srand(time(NULL));
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = rand() % 2;
        }
    }
}

void reset_grid(bool grid[GRID_HEIGHT][GRID_WIDTH])
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = false;
        }
    }
}

void update_grid(bool grid[GRID_HEIGHT][GRID_WIDTH], bool next_grid[GRID_HEIGHT][GRID_WIDTH])
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            int live_neighbors = 0;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    int neighbor_x = x + dx;
                    int neighbor_y = y + dy;

                    if (neighbor_x >= 0 && neighbor_x < GRID_WIDTH &&
                        neighbor_y >= 0 && neighbor_y < GRID_HEIGHT)
                    {
                        live_neighbors += grid[neighbor_y][neighbor_x];
                    }
                }
            }

            if (grid[y][x] == 1)
            {
                next_grid[y][x] = (live_neighbors == 2 || live_neighbors == 3);
            }
            else
            {
                next_grid[y][x] = (live_neighbors == 3);
            }
        }
    }

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = next_grid[y][x];
        }
    }
}

// --- Gráficos e Display ---
void splash_animation(ssd1306_t *display)
{
    ssd1306_draw_string(display, 20, 30, 1, "Made By");
    ssd1306_draw_string(display, 20, 40, 1, "Ryan Mesquita");
    ssd1306_show(display);
    make_intro_sound();
    ssd1306_clear(display);
    ssd1306_draw_string(display, 0, 0, 2, "Embarca");
    ssd1306_draw_string(display, 10, 25, 2, "Tech");
    ssd1306_draw_string(display, 50, 50, 2, "2025");
    ssd1306_show(display);
    make_course_logo_sound();
    ssd1306_clear(display);
}

void draw_grid(ssd1306_t *display, bool grid[GRID_HEIGHT][GRID_WIDTH])
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            uint32_t x_pos = x * CELL_SIZE;
            uint32_t y_pos = y * CELL_SIZE;

            if (grid[y][x])
            {
                ssd1306_draw_square(display, x_pos, y_pos, CELL_SIZE, CELL_SIZE);
            }
            else
            {
                ssd1306_clear_square(display, x_pos, y_pos, CELL_SIZE, CELL_SIZE);
            }
        }
    }
    ssd1306_show(display);
}

// --- Sons e Alertas ---
void make_course_logo_sound()
{
    int frequencies[] = {330, 349, 392, 440, 392, 349};
    int durations[] = {300, 300, 400, 500, 400, 300};
    int note_count = sizeof(frequencies) / sizeof(frequencies[0]);

    for (int i = 0; i < note_count; i++)
    {
        for (int j = 0; j < durations[i] * 1000 / (1000000 / frequencies[i]); j++)
        {
            gpio_put(BUZZER_A, 1);
            sleep_us(750000 / frequencies[i]);
            gpio_put(BUZZER_A, 0);
            sleep_us(250000 / frequencies[i]);
        }
        sleep_ms(50);
    }

    int final_note_frequency = 523;
    int final_note_duration = 600;
    for (int j = 0; j < final_note_duration * 1000 / (1000000 / final_note_frequency); j++)
    {
        gpio_put(BUZZER_A, 1);
        sleep_us(750000 / final_note_frequency);
        gpio_put(BUZZER_A, 0);
        sleep_us(250000 / final_note_frequency);
    }
}

void make_intro_sound()
{
    int frequencies[] = {349, 523, 440, 392, 349, 440, 523, 349, 523, 587};
    int durations[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 700};
    int note_count = sizeof(frequencies) / sizeof(frequencies[0]);

    for (int i = 0; i < note_count; i++)
    {
        for (int j = 0; j < durations[i] * 1000 / (1000000 / frequencies[i]); j++)
        {
            gpio_put(BUZZER_A, 1);
            sleep_us(750000 / frequencies[i]);
            gpio_put(BUZZER_A, 0);
            sleep_us(250000 / frequencies[i]);
        }
        sleep_ms(50);
    }

    int final_note_frequency = 220;
    int final_note_duration = 1000;
    for (int j = 0; j < final_note_duration * 1000 / (1000000 / final_note_frequency); j++)
    {
        gpio_put(BUZZER_A, 1);
        sleep_us(750000 / final_note_frequency);
        gpio_put(BUZZER_A, 0);
        sleep_us(250000 / final_note_frequency);
    }
}

void make_reset_alert_sound()
{
    int frequencies[] = {523, 659, 784, 523};
    int durations[] = {400, 400, 400, 800};
    int note_count = sizeof(frequencies) / sizeof(frequencies[0]);

    for (int i = 0; i < note_count; i++)
    {
        for (int j = 0; j < durations[i] * 1000 / (1000000 / frequencies[i]); j++)
        {
            gpio_put(BUZZER_A, 1);
            sleep_us(500000 / frequencies[i]);
            gpio_put(BUZZER_A, 0);
            sleep_us(500000 / frequencies[i]);
        }
        sleep_ms(50);
    }

    sleep_ms(500);
    for (int i = 0; i < note_count; i++)
    {
        for (int j = 0; j < durations[i] * 1000 / (1000000 / frequencies[i]); j++)
        {
            gpio_put(BUZZER_A, 1);
            sleep_us(500000 / frequencies[i]);
            gpio_put(BUZZER_A, 0);
            sleep_us(500000 / frequencies[i]);
        }
    }
}

void make_sounds()
{
    int frequencies[] = {880, 1046, 1318, 1046, 880};
    int durations[] = {100, 100, 100, 100, 300};
    int note_count = sizeof(frequencies) / sizeof(frequencies[0]);

    for (int i = 0; i < note_count; i++)
    {
        for (int j = 0; j < durations[i] * 1000 / (1000000 / frequencies[i]); j++)
        {
            gpio_put(BUZZER_A, 1);
            sleep_us(500000 / frequencies[i]);
            gpio_put(BUZZER_A, 0);
            sleep_us(500000 / frequencies[i]);
        }
        sleep_ms(20);
    }

    sleep_ms(100);
}

// --- Inicialização e Setup ---
void setup_gpios(void)
{
    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_B, GPIO_OUT);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);
}

bool life_ended(bool grid[GRID_HEIGHT][GRID_WIDTH])
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (grid[y][x])
            {
                return false;
            }
        }
    }
    gpio_put(LED_RED, 1);
    return true;
}

// --- Funções de Jogo ---
void init_game(ssd1306_t *display, bool grid[GRID_HEIGHT][GRID_WIDTH])
{
    setup_gpios();
    display->external_vcc = false;
    ssd1306_init(display, 128, 64, 0x3C, i2c1);
    ssd1306_clear(display);
    splash_animation(display);
    initialize_grid(grid);
}

void end_game(ssd1306_t *disp)
{
    make_sounds();
    sleep_ms(3000);
    ssd1306_clear(disp);
    ssd1306_draw_string(disp, 20, 30, 1, "Fim da");
    ssd1306_draw_string(disp, 20, 40, 1, "Simulacao");
    make_sounds();
    ssd1306_show(disp);
    sleep_ms(1000);
    ssd1306_clear(disp);
    ssd1306_draw_string(disp, 20, 30, 1, "Reinice a");
    ssd1306_draw_string(disp, 20, 40, 1, "Placa!");
    ssd1306_show(disp);
    sleep_ms(1000);
    ssd1306_clear(disp);
    while (true)
    {
        make_reset_alert_sound();
    }

    ssd1306_clear(disp);
}

// -- Bonus! --
