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
    std::cout<<fg.empty()<<"\n";
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

angleCounter::angleCounter()
{
    this->count = 0;
    this->step = 1;
}

angleCounter::angleCounter(float stp)
{
    this->step = stp;
}

void angleCounter::setStep(float stp)
{
    this->step = stp;
}

float angleCounter::getCount()
{   
    count += step*TORADIAN;
    if(count>=spin)count -= spin; 
    
    return count;
}

void angleCounter::resetCount()
{
    count = 0;
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

bool overlayer::comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
{
    if (lpoint.y < rpoint.y) return true;
    if (lpoint.y > rpoint.y) return false;
    return lpoint.x < rpoint.x;
}

void overlayer::overlay(std::vector<SDL_FPoint> *lpoints, std::vector<SDL_FPoint> *rpoints) // TODO переделать нахуй
{
    sort(lpoints->begin(), lpoints->end(), comparePoints);
    sort(rpoints->begin(), rpoints->end(), comparePoints);

    auto iter = lpoints->begin();

    for (size_t i = 0; i < rpoints->size(); i++) {
        while (iter != lpoints->end()) {
            if (SDL_abs((rpoints->at(i).x) - (iter->x)) <= 0.1f || SDL_abs((rpoints->at(i).y) - (iter->y)) <= 0.1f) {
                iter = lpoints->erase(iter);  // erase возвращает следующий итератор
                break;  // Прерываем while, так как нашли нужный элемент
            } else {
                ++iter;
            }
        }
    }
}

void circleCreator::createCircle(float centerX, float centerY, int radius) {
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
        circle.push_back({ centerX + x, centerY + y });
        circle.push_back({ centerX - x, centerY - y });
        circle.push_back({ centerX + y, centerY + x });
        circle.push_back({ centerX - y, centerY - x });
        circle.push_back({ centerX - x, centerY + y });
        circle.push_back({ centerX + x, centerY - y });
        circle.push_back({ centerX - y, centerY + x });
        circle.push_back({ centerX + y, centerY - x });
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

std::vector<SDL_FPoint> *circleCreator::getCircle()
{
    return &circle;
}

void curveCreator::createCurve(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step)
{   
    curve.clear();
    float  
    t = 0.0f,
    x,
    y,
    x1,
    y1;
    lines lin;
    while(t<=1+step){
        x = (1-t)*p0.x + t*p1.x;
        y = (1-t)*p0.y + t*p1.y;

        x1 = (1-t)*p1.x + t*p2.x;
        y1 = (1-t)*p1.y + t*p2.y;

        x = (1-t)*x + t*x1;
        y = (1-t)*y + t*y1;
        curve.push_back({x,y});
        t += step;
    }
}

std::vector<SDL_FPoint> *curveCreator::getCurve()
{
    return &curve;
}
