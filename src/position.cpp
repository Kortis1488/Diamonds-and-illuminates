#include "position.h"

scaler::scaler()
{

}

void scaler::scale(std::vector<SDL_FPoint> & figure, float scaleVal, SDL_FPoint center)
{
    for(int i = 0; i< figure.size(); i++){
        figure[i].x += (figure[i].x-center.x)*(scaleVal-1);
        figure[i].y += (figure[i].y-center.y)*(scaleVal-1);
     }
}

offseter::offseter()
{

}

void offseter::offset(std::vector<SDL_FPoint> &fg, SDL_FPoint center, int ww, int wh)
{
    SDL_FPoint offsets;
    offsets.x = ww/2 - center.x;
    offsets.y = wh/2 - center.y;
    this->ofst.x = offsets.x;
    this->ofst.y = offsets.y;

    center.x +=offsets.x;
    center.y +=offsets.y;

    for(int i = 0; i<fg.size(); i++){
        fg[i].x += offsets.x;
        fg[i].y += offsets.y;  
    }
}



void rotator::rotate(std::vector<SDL_FPoint> & fg, SDL_FPoint center, float turnAngle, offseter offst)
{
    double cos = SDL_cos(turnAngle);
    double sin = SDL_sin(turnAngle);
    for(int i = 0; i<fg.size(); i++){
        float x = fg[i].x - center.x;
        float y = fg[i].y - center.y;
        
        fg[i].x =   (x * cos - y * sin) + center.x;
        fg[i].y =   (x * sin + y * cos) + center.y;
    }
}

const float radCalculator::calculateRadius(SDL_FPoint &center, SDL_FPoint &point)
{
    float xR = SDL_pow((point.x - center.x),2);
    float yR = SDL_pow((point.y - center.y),2);
    return SDL_sqrt(xR+yR);
}


void lines::createLines(const SDL_FPoint &point1, const SDL_FPoint &point2)
{  
    SDL_FPoint 
        p1 = point1, 
        p2 = point2;

    p1.x = SDL_round(p1.x);
    p1.y = SDL_round(p1.y);
    p2.x = SDL_round(p2.x);
    p2.y = SDL_round(p2.y);

    float 
        dx = p2.x - p1.x, 
        dy = p2.y - p1.y;
    bool isXMajor = SDL_fabsf(dx) > SDL_fabsf(dy);
    
    if (dx == 0 && dy == 0) return;
    
    float 
        err = 0,
        signX = (dx >= 0) ? 1.0f : -1.0f,
        signY = (dy >= 0) ? 1.0f : -1.0f,
        df = isXMajor ? SDL_fabsf(dy / dx) : SDL_fabsf(dx / dy),
        *mainFlowValPtr = isXMajor ? &p1.x : &p1.y,
        *mainSignPtr = isXMajor ? &signX : &signY;
    
    
    
    while (!(p1.x == p2.x && p1.y == p2.y))
    {
        lin.push_back(p1);
        err += df;
        if (err >= 0.5f) 
        {
            err -= 1.0f;
            p1.x += signX;
            p1.y += signY;
        }
        else
        {
            *mainFlowValPtr += *mainSignPtr;
        }
    }
    lin.push_back(p1);
}


std::vector<SDL_FPoint>* lines::getLines()
{
    return &lin;
}

void lines::clear()
{
    lin.clear();
}

bool innerRegion::comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
{   
    if (lpoint.y < rpoint.y) return true;
    if (lpoint.y > rpoint.y) return false;
    return lpoint.x < rpoint.x;
}

void innerRegion::createInnReg(std::vector<SDL_FPoint> &lin)
{
    lines l;
    sort(lin.begin(),lin.end(),comparePoints);

    for(int i = 0; i<lin.size()-1; i++){
        if(lin[i].y==lin[i+1].y){
            l.createLines(lin.at(i),lin.at(i+1));
        }
    }
    lin.insert(lin.end(),l.getLines()->begin(),l.getLines()->end());
}


rotator::rotator()
{
    
}