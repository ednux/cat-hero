#include "view.h"

catHeroRender::catHeroRender() :
    font{ 0,0, 100, 88 },
    dest{ (800 - 100) / 2,600 - 132,100,88 },
    background{ 0,0,800,1600 }
{
    define_animations();
}

catHeroRender::~catHeroRender()
{

}

int catHeroRender::LoadImages(SDL_Renderer **renderer)
{
    SDL_Surface *image = NULL;

    image = IMG_Load("cat.png");

    if (!image)
    {
        SDL_Log("Could not open cat.png\n, Error: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
	}

    texture = SDL_CreateTextureFromSurface(*renderer, image);
    SDL_FreeSurface(image);
    
    image = IMG_Load("background.png");
    
    if (!image)
    {
        SDL_Log("Could not open background.png\n, Error: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    texture2 = SDL_CreateTextureFromSurface(*renderer, image);
    SDL_FreeSurface(image);

    return 0;
}

void catHeroRender::updateWindow(SDL_Renderer **renderer, SDL_RendererFlip flip)
{
    SDL_RenderClear(*renderer);
    SDL_SetRenderDrawColor(*renderer,255,255,255,255);
    SDL_RenderCopyEx(*renderer,texture2,&background,NULL,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(*renderer,texture,&font,&dest,0,NULL,flip);
    SDL_RenderPresent(*renderer);
    SDL_Delay(60);
}

void catHeroRender::AnimeUpdate(int state)
{
    animations[state].loop = animations[state].loop + 1;
    
    if ((animations[state].loop % animations[state].delay) == 0)
    {
        animations[state].index = animations[state].index + animations[state].add;
        
        if (animations[state].index > animations[state].sprite_max - 1)
        {
            if (animations[state].restart)
            {
                animations[state].loop = 0;
                animations[state].index = 0;
            }
            else
            {
                animations[state].index = animations[state].sprite_max - 1;
            }
            return;
        }
        
        if (animations[state].index < 0)
        {
            if (animations[state].restart)
            {
                animations[state].loop = 0;
                animations[state].index = animations[state].sprite_max - 1;
            }
            else
            {
                animations[state].index = 0;
            }
            return;
        }
    }
}

void catHeroRender::define_animations()
{
    SpriteAnim animation = { 0 };

    // idle
    animation.loop = 0;
    animation.delay = 2;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 10;
    animation.restart = 1;

    animations.push_back(animation);

    // walking
    animation.loop = 0;
    animation.delay = 1;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 10;
    animation.restart = 1;

    animations.push_back(animation);

    // running
    animation.loop = 0;
    animation.delay = 1;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 8;
    animation.restart = 1;

    animations.push_back(animation);

    // jumping
    animation.loop = 0;
    animation.delay = 1;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 8;
    animation.restart = 1;

    animations.push_back(animation);


    // falling down
    animation.loop = 0;
    animation.delay = 1;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 8;
    animation.restart = 1;

    animations.push_back(animation);

    // beating
    animation.loop = 0;
    animation.delay = 2;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 10;
    animation.restart = 1;

    animations.push_back(animation);

    // dead
    animation.loop = 0;
    animation.delay = 1;
    animation.index = 0;
    animation.add = 1;
    animation.sprite_max = 10;
    animation.restart = 1;

    animations.push_back(animation);

}