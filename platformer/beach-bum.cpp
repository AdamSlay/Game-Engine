// Simple Platformer using BeachBum as the char

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool init();
void kill();
bool loop();
bool flip = false;
bool jumping = false;

// Pointers to window, renderer, and texture
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
int playerX = 200;
int playerY = 350;
int jumptime = 30;
float jumpforce = .01;
int deltaTime = 0;
int gravity = 10;
int speed = 10;
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
    if (playerY <= 350 && !jumping)
    {
        playerY += gravity;
    }
    SDL_Rect player = {playerX, playerY, 180, 300};
    static const unsigned char* keys = SDL_GetKeyboardState(NULL);
    // Check Event
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            return false;
            break;
        }
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return false;
                    break;
                case SDLK_a:
                    flip = true;
                    break;
                case SDLK_d:
                    flip = false;
                    break;
                case SDLK_SPACE:
                    int i = jumptime;
                    jumping = true;
                    while (i--)
                    {
                        playerY--;
                    }
            }
        }
        if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_SPACE:
                    jumping = false;
                    break;
            }
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_A])
    {
        playerX -= speed;
    }
    if (keystate[SDL_SCANCODE_D])
    {
        playerX += speed;
    }

    // Update Window
    SDL_SetRenderDrawColor(renderer, 23,26,17,255);
    SDL_RenderClear(renderer);
    if (flip)
    {
        SDL_RenderCopyEx(renderer, texture, NULL, &player, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopyEx(renderer, texture, NULL, &player,0,NULL,
                        keys[SDL_SCANCODE_LEFT] ? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
    }
    SDL_RenderPresent(renderer);
    // loop again 
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
   
    // Init IMG with Error Check
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cout << "Error initializing SDL_image:" << IMG_GetError() << std::endl;
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); 
    if (!renderer)
    {
        std::cout << "Error creating renderer:" << SDL_GetError() << std::endl;
        return false;
    }

    // Load PNG to surface
    SDL_Surface* buffer = IMG_Load("beach_bum_still.png");
    if(!buffer)
    {
        std::cout << "Error loading image beach_bum_still.png" << IMG_GetError() << std::endl;
        return false;
    }
  
    // Create Texture from IMG surface
    texture = SDL_CreateTextureFromSurface(renderer, buffer);
    SDL_FreeSurface(buffer);
    buffer = NULL;
    if(!texture)
    {
        std::cout << "Error creating texture:" << SDL_GetError() << std::endl;
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
    
    IMG_Quit();
    SDL_Quit();
}
