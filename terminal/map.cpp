// Pip Boy style terminal for Inspector Gray

#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void draw_map()
{

    SDL_Rect rect{50,20, 1180,20};
    
    SDL_SetRenderDrawColor(renderer, 23, 26, 17, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 241, 201, 8, 255);
    SDL_RenderFillRect(renderer, &rect);


    SDL_RenderPresent(renderer);
}

int main()
{

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(1280, 800, 0, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
    // Vars and Bools
    bool running = true;
    SDL_Event event;
    
    // Entities
    while(running)
    {
        // Check Which Key is Pressed. Exit Handling.
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            }
            break;
        }

        // Draw Map to Screen
        draw_map();
    }

}
