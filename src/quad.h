#pragma once
#include <SDL3/SDL.h>

class dimond{
    public:
        static const int quadr2 = 64;
        const int quadr = quadr2/2;
        SDL_FRect rect [quadr2];
        dimond(int wl, int wh, int size);
        SDL_FRect * getQuad();
        int getResolution();
        int size;
        int basePoseX;
        int basePoseY;
};

