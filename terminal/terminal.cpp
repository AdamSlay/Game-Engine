// Vintage Terminal

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Vars
bool running = true;
int staticW = 0;
int staticH = 0;
int promptW = 0;
int promptH = 0;
int promptY = 100; 
int inpW = 0;
int inpH = 0;
int bs_allowed = 0;
int new_lines = 0;
std::string prompt("-> ");
std::string inp(""); 
std::string title("Welcome to Typer v0.0.1");
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event event;
SDL_Rect title_rect{50,50, 820,27};
SDL_Rect bot_rect{50,723, 820,27};
SDL_Rect prompt_rect{60,promptY, promptW,promptH};
SDL_Rect input_rect{90,promptY, inpW,inpH};
SDL_Rect side_panel{920,450, 300,300};
SDL_Rect systems_rect{940,467, 260,27};
SDL_Rect Tside_panel{920,50, 300,380};
SDL_Color bg{23,26,17};
SDL_Color tx{241,201,8};
//TODO: History Vector for strings and Rect

std::string system_check_text("Air Circulation   Normal\nWater Level       Normal \nTemperature       Normal\n");

int main()
{
    // Initializations    
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1280, 800, 0, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
    SDL_StartTextInput();
  
    // Static Text 
    TTF_Font *font = TTF_OpenFont("VT323-Regular.ttf", 25);
    SDL_Surface *font_surf = TTF_RenderText_Solid(font, title.c_str(), bg);
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surf);
    SDL_FreeSurface(font_surf);
    SDL_QueryTexture(font_texture, NULL, NULL, &staticW, &staticH);
    SDL_Rect font_rect{title_rect.x + 280, title_rect.y - 1, staticW, staticH}; 
    
    SDL_Surface *systxt_surf = TTF_RenderText_Solid(font, "Systems", bg);
    SDL_Texture *systxt_texture = SDL_CreateTextureFromSurface(renderer, systxt_surf);
    SDL_FreeSurface(systxt_surf);
    SDL_QueryTexture(systxt_texture, NULL, NULL, &staticW, &staticH);
    SDL_Rect systxt_rect{systems_rect.x + 90, systems_rect.y - 1, staticW, staticH};

    SDL_Surface *bottxt_surf = TTF_RenderText_Solid(font, "Type Command and Press ENTER", bg);
    SDL_Texture *bottxt_texture = SDL_CreateTextureFromSurface(renderer, bottxt_surf);
    SDL_FreeSurface(bottxt_surf);
    SDL_QueryTexture(bottxt_texture, NULL, NULL, &staticW, &staticH);
    SDL_Rect bottxt_rect{bot_rect.x + 260, bot_rect.y - 1, staticW, staticH};
    
    SDL_Surface *syslist_surf = TTF_RenderText_Blended_Wrapped(font, system_check_text.c_str(), tx, 0);
    SDL_Texture *syslist_texture = SDL_CreateTextureFromSurface(renderer, syslist_surf);
    SDL_FreeSurface(syslist_surf);
    SDL_QueryTexture(syslist_texture, NULL, NULL, &staticW, &staticH);
    SDL_Rect syslist_rect{side_panel.x + 25, side_panel.y + 60, staticW, staticH};


    while(running)
    {
        // Surfaces, Textures, Rects
        SDL_Surface *prompt_surf = TTF_RenderText_Blended_Wrapped(font, prompt.c_str(), tx, 0);
        SDL_Texture *prompt_texture = SDL_CreateTextureFromSurface(renderer, prompt_surf);
        SDL_QueryTexture(prompt_texture, NULL, NULL, &promptW, &promptH);
        SDL_Surface *input_surf = TTF_RenderText_Blended_Wrapped(font, inp.c_str(), tx, 0);
        SDL_Texture *input_texture = SDL_CreateTextureFromSurface(renderer, input_surf);
        SDL_QueryTexture(input_texture, NULL, NULL, &inpW, &inpH);
        //TODO: Histry Surf and Texture
        prompt_rect.y = promptY;
        prompt_rect.h = promptH;
        prompt_rect.w = promptW;
        input_rect.y = promptY;
        input_rect.h = inpH;
        input_rect.w = inpW;
        
        // User Iput
        while(SDL_PollEvent(&event))
        {
            // Text Input
            if(event.type == SDL_TEXTINPUT)
            {
                inp += event.text.text;
                bs_allowed += 1;
                
                // Wrap Text after 80 chars
                if (bs_allowed % 75 == 0 and bs_allowed > 1)
                {  
                    inp.substr(inp.size() - 1) == " " ? inp+="\n": inp+="-\n";
                    new_lines += 1;
                    bs_allowed += 2;
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
                            bs_allowed -= 1;
                            // if backspace traverses over new_line,
                            // subtract one new line from the prompt queue
                            if (bs_allowed % 75 == 0 and bs_allowed > 1)
                            {
                                new_lines -= 1;
                            }
                        }
                        break;
                    case SDLK_RETURN:
                        // Move prompt to the correct line
                        // Reset available backspaces
                        // TODO: append inp to history and start new inp
                        inp += "\n";
                        for (int i = 0; i < new_lines; i++)
                        {
                            prompt += "\n";
                        }
                        prompt += "\n-> ";
                        bs_allowed = 0;
                        new_lines = 0;
                        break;
                    //TODO: case SDLK_UP -> go back in history
                    //TODO: case SDLK_DOWN -> go forward in history
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
        SDL_RenderDrawRect(renderer, &side_panel);
        SDL_RenderDrawRect(renderer, &Tside_panel);
        SDL_RenderFillRect(renderer, &systems_rect);
        SDL_RenderFillRect(renderer, &title_rect);
        SDL_RenderFillRect(renderer, &bot_rect);
        SDL_RenderCopy(renderer, font_texture, NULL, &font_rect);
        SDL_RenderCopy(renderer, input_texture, NULL, &input_rect);
        SDL_RenderCopy(renderer, prompt_texture, NULL, &prompt_rect);
        SDL_RenderCopy(renderer, systxt_texture, NULL, &systxt_rect);
        SDL_RenderCopy(renderer, bottxt_texture, NULL, &bottxt_rect);
        SDL_RenderCopy(renderer, syslist_texture, NULL, &syslist_rect);
        SDL_RenderPresent(renderer);
        // Release Resources
        SDL_FreeSurface(input_surf);
        SDL_DestroyTexture(input_texture);
        SDL_FreeSurface(prompt_surf);
        SDL_DestroyTexture(prompt_texture);
    }

    // Close All
    SDL_StopTextInput();
    SDL_DestroyTexture(font_texture);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
