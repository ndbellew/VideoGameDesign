#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class AnimationFrame {
	SDL_Texture *frame;
	int time,w, h;//ms
	public:
		AnimationFrame(SDL_Texture *newFrame, int newTime=100)
		{
		frame=newFrame;
		time=newTime;
		}
		AnimationFrame(SDL_Renderer *ren, const char *imagePath, int newTime=100){
			SDL_Surface *bmp = SDL_LoadBMP(imagePath);
			if(bmp==NULL){
				cout<<"SDL_CreateTextureFromSurface Error:"<<SDL_GetError()<<
				endl;
				SDL_Quit();
			}
			w=bmp->w;
			h=bmp->h;
				time = newTime;
		}
		
		
		void show(SDL_Renderer *ren, int x=0, int y=0){
			SDL_Rect src, dest;
			dest.x=x;  dest.y=y;  dest.w=w; dest.h=h;
			src.x=0;  src.y=0; src.w=w;  src.h=h;
			SDL_RenderCopy(ren, frame, &src, &dest);
		}
		int getTime(){
			return time;
		}
		void destroy(){
			SDL_DestroyTexture(frame);
		}
};

class Animation{

	vector <AnimationFrame *> frames; 
	int totaltime;
	public:
		Animation()
		{
			totaltime=0;
		}	
		void addFrame(AnimationFrame *c)
		{
			frames.push_back(c);
			totaltime+=c->getTime();
		}
		virtual void show(SDL_Renderer *ren, int time /*ms*/, int x=0, int y=0){
			int aTime=time % totaltime;
			int tTime=0;
			unsigned int i=0;
			for (i=0; i<frames.size();i++){
				tTime+=frames[i]->getTime();
				if(aTime<=tTime) break;
			}
			frames[i]->show(ren);
		}
		virtual void destroy(){
			for(unsigned int i=0;i<frames.size();i++)
			frames[i]->destroy();
		}
	};
	
class Game{
	protected:
	SDL_Window *win;
	SDL_Renderer *ren;
	public:
	void init(const char *gameName, int maxW=640, int maxH=480, 
	int startX=100, int startY=100){
		if (SDL_Init(SDL_INIT_VIDEO) != 0){
			cout << "SDL_Init Error: " << SDL_GetError() << endl;
			SDL_Quit();
		}
		win=SDL_CreateWindow(gameName, startX, startY, maxW, maxH, SDL_WINDOW_SHOWN);
		if (win == NULL){
			cout << "SDL_CreateWindow Error: " << SDL_GetError() <<endl;
			SDL_Quit();
		}
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == NULL){
			SDL_DestroyWindow(win);
			cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
			SDL_Quit();
		}
	}
	class Sprite : public Animation{
		float x,dx,ax,y,dy,ay;
		public:
		Sprite():Animation()
		{
				x=0.0;
				dx=0.0;
				ax=0.0;
				y=0.0;
				dy=0.0;
				dx=0.0;
				
		}
		void addFrames(SDL_Renderer *ren, const char *imagPath, int count, int timePerFrame=100){
			for (int i =1;i<=count;i++)
			{
				stringstream ss;
				ss<<imagePath<<i<<".bmp";
				addFrame(new AnimationFrame(ren, ss.str().c_str(),timePerFrame));
				
			}
		}
		void show(SDL_Renderer*re, int time){
			Animation::
	};
	void done(){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}
	SDL_Renderer* getRenderer(){
		return ren;
	}
	void handleEvent(SDL_Event &event){
		
	}
};	
	
class NateGame:public Game{
	void handleEvent(SDL_Event *event){
		
	}
};
		
int main(int argc, char **argv)
	{

	Game g;
	g.init("Hello World!");
	Animation a;
	a.addFrame(new AnimationFrame(g.getRenderer(),"hello.bmp"));
	a.addFrame(new AnimationFrame(g.getRenderer(),"hello1.bmp",200));
	int start = SDL_GetTicks();
	bool done=false;
	while(!done)
	{
		SDL_Event event;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_WINDOWEVENT){
				if (event.window.event==SDL_WINDOWEVENT_CLOSE){
					done=true;
				}
			}
			if(event.type==SDL_KEYDOWN){
					if(event.key.keysym.sym==SDLK_ESCAPE)done=true;
				}
				if (!done) g.handleEvent(event);		
			}				
			int ticks=SDL_GetTicks();
			SDL_RenderClear(g.getRenderer());
			a.show(g.getRenderer(),ticks);
			SDL_RenderPresent(g.getRenderer());
		
	}
	a.destroy();
	g.done();
	return 0;
}


