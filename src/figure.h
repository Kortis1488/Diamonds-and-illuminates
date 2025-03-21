#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <iostream>

class baseFigure{
    protected:
        std::vector<SDL_FPoint> peaks;
        const Uint8 angles;
    public:
        baseFigure(Uint8 angles);
        virtual SDL_FPoint getCenter();
};


class baseTriangle: public baseFigure{
    public:
        baseTriangle();
        std::shared_ptr <std::vector<SDL_FPoint>> getTrianglePointsPtr();    
    };

class circle{
    private: 
        std::vector<SDL_FPoint> circ;
    public:
        circle();
        void createCircle(double rCirX, double step, double multiplier);
        std::shared_ptr <std::vector<SDL_FPoint>> getPoints();
};
