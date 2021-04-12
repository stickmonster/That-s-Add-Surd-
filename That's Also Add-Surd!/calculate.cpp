
#include "calculate.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>


//Calculate::operator Line() { return <Calculate::Line, std::allocator<Calculate::Line>>; }

std::vector<double> Calculate::euclidean_length(std::vector<Line> drawn_lines) {
    for (auto& line : drawn_lines) {


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
    return euclids;

}



    void Calculate::sum_up(std::vector<double> &euclids) {

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
            std::cout << "You scored higher than the most popular transcendent irrational rationalised and scaled up by 100. You win!" << std::endl;
        }

    }