//Nathan Game
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class AnimationFrame{
  SDL_Texture *frame;
  int Time,w,h;
  public:
  AnimationFrame(SDL_Texture *newFrame,int newTime=100){
    frame = newFrame;
    Time = newTime;
  }
  AnimationFrame(SDL_Renderer *ren,const char *imagePath,int newTime=100){
    SDL_Surface *bmp = SDL_LoadBMP (imagePath);
    if (bmp == NULL){
      cout<<"SDL_LoadBMP Error: "<< SDL_GetError << endl;
      SDL_Quit();
    }
    SDL_SetColorKey(bmp,SDL_TRUE,SDL_MapRGB(bmp->format,0,255,0));
    w = bmp->w;
    h = bmp->h;
    frame = SDL_CreateTextureFromSurface(ren,bmp);
    SDL_FreeSurface(bmp);
  }
}

class AdventureQuest:public Game{

}

int main(int argc, char **argv){


return 0;
}
