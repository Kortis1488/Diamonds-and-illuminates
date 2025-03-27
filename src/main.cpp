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
circle beko;

std::vector<SDL_FPoint> linia;

imageDesigner trng(baseTrngl.getTrianglePointsPtr().get(),115);
imageDesigner trng1(baseTrngl1.getTrianglePointsPtr().get(),130);


std::shared_ptr<std::vector<SDL_FPoint>> trngl;
std::shared_ptr<std::vector<SDL_FPoint>> trngl1;
std::shared_ptr<std::vector<SDL_FPoint>> circ;




scaler sclr;
offseter ofstr;


circle eyeApple;
offseter ofstrCirc;

lines l;
lines l1;
innerRegion innReg;

rotator rtr;

SDL_FPoint cc;




#define WINDOW_WIDTH 1080
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
    

    // cc.x = 0.0f;
    // cc.y = 0.0f;

    // beko.createCircle((double)75, 0.05f, 0.3);
    
    
    
    // trngl = std::make_shared<std::vector<SDL_FPoint>>(*trng.getPoints());
    

    
    // trng1.dif(*trng.getOutline());
    
    // trngl1 = std::make_shared<std::vector<SDL_FPoint>>(*trng1.getPoints());

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
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{   
    SDL_SetRenderDrawColor(renderer, 30, 20, 40, 255);
    SDL_RenderClear(renderer);
    
   
    //rtr.rotate(*trngl, baseTrngl.getCenter(),2*TORADIAN, ofstr); 
    //rtr.rotate(*trngl1, baseTrngl1.getCenter(),2*TORADIAN, ofstr); 
    //rtr.rotate(*beko.getPoints(), cc, 2*TORADIAN, ofstr); 
    
    trng1.rotate(TORADIAN);
    trng.rotate(TORADIAN);











//     //ромбы    
if(siq==5){
    u = -1;
}
if(siq==0){
    u = 1;
}
if((SDL_GetTicks()/10)%20==0){
    siq += u;
}
                    
for(int i = 0; i<quntity; i++){
    di.emplace_back(WW,WH,i);
}
                        
Uint8 rC = 0, gC = 0, bC = 0, f = 1, d = 1;
                        
                        
for(int i = 0; i<quntity; i++){
    rC>255 ? f = 1 : f = -1;
    gC>50 ? d = -1 : d = -1;
    gC<10 ? d = 1 : d = 1;
                            
                            
    rC = i*10;
    gC = i*10 + 20;
    bC = gC + d*(SDL_GetTicks()/102*10+20);
                            
    SDL_SetRenderDrawColor(renderer, rC , gC, bC, 100);
    for(int j = 0; j<64; j++){
        SDL_RenderFillRect(renderer, di[i].getQuad()+j); 
    }
}
                                
di.clear();


   
    SDL_SetRenderDrawColor(renderer, 155, 155, 200, 100);
    SDL_RenderPoints(renderer, trng1.getPoints()->data(), trng1.getPoints()->size());
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    SDL_RenderPoints(renderer, trng.getPoints()->data(), trng.getPoints()->size());
    

    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    //SDL_RenderPoints(renderer, circ->data(), circ->size());
    
    
    SDL_RenderPresent(renderer);
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}
                            
/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}

                            
                            
// rCir = 25;
// x = -rCir;

// while(x<=rCir){
//     circle.emplace_back();
//     x += 0.001;
//     circle.back().x = x;
//     circle.back().y = SDL_sqrt(SDL_pow(rCir,2)-SDL_pow(x,2));
//     circle.back().x += offX;
//     circle.back().y += offY;
    
//     circle.emplace_back();
//     x += 0.001;
//     circle.back().x = x;
//     circle.back().y = -SDL_sqrt(SDL_pow(rCir,2)-SDL_pow(x,2));
//     circle.back().x += offX;
//     circle.back().y += offY;
// }

// rCir = 15;
// x = -rCir;

// while(x<=rCir){
//     circle.emplace_back();
//     x += 0.001;
//     circle.back().x = x;
//     circle.back().y = SDL_sqrt(SDL_pow(rCir,2)-SDL_pow(x,2));
//     circle.back().x += offX;
//     circle.back().y += offY;
    
//     circle.emplace_back();
//     x += 0.001;
//     circle.back().x = x;
//     circle.back().y = -SDL_sqrt(SDL_pow(rCir,2)-SDL_pow(x,2));
//     circle.back().x += offX;
//     circle.back().y += offY;
// }
// rCir = 5;
// x = -rCir;

// while(x<=rCir){
//     circle.emplace_back();
//     x += 0.001;
//     circle.back().x = x;
//     circle.back().y = SDL_sqrt(SDL_pow(rCir,2)-SDL_pow(x,2));
//     circle.back().x += offX+15;
//     circle.back().y += offY-12;
    
//     circle.emplace_back();
//     x += 0.001;
//     circle.back().x = x;
//     circle.back().y = -SDL_sqrt(SDL_pow(rCir,2)-SDL_pow(x,2));
//     circle.back().x += offX+15;
//     circle.back().y += offY-12;
// }
