#include "Image.h"




void imageDesigner::aOT(std::vector<SDL_FPoint> *pts, float scale)
{
    angles.insert(angles.end(),pts->begin(),pts->end());
    calculateCenter(ANGLES);
    scaler.scale(angles, scale, this->center);
    offseter.offset(angles, this->center, WW, WH); 
    creatOutline();

    outline.insert(outline.end(),angles.begin(),angles.end());
    inner.insert(inner.end(),outline.begin(),outline.end());
    innerRegion.createInnReg(inner);
    
    points.insert(points.end(),inner.begin(),inner.end());
}

void imageDesigner::hMOT(std::vector<SDL_FPoint> *pts)
{   
    outline.insert(outline.end(),pts->begin(),pts->end());
    calculateCenter(OUTLINE);
    offseter.offset(outline, this->center, WW, WH); 
    inner.insert(inner.end(),outline.begin(),outline.end());
    innerRegion.createInnReg(inner);

    points.insert(points.end(),inner.begin(),inner.end());
}

void imageDesigner:: calculateCenter(mode m)
{   
    std::vector<SDL_FPoint> *pts;
    m==ANGLES ? pts = &angles : pts = &outline; 

    if (pts->empty()) {
        return;
    }
    
    float y = 0, x = 0;
    for(int i = 0; i<pts->size(); i++){
        x += pts->at(i).x;
        y += pts->at(i).y;
    }
    
    this->center.x = x/pts->size();
    this->center.y = y/pts->size();
}

void imageDesigner::creatOutline()
{
    sort(angles.begin(), angles.end(), comparePoints);
    for(size_t i = 0; i<angles.size()-1; i++){
        lin.createLines(angles[i],angles[i+1]);
    }
    lin.createLines(angles[0],angles[angles.size()-1]);
    outline.insert(outline.end(),lin.getLines()->begin(),lin.getLines()->end());
}

bool imageDesigner::comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
{
    if (lpoint.y < rpoint.y) return true;
    if (lpoint.y > rpoint.y) return false;
    return lpoint.x < rpoint.x;
}

imageDesigner::imageDesigner(std::vector<SDL_FPoint> *points, float scale)
{
    aOT(points, scale);
}

imageDesigner::imageDesigner(std::vector<SDL_FPoint> *points)
{
    hMOT(points);
}

void imageDesigner::rotate(float radian)
{   
    calculateCenter(OUTLINE); // O(N)
    rotator.rotate(points,center,radian,offseter);
}

std::vector<SDL_FPoint> *imageDesigner::getPoints()
{
    return &points;
}

void imageDesigner::dif(const std::vector<SDL_FPoint> &outline) {
    std::vector<SDL_FPoint> oL(outline);  
    std::sort(oL.begin(), oL.end(), comparePoints);
    std::sort(this->inner.begin(), this->inner.end(), comparePoints);

    constexpr float EPSILON = 0.001f; // Только для y
    
    float lY, rY;
    float lX, rX;

    this->inner.erase(std::remove_if(this->inner.begin(), this->inner.end(),
        [&](const SDL_FPoint& point) {
            for (size_t i = 0; i < oL.size() - 1; i++) {
                lY = oL[i].y; 
                rY = oL[i+1].y;
                lX = oL[i].x; 
                rX = oL[i+1].x;

                if (SDL_abs(lY - rY) > EPSILON) continue; // Пропускаем, если не горизонталь
                if (SDL_abs(point.y - lY) < EPSILON && point.x >= lX && point.x <= rX) {
                    return true; // Удаляем точку
                }
            }
            return false;
        }), this->inner.end());

    this->points = this->inner;
}

std::vector<SDL_FPoint> *imageDesigner::getOutline()
{
    return &outline;
}
imageDesigner::imageDesigner()
{
}




