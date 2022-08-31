// Simple Platformer using BeachBum as the char

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

bool init();
void kill();
bool loop();

// Pointers to window, renderer, and texture
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

// Main
int main(int argc, char** args)
{
    if (!init()) return 1;
    while(loop())
    {
        SDL_Delay(10);
    }
    
    kill();
    return 0;
}

// Game Loop
bool loop()
{
    // Check Event
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return false;
                    break;
            }
        }
    }
    // Update Window
    SDL_SetRenderDrawColor(renderer, 23,26,17,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    // Go again 
    return true;
}

// Initializations
bool init()
{
    // Init SDL with Error Check
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Error initializing SDL:" << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    
    // Init Window with Error Check
    window = SDL_CreateWindow("Beach Bum", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Error creating window:" << SDL_GetError() << std::endl;
        system("pause");
        return false;
    }
    
    // Init Renderer with Error Check
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if (!renderer)
    {
        std::cout << "Error creating renderer:" << SDL_GetError() << std::endl;
        return false;
    }
   
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return true;
}

// Free Resources
void kill()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    texture = NULL;
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}
