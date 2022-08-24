// Pip Boy style terminal for Inspector Gray

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void draw_map()
{
    SDL_Rect rect{20,20,100,100};
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
   
    // Vars and Bools
    bool running = true;
    SDL_Event event;
    
    // Entities
    SDL_Rect rect{30,30,100,100};

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


        draw_map();
    }

}
