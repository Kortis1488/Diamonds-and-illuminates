#include "figure.h"

baseFigure::baseFigure(Uint8 angles): angles(angles)
{
}

baseTriangle::baseTriangle():baseFigure(3)
{   
    float baseY = SDL_sqrt(3);

    peaks.push_back({0, 0});
    peaks.push_back({1.0, baseY});
    peaks.push_back({-1.0, baseY});
}


SDL_FPoint baseFigure::getCenter()
{
    if (peaks.empty()) {
        return SDL_FPoint{0, 0};
    }
    
    float y = 0, x = 0;
    for(int i = 0; i<peaks.size(); i++){
        x += peaks[i].x;
        y += peaks[i].y; 
    }
    
    SDL_FPoint center;
    center.x = x/peaks.size();
    center.y = y/peaks.size();

    return center;
}

std::shared_ptr<std::vector<SDL_FPoint>> baseTriangle::getTrianglePointsPtr()
{
    return std::make_shared<std::vector<SDL_FPoint>>(peaks);
}

circle::circle()
{
}

void circle::createCircle(double rCirX, double step, double multiplier)
{

}


std::shared_ptr <std::vector<SDL_FPoint>> circle::getPoints()
{
    return std::make_shared<std::vector<SDL_FPoint>>(circ);
}
