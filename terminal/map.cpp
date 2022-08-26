// Pip Boy style terminal

#include <SDL2/SDL_pixels.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


// Vars
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event event;
SDL_Rect rect{20,50, 980,27};
bool running = true;
int titleW = 0;
int titleH = 0;
int inpW = 0;
int inpH = 0;
int inpY = 100; 
int bs_allowed = 0;
std::string inp("-> "); 
std::string title("Welcome to TerminAItor v0.0.1");
SDL_Color bg{23,26,17};
SDL_Color tx{241,201,8};

int main()
{
    // Initializations    
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1280, 800, 0, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
    SDL_StartTextInput();
  
    // Font Setup 
    TTF_Font *font = TTF_OpenFont("VT323-Regular.ttf", 25);
    SDL_Surface *font_surf = TTF_RenderText_Solid(font, title.c_str(), bg);
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surf);
    SDL_FreeSurface(font_surf);

    SDL_QueryTexture(font_texture, NULL, NULL, &titleW, &titleH);
    SDL_Rect font_rect{rect.x + 10, rect.y - 1, titleW, titleH}; 
   
    while(running)
    {
        // Setup User Input and Display to Screen
        SDL_Surface *input_surf = TTF_RenderText_Blended_Wrapped(font, inp.c_str(), tx, 0);
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
                bs_allowed += 1;
                
                // Wrap Text after 80 chars
                if (bs_allowed % 80 == 0 and bs_allowed > 1)
                {  
                    bs_allowed = 0;
                    if (inp.substr(inp.size() - 1) == " ")
                    {
                        inp += "\n   ";
                    }
                    else
                    {
                        inp += "-\n   ";
                    }
                }
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
                        if (bs_allowed > 0)
                        {
                            inp.pop_back();
                        }
                        bs_allowed -= 1;
                        SDL_Delay(5);
                        break;
                    case SDLK_RETURN:
                        //TODO: keep old text and start new text on new line
                        inp += "\n-> "; 
                        bs_allowed = 0;
                        break;
                }
            }

            // Exit
            else if (event.type == SDL_QUIT)
            {
                running = false;
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
