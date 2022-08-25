// Pip Boy style terminal

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


int main()
{
    // Initializations    
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1280, 800, 0, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
    SDL_StartTextInput();
  
    // Font Setup 
    TTF_Font *font = TTF_OpenFont("VT323-Regular.ttf", 25);
    SDL_Surface *font_surf = TTF_RenderText_Solid(font, "Welcome to the Holocron v4.7.20", {23,26,17});
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surf);
    SDL_FreeSurface(font_surf);

    // Vars and Bools
    bool running = true;
    SDL_Event event;
    SDL_Rect rect{20,50, 980,27};
    int w = 0;
    int h = 0;
    SDL_QueryTexture(font_texture, NULL, NULL, &w, &h);
    SDL_Rect font_rect{rect.x + 10, rect.y - 1, w, h}; 
    std::string inp("-> "); 
    int inpW = 0;
    int inpH = 0;
    int inpY = 100; 
    
    while(running)
    {
        // Setup User Input and Display to Screen
        SDL_Surface *input_surf = TTF_RenderText_Solid(font, inp.c_str(), {241,201,8});
        SDL_Texture *input_texture = SDL_CreateTextureFromSurface(renderer, input_surf);
        SDL_QueryTexture(input_texture, NULL, NULL, &inpW, &inpH);
        SDL_Rect input_rect{20,inpY, inpW, inpH};
    
        // User Iput
        while(SDL_PollEvent(&event))
        {   
            // Text Input
            if(event.type == SDL_TEXTINPUT)
            {
                inp += event.text.text;
            }
            if(inp.size() > 79 and inp.size() < 81)
            {
               //TODO: Wrap New Lines 
            }
            
            // Escape, Backspace, Enter
            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_BACKSPACE:
                        if (inp.size() > 3)
                        {
                            inp.pop_back();
                        }
                        break;
                    case SDLK_RETURN:
                        //TODO: Figure  out how to keep old text and start new text box.
                        inpY += 25;
                        break;
                }
            }
        }

        // Draw to Screen
        SDL_SetRenderDrawColor(renderer, 23, 26, 17, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 241, 201, 8, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, font_texture, NULL, &font_rect);
        SDL_RenderCopy(renderer, input_texture, NULL, &input_rect);

        SDL_RenderPresent(renderer);
    }

    // Release Resources
    SDL_StopTextInput();
    SDL_DestroyTexture(font_texture);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

}
