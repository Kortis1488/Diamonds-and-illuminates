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



/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;
int quntity = 150;
std::vector<dimond> di;
std::vector<imageDesigner> objects;


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

    objects.emplace_back(baseTrngl1.getVertex().get(),130); // 1
    objects.emplace_back(baseTrngl.getVertex().get(),115); // 0
    objects.emplace_back(expCurva.getVertex().get(),0.75); // 2
    objects.emplace_back(expCurva.getVertex().get(),0.6); // 3
    objects.emplace_back(cirCreater.getVertex().get()); // 4
    objects.emplace_back(cirCreater1.getVertex().get()); // 5
    objects.emplace_back(cirCreater2.getVertex().get()); // 6
    objects.emplace_back(cirCreater3.getVertex().get()); // 7

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
    
    float speed = TORADIAN*0.568f;
    objects[0].rotate(speed);
    objects[1].rotate(speed);
    objects[2].rotate(speed);
    objects[3].rotate(speed);

//    ромбы                        
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


    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    // SDL_RenderPoints(renderer, line.data(), line.size());

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
    //return SDL_APP_FAILURE;
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}
                            
/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}