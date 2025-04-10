#include "figure.h"

baseFigureCreator::baseFigureCreator()
{
}

baseTriangle::baseTriangle()
{   
    float baseY = SDL_sqrt(3);
    vertex.push_back({0, 0});
    vertex.push_back({1.0, baseY});
    vertex.push_back({-1.0, baseY});
}


SDL_FPoint baseFigureCreator::getCenter()
{
    if (vertex.empty()) {
        return SDL_FPoint{0, 0};
    }
    
    float y = 0, x = 0;
    for(int i = 0; i<vertex.size(); i++){
        x += vertex[i].x;
        y += vertex[i].y; 
    }
    
    SDL_FPoint center;
    center.x = x/vertex.size();
    center.y = y/vertex.size();

    return center;
}

std::shared_ptr<std::vector<SDL_FPoint>> baseFigureCreator::getVertex()
{
    return std::make_shared<std::vector<SDL_FPoint>>(vertex);
}

circleCreator::circleCreator()
{
    createCircle(0, 0, 100);
}

circleCreator::circleCreator(float centerX, float centerY, int radius)
{
    createCircle(centerX, centerY, radius);
}

void circleCreator::createCircle(float centerX, float centerY, int radius)
{
    SDL_FPoint cen = {centerX,centerY};
    int 
        Dg,
        Dd,
        Dv,
        y = radius,
        x = 0,
        r = radius;

    auto calcDd = [&](){
        Dd = SDL_pow((x+1),2)+SDL_pow((y-1),2) - SDL_pow(r,2);
    };
    auto calcDg = [&](){
        Dg = SDL_pow((x+1),2)+SDL_pow(y,2) - SDL_pow(r,2);
    };
    auto calcDv = [&](){
        Dv = SDL_pow(x,2)+SDL_pow((y-1),2) - SDL_pow(r,2);
    };
    auto dig = [&](){
        x++;
        y--;
    };

    auto addPoint = [&](){
        vertex.push_back({ centerX + x, centerY + y });
        vertex.push_back({ centerX - x, centerY - y });
        vertex.push_back({ centerX + y, centerY + x });
        vertex.push_back({ centerX - y, centerY - x });
        vertex.push_back({ centerX - x, centerY + y });
        vertex.push_back({ centerX + x, centerY - y });
        vertex.push_back({ centerX - y, centerY + x });
        vertex.push_back({ centerX + y, centerY - x });
    };

    
    while(x<radius){
        addPoint();
        calcDd();

        if(Dd<0){
            calcDg();
            if(SDL_abs(Dg)-SDL_abs(Dd)<=0) 
            {
                x++;
                continue;
            }
        }
        if(Dd>0)
        {
            calcDv();
            if(SDL_abs(Dd)-SDL_abs(Dv)>0) {
                y--;
                continue;
            }
        }
        dig();
    }
}