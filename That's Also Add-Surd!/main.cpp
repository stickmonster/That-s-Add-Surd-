#define SDL_MAIN_HANDLED

#include <iostream>
#include "game.h"
#include "renderer.h"



int main() {
    SDL_SetMainReady();

    //variables to be passed to the instances below
     constexpr std::size_t kScreenWidth{ 640 };
    constexpr std::size_t kScreenHeight{ 640 };
    constexpr std::size_t kGridWidth{ 32 };
    constexpr std::size_t kGridHeight{ 32 };

    
      
    //instances of the renderer (setting up SDL2), the game, and the game member function- running the game 
    //(which leads onto the game loop)

    
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

    Game game(kGridWidth, kGridHeight);
        

    game.Run(renderer);
    
  
 
    return 0;
}