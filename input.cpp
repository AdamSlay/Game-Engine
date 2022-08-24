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


bool check_collision(SDL_Rect player, SDL_Rect platform)
{
    // A = Player | B = Platform
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int botA, botB;

    leftA = player.x;
    rightA = player.x + player.w;
    topA = player.y;
    botA = player.y + player.h;
    
    leftB = platform.x;
    rightB = platform.x + platform.w;
    topB = platform.y;
    botB = platform.y + platform.h;

    if (botA <= topB)
    {
        return false;
    }
    if (topA >= botB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    return true;
}



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
    int sq = 10;
    int gravity = 7;
    SDL_Rect rect{sq, sq, 30, 30};
    SDL_Rect plat{0,800,640,40};
    
    // Control
    bool running = true;
    bool touching;
    SDL_Event event;
    const Uint8 *keystate;
    bool Grounded = true;
    
    while (running)
    { 
        // Gravitational Force
        plat.y -= 2;
        bool touching = check_collision(rect, plat);
        if (touching)
        {
            Grounded = true;
            rect.y = plat.y - 30;
        }
        else
        {   
            Grounded = false;
            rect.y += gravity; 
        }
        
        // User Input Events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                // Check Which Key is Entered
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            }
            break;
        }

        // Movement
        keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_D])
        {
            rect.x += 5;
        }
        if (keystate[SDL_SCANCODE_A])
        {
            rect.x -= 5;
        }
        if (rect.x < 0 - rect.w)
        {
            rect.x = 1280;
        }
        if (rect.x > 1280)
        {
            rect.x = 0 - rect.w;
        }
        
        // Draw
        SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 158, 136, 25, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &plat);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }


    return 0;
}
