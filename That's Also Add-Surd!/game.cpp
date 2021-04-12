#include "game.h"
#include <iostream>
#include "SDL.h"
#include "renderer.h"



//The window renderer
SDL_Renderer* sdl_renderer = NULL;


Game::Game(std::size_t grid_width, std::size_t grid_height) {}


void Game::Run(Renderer& renderer) {

    // Render - including the main game loop.

    renderer.Render(block);
    
 }


