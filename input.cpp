// Using SDL to take user input
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <iterator>
int main()
{
    // Setup Window and Renderer
    int aspect_x = 1280;
    int aspect_y = 800;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(aspect_x, aspect_y, 0, &window, &renderer);
    
    // Player
    int speed = 5;
    int velocityX = 10;
    int velocityY = 10;
    SDL_Rect rect{velocityX,velocityY,100, 200}; 
    // Control
    bool running = true;
    SDL_Event event;
    while (running)
    {   
        // User Input Events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                // Check Which Key is Entered
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                    case SDLK_d:
                        rect.x += speed;
                        break;
                    case SDLK_a:
                        rect.x -= speed;
                        break;
                    case SDLK_s:
                        rect.y += speed;
                        break;
                    case SDLK_w:
                        rect.y -= speed;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
        SDL_RenderClear(renderer);
        
        // Draw
        SDL_SetRenderDrawColor(renderer, 158, 136, 25, 255);
        SDL_RenderDrawLine(renderer, 400, 600, 800, 600);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }


    return 0;
}
