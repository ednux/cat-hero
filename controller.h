#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <vector>

typedef enum {nothing, pressed, released} ButtonInput;

typedef struct
{
    SDL_Scancode key;
    int state;
    ButtonInput input;
} Button;

class catHeroController
{
    public:
        catHeroController();
        ~catHeroController();

        int SButton(Button *b);
        int getKeyboardEvents();
        void updateButtons();
        SDL_RendererFlip getDirection();
        int getSpeed();
        std::vector<Button> getButtons(){ return buttons;};

    private:
        SDL_Event event;
        SDL_RendererFlip flip;
        std::vector<Button> buttons;
        void define_buttons();
        const Uint8 *kb;
};