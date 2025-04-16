/* points.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some points
 * to it every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include "figure.h"
#include "position.h"
#include "Image.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
int quntity = 150;
std::vector<dimond> di;
std::vector<imageDesigner> objects;


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WW WINDOW_WIDTH
#define WH WINDOW_HEIGHT


void rendTri(){

    SDL_FPoint p0 = { 300, 300 };  
    SDL_FPoint p1 = { 400, 250 };  
    SDL_FPoint p2 = { 500, 300 };  
    
    baseTriangle baseTrngl;
    baseTriangle baseTrngl1;    
    
    circleCreator cirCreater(WW/2,WH/2,18);
    circleCreator cirCreater1(WW/2,WH/2,15);
    circleCreator cirCreater2(WW/2,WH/2,12);
    circleCreator cirCreater3(WW/2+7,WH/2-7,3);

    curveCreator curvCretExp;


    doubleCurveCreator expCurva(p0,p1,p2,0.1f);

    objects.emplace_back(baseTrngl1.getVertex().get(),130); 
    objects.emplace_back(baseTrngl.getVertex().get(),115); 
    objects.emplace_back(expCurva.getVertex().get(),0.75); 
    objects.emplace_back(expCurva.getVertex().get(),0.6); 
    objects.emplace_back(cirCreater.getVertex().get()); 
    objects.emplace_back(cirCreater1.getVertex().get()); 
    objects.emplace_back(cirCreater2.getVertex().get()); 
    objects.emplace_back(cirCreater3.getVertex().get()); 

}


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    rendTri();
    for(int i = 0; i<quntity; i++){
        di.emplace_back(WW,WH,i);
    }
    
    int i;
    SDL_SetAppMetadata("Circling triangle", "1.0", "Bruh");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Circling triangle", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS; 
        break;
    default:
        break;
    }
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate)
{   
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 100);
    SDL_RenderClear(renderer);
    
    float speed = TORADIAN*0.568f;
    objects[0].rotate(speed);
    objects[1].rotate(speed);
    objects[2].rotate(speed);
    objects[3].rotate(speed);

                     
for(int i = 0; i<quntity; i++){
    di.emplace_back(WW,WH,i);
}
                        
Uint8 rC = 0, gC = 0, bC = 0, f = 1, d = 1, t = 0;                        
      
for(int i = 0; i<quntity; i++){
    t = SDL_GetTicks()/7;
  
                            
    rC = -i*10;
    gC = -i*10 - 100;
    bC = gC + (t);

    if(bC<50) bC = 50;
    if(bC>180) bC = 180;
    if(gC>200) gC = 140;

    SDL_SetRenderDrawColor(renderer, rC, gC, bC, 100);
    for(int j = 0; j<64; j++){
        SDL_RenderFillRect(renderer, di[i].getQuad()+j); 
    }
}
                                
di.clear();



    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderPoints(renderer, objects[0].getPoints()->data(), objects[0].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_RenderPoints(renderer, objects[1].getPoints()->data(), objects[1].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderPoints(renderer, objects[2].getPoints()->data(), objects[2].getPoints()->size());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_RenderPoints(renderer, objects[3].getPoints()->data(), objects[3].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderPoints(renderer, objects[4].getPoints()->data(), objects[4].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_RenderPoints(renderer, objects[5].getPoints()->data(), objects[5].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderPoints(renderer, objects[6].getPoints()->data(), objects[6].getPoints()->size());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_RenderPoints(renderer, objects[7].getPoints()->data(), objects[7].getPoints()->size());

    SDL_RenderPresent(renderer);
   
    return SDL_APP_CONTINUE; 
}
                            

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  
}