// Rendering a Pixel to the screen.

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cmath>

int main()
{ 
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Ground 
    SDL_RenderDrawLine(renderer, 0, 400, 640, 400);
    int c = 4;
    int g_tex = 0;
    int ground = 400;
    int b_window = 480;
    while (g_tex < 700)
    { 
        SDL_RenderDrawLine(renderer, g_tex, b_window, g_tex + 50, ground + 12);
        g_tex += 50;
    }

    // Wall
    int L_wall = 100;
    int R_wall = 530;
    int T_wall = 300;
    SDL_RenderDrawLine(renderer, L_wall, T_wall, L_wall, ground);
    SDL_RenderDrawLine(renderer, R_wall, T_wall, R_wall, ground);
    int x = L_wall;
    while (x < R_wall)
    {
        if (x % 20 == 0)
        {
            // Horizontal Upper
            // Top of Wall
            SDL_RenderDrawLine(renderer, x, T_wall, x + 10, T_wall);    
            // Bricks
            for (int y = T_wall + 12.5; y < ground; y += 10)
            {
                SDL_RenderDrawLine(renderer, x, y, x + 10, y);
            }
        }
        else if (x % 10 == 0) 
        {
            // Horizontal Lower
            // Top of Wall
            SDL_RenderDrawLine(renderer, x, T_wall + 10, x + 10, T_wall + 10);
            // Bricks
            for (int y = T_wall + 17.5; y < ground; y += 10)
            {
                SDL_RenderDrawLine(renderer, x, y, x + 10, y);
            }
        }
        // Top of Wall - vert
        SDL_RenderDrawLine(renderer, x + 10, T_wall, x + 10, T_wall + 10);
        SDL_RenderDrawLine(renderer, L_wall, T_wall + 12.5, R_wall, T_wall + 12.5);
       
        // Bricks - vert 
        SDL_RenderDrawLine(renderer, x + 10, T_wall+12.5, x + 10, ground);

        x += 10; 
    }


    // Second Story
    int LL_sec = 160;
    int LR_sec = 260;
    int T_sec = 250;
    SDL_RenderDrawLine(renderer, LL_sec, T_wall, LL_sec, T_sec);
    SDL_RenderDrawLine(renderer, LL_sec, T_sec, LR_sec, T_sec);
    SDL_RenderDrawLine(renderer, LR_sec, T_wall, LR_sec, T_sec);
    int RL_sec = 370;
    int RR_sec = 470;
    SDL_RenderDrawLine(renderer, RL_sec, T_sec, RR_sec, T_sec);
    SDL_RenderDrawLine(renderer, RL_sec, T_wall, RL_sec, T_sec);
    SDL_RenderDrawLine(renderer, RR_sec, T_wall, RR_sec, T_sec);
    SDL_RenderDrawLine(renderer, RL_sec, T_sec+20, LR_sec, T_sec+20);

    // Third Story
    SDL_RenderDrawLine(renderer, 210, T_sec, 210, 200);    
    SDL_RenderDrawLine(renderer, 210, 200, 420, 200);    
    SDL_RenderDrawLine(renderer, 420, T_sec, 420, 200);
    
    // Tower
    SDL_RenderDrawLine(renderer, 290, 200, 290, 100);
    SDL_RenderDrawLine(renderer, 340, 200, 340, 100);
    
    // Roof Triangle
    SDL_RenderDrawLine(renderer, 290, 100, 280, 100);
    SDL_RenderDrawLine(renderer, 340, 100, 350, 100);
    SDL_RenderDrawLine(renderer, 280, 100, 316, 50);
    SDL_RenderDrawLine(renderer, 350, 100, 316, 50);

    SDL_RenderPresent(renderer);
    SDL_Delay(13000);

    return 0;
}
