#include <string>
#include "model.h"

int main(int argc, char **argv)
{
    int done = 0;
	int fstate = 0, prevstate = -1;
	int speed_x = 0, speed_y = 0;

    catHero hero;
    catHeroRender hero_render;
    catHeroController hero_controller;

    hero.Init();
    hero_render.LoadImages(hero.getRenderer());
    
    while (!done)
    {
        done = hero_controller.getKeyboardEvents();

        hero_controller.updateButtons();
		
        prevstate = fstate;

        fstate = hero.StateMachine(prevstate, hero_controller.getButtons(), hero_render.getAnimations(), 0, &speed_x, &speed_y);

        hero_render.AnimeUpdate(fstate);

        hero.updateHeroPosition(hero_render.getFont(), hero_render.getDest(), speed_x, speed_y, hero_render.getAnimations()[fstate].index, fstate);
        
        hero_render.updateWindow(hero.getRenderer(), hero_controller.getDirection());
    }

    return 0;
}