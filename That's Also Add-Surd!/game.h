#ifndef GAME_H
#define GAME_H

#include "renderer.h"
#include "SDL.h"


class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height);


    void Run(Renderer& renderer);

   
private:
    SDL_Point block = { 0, 0 };
 
};

#endif