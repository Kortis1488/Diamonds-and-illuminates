#include "quad.h"

dimond::dimond(int wl, int wh, int size)
{   
    this->size = size;
    basePoseX = (wl-size*quadr+size/2);
    basePoseY = (wh-size*2+size/2);
    int k, kpo;

    for(int i = 0; i<quadr; i++){
        k = quadr2-i-1;
        kpo = k-3; //k minus three

        rect[i].w = rect[i].h = rect[k].w = rect[k].h = size;

        if(i%2==0){ 
            rect[i].x = (i*size+basePoseX)/2;
            rect[i].y = (-i*size+basePoseY)/2;

            rect[k].x = (kpo*size+basePoseX)/2;
            rect[k].y = rect[i].y;
        }
        else{
            rect[i].x = ((i-1)*size+basePoseX)/2;
            rect[i].y = ((i-1)*size+basePoseY)/2;

            rect[k].x = ((kpo+1)*size+basePoseX)/2;
            rect[k].y = rect[i].y;
        }
    }

}

SDL_FRect *dimond::getQuad()
{   
    return rect;
}

int dimond::getResolution()
{
    return quadr2;
}
