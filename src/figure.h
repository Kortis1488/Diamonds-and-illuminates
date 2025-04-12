#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

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

class curveCreator: public baseFigureCreator{
    public:
        curveCreator();
        curveCreator(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
        void createCurve(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
};

class doubleCurveCreator: public curveCreator{
    public:
        doubleCurveCreator(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
};