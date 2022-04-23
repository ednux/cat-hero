#include "controller.h"

catHeroController::catHeroController()
{
    define_buttons();
    kb = SDL_GetKeyboardState(NULL);
    SDL_Rect dest = {(800-100)/2,600-132,100,88};
}

catHeroController::~catHeroController()
{

}

void catHeroController::define_buttons()
{
    Button b;

    // right
	b.key = SDL_SCANCODE_RIGHT;
	b.state = 0;
	b.input = nothing;

    buttons.push_back(b);

    // left
	b.key = SDL_SCANCODE_LEFT;
    buttons.push_back(b);
    
    // jump
	b.key = SDL_SCANCODE_UP;
    buttons.push_back(b);
    
    // slide
	b.key = SDL_SCANCODE_DOWN;
    buttons.push_back(b);
}

int catHeroController::SButton(Button *b)
{
    switch (b->state)
    {
        case 0:
        {
            switch (b->input)
            {
                case pressed:
                {
                    return 1;
                }
				case released:
                {
                    break;
                }
			}
			break;
        }
        case 1:
        {
            switch (b->input)
            {
                case pressed:
                {
                    break;
                }
				case released:
                {
                    return 2;
                }
			}
			break;
        }
        case 2:
        {
            switch (b->input)
            {
                case pressed:
                {
                    return 0;
                }
				case released:
                {
                    return 0;
                }
			}
			break;
        }	
	}

	return b->state; //retorna o estado atual
}

int catHeroController::getKeyboardEvents()
{
    int done = 0;

    SDL_PumpEvents();
    
    if (kb[SDL_SCANCODE_ESCAPE])
    {
        done = 1;
    }
        
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            done = 1;
            break;
        }
        
        if (event.type == SDL_KEYDOWN)
        {
            for (Button &b : buttons)
            {
                if (event.key.keysym.scancode == b.key)
                {
                    b.input = pressed;
                }
            }
        }
        else
        {
            if (event.type == SDL_KEYUP)
            {
                for (Button &b : buttons)
                {
                    if (event.key.keysym.scancode == b.key)
                    {
                        b.input = released;
                    }
                }
            }
        }
    }
    return done;
}

void catHeroController::updateButtons()
{
    for (Button &b : buttons)
    {
        b.state = SButton(&b);
    }
}

SDL_RendererFlip catHeroController::getDirection()
{
    if (kb[SDL_SCANCODE_LEFT])
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (kb[SDL_SCANCODE_RIGHT])
    {
        flip = SDL_FLIP_NONE;
    }
    return flip;
}

int catHeroController::getSpeed()
{
    int speed_x = 0;

    if (kb[SDL_SCANCODE_A])
    {
        if (flip == SDL_FLIP_NONE)
        {
            speed_x = 100;
        }
        else
        {
            speed_x = -100;
        }
    }
    else
    {
        speed_x = 0;
    }
    return speed_x;
}