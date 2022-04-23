#include "model.h"

catHero::catHero()
{
    window = NULL;
    renderer = NULL;
    screen_width = 800;          // width, in pixels
    screen_height = 600;         // height in pixels
    max_screen_width = 1600;     // max width in pixels
    max_screen_height = 800;     // max height in pixels
    wall_limit = -200;           // wall limit
    title_name = "Cat Hero+";    // window title
}

catHero::~catHero()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int catHero::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("\nUnable to initialize SDL:  %s\n", SDL_GetError());
        return -1;
    }
    else
    {
        // Create an application window with the following settings:
        window = SDL_CreateWindow(
            title_name.c_str(),          // window title
            SDL_WINDOWPOS_UNDEFINED,     // initial x position
            SDL_WINDOWPOS_UNDEFINED,     // initial y position
            screen_width,                // width, in pixels
            screen_height,               // height, in pixels
            SDL_WINDOW_OPENGL            // flags
        );
        
        if (window == NULL)
        {
            return -1;
        }
        
        if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) ) == NULL)
        {
            return -1;
        }
    }

    return 0;
}

int catHero::StateMachine(int state, std::vector<Button> b, std::vector<SpriteAnim> anim, int gethit, int* velo_x, int* velo_y)
{
    switch (state)
    {
		case 0: // parado
        {
            *velo_x = 0;
			if (gethit == 1) // Bateu
            {
				// reiniciando a próxima animação
				anim[6].index = 0;
				anim[6].loop = 0;
				return 6;
			}
			if (b[0].state == 1 || b[1].state == 1) // se pressiona o botão para andar
            {
				// reiniciando a próxima animação
				anim[1].index = 0;
				anim[1].loop = 0;
				return 1;
			}
			if (b[2].state == 1) // pulando
            {
				// reiniciando a próxima animação
				anim[3].index = 0;
				anim[3].loop = 0;
                b[2].input = released;
				return 3;
			}
            if (b[3].state == 1) // escorregar
            {
				// reiniciando a próxima animação
				anim[5].index = 0;
				anim[5].loop = 0;
                b[3].input = released;
				return 5;
			}
			break;
        }
		case 1: // caminhando
        {
            if (gethit == 1) // Bateu
            {
				// reiniciando a próxima animação
				anim[6].index = 0;
				anim[6].loop = 0;
				return 6;
			}
			if (b[0].state == 1) // caminhar direita
				*velo_x = 5;
			if (b[1].state == 1) // caminhar esquerda
				*velo_x = -5;
			if (b[0].state == 2 || b[1].state == 2) // parou de caminhar
            {
                // reiniciando a próxima animação
				anim[0].index = 0;
				anim[0].loop = 0;
				return 0;
			}
			if (b[2].state == 1) // pulando
            {
				// reiniciando a próxima animação
				anim[3].index = 0;
				anim[3].loop = 0;
                b[2].input = released;
				return 3;
			}
            if (b[3].state == 1) // escorregar
            {
                // reiniciando a próxima animação
				anim[5].index = 0;
				anim[5].loop = 0;
                b[3].input = released;
                return 5;
			}
			break;
        }
		case 3: // pulando
        {
			*velo_y = -10;
			if (b[0].state == 1) // caminhar direita
				*velo_x = 10;
			if (b[1].state == 1) // caminhar esquerda
				*velo_x = -10;
			// Se chegou ao final da animação pular
			if (anim[3].index == anim[3].sprite_max - 1)
            {
				// reiniciando a próxima animação
				anim[4].index = 0;
				anim[4].loop = 0;
                *velo_y = 0;
				return 4;
			}
			break;
        }	
		case 4: // caindo
        {
            // supondo que está caindo após um pulo
			*velo_y = 10;
			if (b[0].state == 1) // caminhar direita
				*velo_x = 10;
			if (b[1].state == 1) // caminhar esquerda
				*velo_x = -10;
			if (anim[4].index == anim[4].sprite_max - 1)
            {
				// reiniciando a próxima animação
				anim[0].index = 0;
				anim[0].loop = 0;
                *velo_y = 0;
				return 0;
			}
			break;
        }
		case 5: // escorregando
        {
            if (b[0].state == 1) // caminhar direita
				*velo_x = 5;
			if (b[1].state == 1) // caminhar esquerda
				*velo_x = -5;
			if (anim[5].index == anim[5].sprite_max - 1)
            {
                // reiniciando a próxima animação
                if(b[3].input == released)
                {
                    anim[0].index = 0;
                    anim[0].loop = 0;
                    *velo_x = 0;
                    return 0;
                }
                else
                {
                    anim[5].index = 0;
                    anim[5].loop = 0;
                    return 5;
                }
			}
			break;
        }
		case 6: // bateu
        {
            *velo_x = 0; // pare de mover
			if (anim[6].index == anim[6].sprite_max - 1)
			{
				// reiniciando a próxima animação
				anim[0].index = 0;
				anim[0].loop = 0;
				return 0;
			}
			break;
        }
		case 7: // morreu
        {
            *velo_x = 0; // pare de mover
			if (anim[7].index == anim[7].sprite_max - 1)
			{
				// reiniciando a próxima animação
				anim[0].index = 0;
				anim[0].loop = 0;
				return 0;
			}
        }
		default:
			break;
	}

	return state; // continua no mesmo
}

void catHero::updateHeroPosition(SDL_Rect* font, SDL_Rect* dest, int speed_x, int speed_y, int state_index, int fstate)
{
	font->x = state_index * font->w;
	font->y = fstate * font->h;

	if (speed_x == 0 && speed_y == 0)
	{
		return;
	}

	if (speed_x > 0)
	{
		if ((dest->x + dest->w + speed_x) <= screen_width)
		{
			dest->x += speed_x;
		}
	}
	else if (speed_x < 0)
	{
		if ((dest->x + dest->w + speed_x) > (0 + dest->w))
		{
			dest->x += speed_x;
		}
	}

	if (speed_y == 0)
	{
		return;
	}

	dest->y += speed_y;

	// descendo
	//if (speed_y > 0)
	//{
	//	if ((dest->y + dest->h + speed_y) <= screen_height - 40)
	//	{
	//		dest->y += speed_y;
	//	}
	//}
	//else // subindo
	//{
	//	if ((dest->y + dest->h + speed_y) > 0)
	//	{
	//		dest->y += speed_y;
	//	}
	//}
}
