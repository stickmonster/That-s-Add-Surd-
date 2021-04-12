#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include <SDL_image.h>







class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
        const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    
    struct Line {

        int x1;
        int y1;
        int x2;
        int y2;
    };


    Line line;

    std::vector<Line> lines;
    std::vector<Line> counted_lines;
    std::vector<double> euclids;
    

    double euclidean = 0.0;




    void Render(SDL_Point const& block);

 
    
private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    
  
    
    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};


#endif
