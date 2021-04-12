#ifndef CALCULATE_H
#define CALCULATE_H

#include "renderer.h"
#include <list>
#include <iostream>
#include <vector>
#include <cmath>


class Renderer;
//declaration of points for line

class Calculate {

public: 
	friend class Renderer;
	//operator Line();

	struct Line {

		int x1;
		int y1;
		int x2;
		int y2;
	};
	Line line;


	std::vector<Line> drawn_lines;
	std::vector<double> euclidean_length(std::vector<Line> drawn_lines);
	void sum_up(std::vector<double> &euclids);
	

private:


	std::vector<double> euclids;
	
	
	double euclidean = 0.0;


};

#endif