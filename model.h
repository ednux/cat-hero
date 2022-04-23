#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <string>
#include "controller.h"
#include "view.h"

#define PERSO_X dest.x + dest.w //espaço ocupado pelo personagem no eixo x

class catHero
{
    public:
        catHero();
        ~catHero();

        int Init();
        int StateMachine(int state, std::vector<Button> b, std::vector<SpriteAnim> anim, int gethit, int *velo_x, int *velo_y);
        void updateHeroPosition(SDL_Rect* font, SDL_Rect* dest, int speed_x, int speed_y, int state_index, int fstate);

        SDL_Window **getWindow() { return &window; }
        SDL_Renderer **getRenderer() { return &renderer; }

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        unsigned int screen_width;
        unsigned int screen_height;
        unsigned int max_screen_width;
        unsigned int max_screen_height;
        int wall_limit;
        std::string title_name;
};