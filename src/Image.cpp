#include "Image.h"




void imageDesigner::aOT(std::vector<SDL_FPoint> *pts, float scale, bool lnn)
{   
    angles.insert(angles.end(),pts->begin(),pts->end());
    calculateCenter(ANGLES);
    if(scale!=1) scaler.scale(angles, scale, this->center);
    offseter.offset(angles, this->center, WW, WH); 
    lnn?creatOutline():creatOutlineNonLinear();

    outline.insert(outline.end(),angles.begin(),angles.end());
    inner.insert(inner.end(),outline.begin(),outline.end());
    //innerRegion.createInnReg(inner);
    
    points.insert(points.end(),inner.begin(),inner.end());
}

void imageDesigner::hMOT(std::vector<SDL_FPoint> *pts)
{   
    outline.insert(outline.end(),pts->begin(),pts->end());
    calculateCenter(OUTLINE);
    //offseter.offset(outline, this->center, WW, WH); 
    inner.insert(inner.end(),outline.begin(),outline.end());
    //innerRegion.createInnReg(inner);

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
    lin.clear();
}
void imageDesigner::sortAngles()
{
    float left;
    auto sortX = [](const SDL_FPoint &lpoint, const SDL_FPoint &rpoint){return lpoint.x < rpoint.x;};
    // auto sortY = [](const SDL_FPoint &lpoint, const SDL_FPoint &rpoint){return lpoint.y < rpoint.y;};
    // auto findLeft = [&left](const SDL_FPoint &lpoint){return lpoint.x == left;};
    sort(angles.begin(), angles.end(), sortX);


    auto sortRV = [](const SDL_FPoint &lpoint, const SDL_FPoint &rpoint){
        if(lpoint.x<rpoint.x && lpoint.y < rpoint.y) return true;
    };
    
    sort(angles.begin(), angles.end(), sortRV);

    // sort(angles.begin(), angles.end(), sortX);
    // left = angles[0].x;
    // sort(angles.begin(), angles.end(), sortY);
    // auto iterL = find_if(angles.begin(), angles.end(),findLeft);
    // iterL++;
    // sort(angles.begin(), iterL, sortX);
    // sort(iterL+1, angles.end(), sortX);

    
    // std::cout<<"\n\n";
    // for(int i = 0; i<angles.size(); i++){
    //     std::cout<<angles[i].x<<" "<<angles[i].y<<"\n";
    // }
    // std::cout<<"\n\n";
}


void imageDesigner::creatOutlineNonLinear()
{
    sortAngles();
    auto iter = angles.begin();
    auto next = iter+1;
    auto end = angles.end();
    auto grid = next;
    while(iter->x < next->x){
        lin.createLines(*iter,*next);
        iter = next++;
    }
    grid = next;
    iter = next++;
    while(next != end){
        lin.createLines(*iter,*next);
        iter = next++;
    }
    lin.createLines(*angles.begin(),*grid);
    grid--;
    lin.createLines(*(angles.end()-1),*grid);
    outline.insert(outline.end(),lin.getLines()->begin(),lin.getLines()->end());
    lin.clear();
}

bool imageDesigner::comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
{
    if (lpoint.x < rpoint.x) return true;
    if (lpoint.x > rpoint.x) return false;
    return lpoint.y < rpoint.y;
}


void imageDesigner::rotate(float radian)
{   
    //outline.clear();
    inner.clear();
    points.clear();

    calculateCenter(ANGLES); 
    rotator.rotate(outline,center,radian,offseter);
    
    //creatOutline();
    
    //outline.insert(outline.end(),angles.begin(),angles.end());
    inner.insert(inner.end(),outline.begin(),outline.end());
    //innerRegion.createInnReg(inner);
    points.insert(points.end(),inner.begin(),inner.end());
    // std::cout<<lin.getLines()->size()<<" lin\n";
    // std::cout<<outline.size()<<" outline\n";
    // std::cout<<angles.size()<<" angles\n";
    // std::cout<<inner.size()<<" inner\n"; 
    
    // std::cout<<points.size()<<" points\n";


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

                if (SDL_abs(lY - rY) > EPSILON) continue; 
                if (SDL_abs(point.y - lY) < EPSILON && point.x >= lX && point.x <= rX) {
                    return true; 
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

imageDesigner::imageDesigner(std::vector<SDL_FPoint> *points, float scale, bool lnn)
{
    aOT(points, scale, lnn);
}

imageDesigner::imageDesigner(std::vector<SDL_FPoint> *points)
{
    hMOT(points);
}



