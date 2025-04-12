#pragma once
#include "position.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WW WINDOW_WIDTH
#define WH WINDOW_HEIGHT


enum mode{
    ANGLES,
    OUTLINE
};

class imageDesigner{
    private:
        std::vector<SDL_FPoint> angles;
        std::vector<SDL_FPoint> outline;
        std::vector<SDL_FPoint> inner;

        lines lin;    
        scaler scaler;
        offseter offseter;
        innerRegion innerRegion;
        rotator rotator;
        
        void setImageWithAutoOutline(std::vector<SDL_FPoint> *points, float scale);
        void setImageWithPreparedOutline(std::vector<SDL_FPoint> *points);
        void creatOutline();

        static bool comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);

    protected:
        SDL_FPoint center;
        std::vector<SDL_FPoint> points;
        void calculateCenter(mode m);
    public:
        imageDesigner();
        imageDesigner(std::vector<SDL_FPoint> * points, float scale);
        imageDesigner(std::vector<SDL_FPoint> * points);
        void rotate(float radian);
        std::vector<SDL_FPoint> * getPoints();
        std::vector<SDL_FPoint> * getOutline();
        std::vector<SDL_FPoint> * getAngles();
    };