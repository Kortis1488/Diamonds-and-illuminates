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
    
    for(int i = 0; i<fg.size(); i++){
        float x = fg[i].x - offst.ofst.x - center.x;
        float y = fg[i].y - offst.ofst.y - center.y;
        
        fg[i].x = center.x + (x * SDL_cos(turnAngle) - y * SDL_sin(turnAngle)) + offst.ofst.x;
        fg[i].y = center.y + (x * SDL_sin(turnAngle) + y * SDL_cos(turnAngle)) + offst.ofst.y;
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
    //std::cout << "START p1t: (" << p1.x << ", " << p1.y << ")  "<< "p2t: (" << p2.x << ", " << p2.y << ")";
    p1.x = SDL_round(p1.x);
    p1.y = SDL_round(p1.y);
    p2.x = SDL_round(p2.x);
    p2.y = SDL_round(p2.y);

    float 
        dx = p2.x - p1.x,
        dy = p2.y - p1.y,
        err = 0,
        signY = (dy>=0 ? 1 : -1),
        signX = (dx>=0 ? 1 : -1),
        * mainFlowValPtr = (dx>dy ?  &p1.x :  &p1.y), // указатель на главную координату, у которой больше прирост
        * mainSignPtr = (dx>dy ?  &signX :  &signY), // указатель на прирост главной координаты
        df = ([&]()->float{
            if((dx||dy)!=0)
            {
                return SDL_fabsf(dx) > SDL_fabsf(dy) ? SDL_fabsf(dy / dx) : SDL_fabsf(dx / dy);
            }
            else{
                return 0.0f;
            }
        })();
        


    for(;;){
        if(p1.x==p2.x && p1.y==p2.y) break;
        err+=df;
        if(err<0.5f) 
        {
            *mainFlowValPtr += *mainSignPtr;
        }
        else{
            p1.x+=signX;
            p1.y+=signY;
            err -= 1.0f;
        }
        lin.push_back(p1);
        //std::cout << "p1t: (" << p1.x << ", " << p1.y << ")  "<< "p2t: (" << p2.x << ", " << p2.y << "), err = " << err <<" " << signX <<" "<< signY<<'\n';
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
        if(SDL_abs(lin.at(i).y-lin.at(i+1).y)<0.05){
            if(SDL_abs(lin.at(i).x-lin.at(i+1).x)>0.2){
                l.createLines(lin.at(i),lin.at(i+1));
            }
        }
        
    }
    std::vector<SDL_FPoint> * l1 = l.getLines();
    lin.insert(lin.end(),l1->begin(),l1->end());
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
