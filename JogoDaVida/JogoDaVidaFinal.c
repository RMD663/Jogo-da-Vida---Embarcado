#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/GameOfLife.h"
#include "libs/ssd1306/ssd1306.h"

ssd1306_t disp;
bool grid[GRID_HEIGHT][GRID_WIDTH];
bool next_grid[GRID_HEIGHT][GRID_WIDTH];

int expansion_step = 0;
bool is_paused = false;
bool reset_game();
bool pause_game();

int main()
{
    stdio_init_all();
    init_game(&disp, grid);
    int gen = 0;
    while (gen < 1000)
    {
        if (pause_game())
        {
            make_sounds();
            is_paused = !is_paused;
            sleep_ms(100);
        }
        if (!is_paused)
        {
            draw_grid(&disp, grid);
            update_grid(grid, next_grid);
            gen++;
            if (reset_game())
            {
                gen = 0;
                reset_grid(grid);
                initialize_grid(grid);
                ssd1306_clear(&disp);
                ssd1306_draw_string(&disp, 0, 30, 1, "Reiniciando as");
                ssd1306_draw_string(&disp, 0, 40, 1, "Celulas!");
                ssd1306_show(&disp);
                sleep_ms(1500);
            }
            if (life_ended(grid))
            {
                ssd1306_clear(&disp);
                ssd1306_draw_string(&disp, 0, 30, 1, "Todas as celulas");
                ssd1306_draw_string(&disp, 0, 40, 1, "Morreram!!!");
                ssd1306_show(&disp);
                make_sounds();
                break;
            }
        }
        sleep_ms(100);
    }
    end_game(&disp);
    return 0;
}

bool pause_game()
{
    if (gpio_get(BUTTON_B) == 0)
    {
        sleep_ms(100);
        return true;
    }
    return false;
}

bool reset_game()
{
    if (gpio_get(BUTTON_A) == 0)
    {
        return true;
    }
    return false;
}
