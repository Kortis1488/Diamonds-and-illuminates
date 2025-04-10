/* points.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some points
 * to it every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include "quad.h"
#include "figure.h"
#include "position.h"
#include "Image.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>



/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;

Uint8 siq = 1;
int u = 1;
int quntity = 150;
std::vector<dimond> di;

//(обводка) базовый треугольник
baseTriangle baseTrngl;
baseTriangle baseTrngl1;

std::vector<imageDesigner> objects;


std::shared_ptr<std::vector<SDL_FPoint>> trngl;
std::shared_ptr<std::vector<SDL_FPoint>> trngl1;





circleCreator cirCreater;
circleCreator cirCreater1;
circleCreator cirCreater2;
circleCreator cirCreater3;
circleCreator cirCreater4;
curveCreator curvCret;
curveCreator curvCret1;
curveCreator curvCret2;
curveCreator curvCret3;





#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WW WINDOW_WIDTH
#define WH WINDOW_HEIGHT

#define NUM_POINTS 500
#define MIN_PIXELS_PER_SECOND 30  /* move at least this many pixels per second. */
#define MAX_PIXELS_PER_SECOND 60  /* move this many pixels per second at most. */




/* (track everything as parallel arrays instead of a array of structs,
   so we can pass the coordinates to the renderer in a single function call.) */

/* Points are plotted as a set of X and Y coordinates.
   (0, 0) is the top left of the window, and larger numbers go down
   and to the right. This isn't how geometry works, but this is pretty
   standard in 2D graphics. */
static SDL_FPoint points[NUM_POINTS];
static float point_speeds[NUM_POINTS];

void rendTri(){
    
    cirCreater.createCircle(WW/2,WH/2,18);
    cirCreater1.createCircle(WW/2,WH/2,15);
    cirCreater2.createCircle(WW/2,WH/2,12);
    cirCreater3.createCircle(WW/2+7,WH/2-7,3);
 
    
    innerRegion in;
    in.createInnReg(*cirCreater.getCircle());
    in.createInnReg(*cirCreater1.getCircle());
    in.createInnReg(*cirCreater2.getCircle());
    in.createInnReg(*cirCreater3.getCircle());

    SDL_FPoint p0 = { 300, 300 };  
    SDL_FPoint p1 = { 400, 250 };  
    SDL_FPoint p3 = { 400, 350 };  
    SDL_FPoint p2 = { 500, 300 };    
    
    curvCret.createCurve(p0,p1,p2,0.1);
    curvCret1.createCurve(p0,p3,p2,0.1);
    curvCret2.createCurve(p0,p1,p2,0.1);
    curvCret3.createCurve(p0,p3,p2,0.1);
    
    std::vector<SDL_FPoint> curva = *curvCret1.getCurve(); 
    std::reverse(curva.begin(),curva.end());
    curvCret.getCurve()->insert(curvCret.getCurve()->end(), curva.begin(), curva.end());


    std::vector<SDL_FPoint> curva1 = *curvCret3.getCurve(); 
    std::reverse(curva1.begin(),curva1.end());
    curvCret2.getCurve()->insert(curvCret2.getCurve()->end(), curva1.begin(), curva1.end());


    objects.emplace_back(baseTrngl1.getVertex().get(),130); // 1
    objects.emplace_back(baseTrngl.getVertex().get(),115); // 0
    objects.emplace_back(curvCret.getCurve(),0.75); // 2
    objects.emplace_back(curvCret2.getCurve(),0.6); // 3

    

    // cc.x = 0.0f;
    // cc.y = 0.0f;

    //image cir(beko.getPoints().get());
    //circ = std::make_shared<std::vector<SDL_FPoint>>(*cir.getPoints());

}


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    rendTri();
    for(int i = 0; i<quntity; i++){
        di.emplace_back(WW,WH,i);
    }
    
    int i;
    SDL_SetAppMetadata("Example Renderer Points", "1.0", "com.example.renderer-points");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Bruh", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* set up the data for a bunch of points. */
    for (i = 0; i < SDL_arraysize(points); i++) {
        points[i].x = SDL_randf() * ((float) WINDOW_WIDTH);
        points[i].y = SDL_randf() * ((float) WINDOW_HEIGHT);
        point_speeds[i] = MIN_PIXELS_PER_SECOND + (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
    }

    last_time = SDL_GetTicks();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
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

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{   
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 100);
    SDL_RenderClear(renderer);
    
   

    double speed = TORADIAN*0.568;
    objects[0].rotate(speed);
    objects[1].rotate(speed);
    objects[2].rotate(speed);
    objects[3].rotate(speed);











//    ромбы    
if(siq==5){
    u = -1;
}
if(siq==0){
    u = 1;
}
if((SDL_GetTicks()/10)%30==0){
    siq += u;
}
                    
for(int i = 0; i<quntity; i++){
    di.emplace_back(WW,WH,i);
}
                        
Uint8 rC = 0, gC = 0, bC = 0, f = 1, d = 1, t = 0;
Uint8 rE, gE ,bE;                        
      
for(int i = 0; i<quntity; i++){
    t = SDL_GetTicks()/7;
    rC>255 ? f = 1 : f = -1;
    gC>50 ? d = 1 : d = 1;
    gC<10 ? d = -1 : d = -1;
                            
                            
    rC = f*i*10;
    gC = d*i*10 - 100;
    bC = gC + (t);

    if(bC<50) bC = 50;
    if(bC>180) bC = 180;
    if(gC>200) gC = 140;

    if(i == 18){
        rE = rC;
        gE = gC;
        bE = bC;
    }
    SDL_SetRenderDrawColor(renderer, rC , gC, bC, 100);
    for(int j = 0; j<64; j++){
        SDL_RenderFillRect(renderer, di[i].getQuad()+j); 
    }
}
                                
di.clear();


   
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderPoints(renderer, objects[0].getPoints()->data(), objects[0].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    SDL_RenderPoints(renderer, objects[1].getPoints()->data(), objects[1].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderPoints(renderer, objects[2].getPoints()->data(), objects[2].getPoints()->size());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    SDL_RenderPoints(renderer, objects[3].getPoints()->data(), objects[3].getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderPoints(renderer, cirCreater.getCircle()->data(), cirCreater.getCircle()->size());
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    SDL_RenderPoints(renderer, cirCreater1.getCircle()->data(), cirCreater1.getCircle()->size());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderPoints(renderer, cirCreater2.getCircle()->data(), cirCreater2.getCircle()->size());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    SDL_RenderPoints(renderer, cirCreater3.getCircle()->data(), cirCreater3.getCircle()->size());

    SDL_RenderPresent(renderer);
    //return SDL_APP_FAILURE;
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}
                            
/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}

                            
// rC>255 ? f = 1 : f = -1;
// gC>50 ? d = -1 : d = -1;
// gC<10 ? d = 1 : d = 1;
                        
                        
// rC = i*10;
// gC = i*10 + 20;
// bC = gC + d*(SDL_GetTicks()/102*10+20);