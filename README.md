

Much like life, 'That's Add-Surd!' is a game where anything irrational is a plus and anything rational is a negative. In this game you have to create unique irrational length lines. For each unique line you create you score the length of the line. However, if the line is rationalisable, you lose the length of that line from your score. Only those lines connected to the yellow blocks count for the scoring. You have 27.182818 seconds to score more than 31.4159265359 points in order to beat the game!

That's Add-Surd! is set in the SDL2 specification. In order to get the project running on your system, you will need the SDL2 development libraries, and to include and add the library files in the Project menu. The steps for this are in these two videos:

https://www.youtube.com/watch?v=QQzAHcojEKg

https://www.youtube.com/watch?v=x77Rbny5iBA

Here is what you should see when you're up and running.

![That's Add-Surd](https://user-images.githubusercontent.com/40922682/114428960-ba7b6680-9bb4-11eb-91f3-eed0a35d884a.JPG)


I hope you enjoy. Any feedback on the code very much appreciated.

Thanks,

Toby

ps, talking of feedback... I wanted to set up a more logical sequence of compilation units by adding a cpp file and header file that separated the below calculation and final summing up from the rendering. A key part of this was the passing of the (below) counted_lines vector to a euclid_length function organised as this screen-shotted For loop: 

![calculatecpp1](https://user-images.githubusercontent.com/40922682/114449789-18b44380-9bcd-11eb-8cb9-fda588d49695.JPG)

I, however, ran into a problem of converting the counted_lines vector as an argument (user defined Line type and struct in the renderer.h file) into the euclidean_length function's parameter in the calculate file. I whittled down the error messaging to:
'no conversion between std::vector<Renderer::Render::Line> and std::vector<Calculate::Line> exists', and then to: 'no conversion between std::vector<Line> and std::vector<Line>' exists.
  
I tried:

1)static cast.
2)re-ordering header file includes
3)putting a space after the header file includes
4)conversion functions 
5)replacing the original struct (both declaration and definition) in any number of positions.
6)staring forlornly at the idea of writing my own allocator function and chickening out.
7)and finally making a deal with Devil and dynamic-casting (sorry world).

Nothing worked. I couldn't get the argument accepted as a parameter in the calculate.cpp file. In the end I fell back on 'The Best is the enemy of the good' and went back to the above format which, at least, worked.
Again, any tips on this much appreciated.

Toby
