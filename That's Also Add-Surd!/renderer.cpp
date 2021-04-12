
#include "renderer.h"
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>



//while loop flag
bool running = true;


Renderer::Renderer(const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
    screen_height(screen_height),
    grid_width(grid_width),
    grid_height(grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    //Initialise PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError());
        //success = false;

    }

    // Create Window
    sdl_window = SDL_CreateWindow("That's Add-Surd!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, screen_width,
        screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}



void Renderer::Render(SDL_Point const& block) {


    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    SDL_Event e;

    //initialisation of struct Line points
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

   
    //while loop handles drawing of lines. Initialisation before while loop to prevent resetting
    bool drawing = false;

    //timer before while loop so as not to restart timing
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


    while (running) {

        bool drawing = false;


        // Render blocks at regular intervals on the grid

        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
        SDL_Rect block;
        block.w = screen_width / grid_width * 0.5;
        block.h = screen_height / grid_height * 0.5;
        for (int i = 8; i < 53; i += 4)
            for (int j = 8; j < 53; j += 4) {
                block.x = j * block.w;
                block.y = i * block.h;

                SDL_RenderFillRect(sdl_renderer, &block);
                SDL_RenderPresent(sdl_renderer);
                SDL_Delay(10);


                SDL_PollEvent(&e);
                

                switch (e.type)
                {


                case SDL_MOUSEBUTTONDOWN:
                    switch (e.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        x1 = e.motion.x;
                        y1 = e.motion.y;
                        x2 = e.motion.x;
                        y2 = e.motion.y;
                        drawing = true;
                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    switch (e.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        drawing = true;
                        Line line = { x1, y1, x2, y2 };
                        lines.push_back(line);
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (drawing)
                    {
                        x2 = e.motion.x;
                        y2 = e.motion.y;
                        break;
                    }
                 
                }
     
                for (std::vector<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
                {
                    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
                    line = *i;

                    SDL_RenderDrawLine(sdl_renderer, line.x1, line.y1, line.x2, line.y2);
                    SDL_RenderPresent(sdl_renderer);
                    //allows only lines originating and terminating in blocks, 
                    //(with some leeway for granularity of mouse) to score
                    if (line.x1 >= block.x - 3 && line.x1 <= (block.x) + 14) {
                        if (line.y1 >= block.y - 3 && line.y1 <= (block.y) + 14) {
                            if (((grid_width - line.x2) % 40 <= 14) && ((grid_height - line.y2) % 40 <= 14))
                            {
                                //Update screen
                          
                                counted_lines.push_back(line);

                            }
                           
                            for (auto& line : counted_lines) {


                                //compute euclidean distance, reducing distance between blocks to one unit
                                //and discounting earlier leeway for block size and mouse motion granularity

                                int x1_narrowed = static_cast<int> (line.x1 / 40);
                                int y1_narrowed = static_cast<int> (line.y1 / 40);
                                int x2_narrowed = static_cast<int> (line.x2 / 40);
                                int y2_narrowed = static_cast<int> (line.y2 / 40);

                                //find euclidean via pythagoras
                                double x_distance = x2_narrowed - x1_narrowed;
                                double y_distance = y2_narrowed - y1_narrowed;
                                double x_distance_squared = pow(x_distance, 2.0);
                                double y_distance_squared = pow(y_distance, 2.0);
                                euclidean = sqrt(x_distance_squared + y_distance_squared);

                                //push back into new vector for sorting and reducing against impact of while loop
                                euclids.push_back(euclidean);

                            }



                        }



                    }

         
                }


            }

                    //timer to terminate the while loop and allow reduction of euclideans and summing
                    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                    auto score_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
                    if (score_time > 27182818) {
                        running = false;
                    }
                

                //last scope in while loop
            }
        //final summation: unique irrationals grant points, unique rationals take-away    
        double sum = 0.0;

        sort(euclids.begin(), euclids.end());

        euclids.erase(std::unique(euclids.begin(), euclids.end()), euclids.end());

        for (auto euclidean : euclids) {
            //attempt (inelegant partly due to binary-rounding inaccuracies) to cover the rationals for points deduction
            if (std::fmod(euclidean, 1) == 0.0 || std::fmod(euclidean, 1 / 99) == 0.0 || std::fmod(euclidean, 1 / 3) == 0.0 || std::fmod(euclidean, 2 / 3) == 0.0 || std::fmod(euclidean, 1 / 105) == 0.0 || std::fmod(euclidean, 1 / 128) == 0.0 ||
                std::fmod(euclidean, 1 / 13) == 0.0 || std::fmod(euclidean, 1 / 17) == 0.0 || std::fmod(euclidean, 1 / 19) == 0.0) {
                sum -= euclidean;
                std::cout << "Lose: " << euclidean << std::endl;
            }

            else {
                sum += euclidean;
                std::cout << "Gain: " << euclidean << std::endl;
            }


        }

            std::cout << "Sum is: " << sum << std::endl;
            if (sum > 31.4159265359) {
                std::cout << "You scored higher than the most popular transcendent irrational rationalised and scaled by a boring, old, rational, round number. Yes, we might as well have called that random but, well, we both know it isn't... You win!" << std::endl;
            }


        }


Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

