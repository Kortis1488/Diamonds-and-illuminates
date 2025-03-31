#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#define PI 3.141592653589793
#define TORADIAN PI/180

class radCalculator{
    public:
        const float calculateRadius(SDL_FPoint &center, SDL_FPoint &point);
};

class scaler{
    private:
        radCalculator rc;
        float scaleVal = 75;
    public:
        scaler();
        void scale(std::vector<SDL_FPoint>& figure, float scaleVal, SDL_FPoint center);
};

class offseter{
    public:
        SDL_FPoint ofst;
        offseter();
        void offset(std::vector<SDL_FPoint>& fg, SDL_FPoint center, int ww, int wh);
};

class rotator{ 
    public: 
        rotator();
        void rotate(std::vector<SDL_FPoint> & fg, SDL_FPoint center, float turnAngle, offseter offst);
    
};

class angleCounter{
    private:
        const double spin = 360*TORADIAN;
        float step;
        float count;
    public:
        angleCounter();
        angleCounter(float stp);
        float getCount();
        void resetCount();
        void setStep(float stp);
};

class lines{
    private:
    std::vector<SDL_FPoint> lin;
    public:
        void createLines(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);
        std::vector<SDL_FPoint>* getLines();
        void clear();
};

class innerRegion{
    public:
        static bool comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);
        void createInnReg(std::vector<SDL_FPoint> &lin);
};

class overlayer{
    public:
        static bool comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);
        static void overlay(std::vector<SDL_FPoint> * lpoints, std::vector<SDL_FPoint> * rpoints);
};

class circleCreater{
    std::vector<SDL_FPoint> circle;
    public:
        void createCircle(float centerX, float centerY, int radius);
        std::vector<SDL_FPoint>* getCircle();
};
