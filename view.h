#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <vector>

typedef struct {
  int loop; // conta o numero de loops(atualizações do jogo)
  int delay;//delay = constante de tempo, ou, quantos loops até mudar de quadro
  int index;//sprite atual para o blit (rect font)
  int add;//controla a direção da animação, 0-para,1-para_frente e -1-retroceder
  int sprite_max;//numero total de sprites, o index vai até sprite_max - 1
  int restart; // reiniciar quando chegar ao fim?
}SpriteAnim;

class catHeroRender
{
    public:
        catHeroRender();
        ~catHeroRender();

        int LoadImages(SDL_Renderer **renderer);
        void AnimeUpdate(int state);
        void updateWindow(SDL_Renderer **renderer, SDL_RendererFlip flip);
        std::vector<SpriteAnim> getAnimations() { return animations; };
        
        SDL_Rect* getFont() { return &font; };
        SDL_Rect* getDest() { return &dest; };
        SDL_Rect* getBackground() { return &background; };

        void setFont(SDL_Rect font) { this->font = font; };
        void setDest(SDL_Rect dest) { this->dest = dest; };
        void setBackground(SDL_Rect background) { this->background = background; };

    private:
        SDL_Texture *texture;
        SDL_Texture* texture2;
        std::vector<SpriteAnim> animations;
        SDL_Rect font;
        SDL_Rect dest;
        SDL_Rect background;

        void define_animations();
};