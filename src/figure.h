#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <iostream>

class baseFigureCreator{
    protected:
        std::vector<SDL_FPoint> vertex;
    public:
        baseFigureCreator();
        virtual SDL_FPoint getCenter();
        std::shared_ptr <std::vector<SDL_FPoint>> getVertex(); 
};


class baseTriangle: public baseFigureCreator{
    public:
        baseTriangle();
    };

class circleCreator: public baseFigureCreator{
    public:
        circleCreator();
        circleCreator(float centerX, float centerY, int radius);
        void createCircle(float centerX, float centerY, int radius);
};