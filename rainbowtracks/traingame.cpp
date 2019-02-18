//train\

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class AnimationFrame {
	SDL_Texture *frame;
	int time,x,y w,h;
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
			SDL SetColorKey(bmp,SDL TRUE, SDL MapRGB(bmp->format,0,255,0));
			w=bmp->w;
			h=bmp->h;
			frame = SDL CreateTExtureFromSurface(ren, bmp);
			SDL FreeSurface(bmp);
			if (frame == NULL){
				std::cout<"SDL_CreateTextureFromSurfaceError:"<<SDL_GetError()<<std::endl;
				SDL Quit();
			}
				time = newTime;
		}
		void show(SDL_Renderer *ren,x=0,y=0){
			SDL Rect src,dest;
			dest.x=x; dest.y=y; dest.w=w; dest.h=h;
			src.x=0; src.y=0; src.w=w; src.h=h;
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
	protected:
	vector<AnimationFrame *> frames;
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
		virtual void show(SDL_Renderer *ren, int time /*ms*/, int x = 0, int y = 0){
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
	
class Sprite : public Animation{
	float x, dx,ax;
	public:
	Sprite():Animation(){
		x=0.0; dx=0.0; ax=0.0;
	}
	void addFrames(SDL_Renderer *re, const char imagPath, int count){
	}
	void update()
	{
		x+=dx;
	}
	
};
class Game{
	protected:
	SDL_Window *win;
	SDL_Renderer *ren;
	int ticks;
	bool finished;
	public:
	virtual void init(const char *gameName, int maxW=1280, int maxH=720, 
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
	virtual void done(){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}
	void run(){
		int start = SDL_GetTicks();
		finished = false;
		while(!finished){
			SDL Event event;
			if (SDL_PollEvent(&event)){
				if (event.type == SDL WINDOWEVENT){
					if(event.window.event == SDL WINDOWEVENT CLOSE)
						finisehd = true;
					
				}
				if (event.type == SDL KEYDOWN) {
					if(event.key.keysym.sym == SDLK ESCAPE)
						finished = true;
				}
				if(!finished) handleEvent(event);
			}
			ticks=SDL GetTicks();
			SDL_RenderClear(ren);
			show();
			SDL RenderPresent(ren);
		}
		int end = SDL_GetTicks();
		cout << "FPS" << (300.0*1000.0/float(end-start))<<endl;
	}
	virtual void show()=0;
	virtual void handleEvent(SDL_Event &event) = 0;
};

class TrainGame: public Game {
	int score = 0;
	
	Animation a;
	Animation train;//world is not being used its a test
	//other stuff you are animating
	
	int x;//only going in x direction
	int dx;
	public:
	void init(const char *gameName="Train Game", int maxW=640, int maxH = 480, int startX = 100, int startY = 100){
		Game::init(gameName);
		a.addFrame(new AnimationFrame(ren,"desert.bmp"));
		//add more frames per animation
		dx=1;
		x=0;
		/*
		for (int i=1; i<=8;i++){
			stringstream ss;
			ss<<"Planet"<< i <<".bmp";
			world.addFrame(newAnimation(ren,sst.str().c,100));
		}*/
	}
	void show(){
		a.show(ren,ticks, x,y);
		train.show(ren,ticks, x,y);
		train.update();
		//x+=dx;
	}
	void handleEvent(SDL Event &event, bool &button,int trainpos){
		switch(event.type) {
			if(event.key.keysym.sym == SDLK_a{
				if (x == 35)
				score+=1;
			}
			if(event.key.keysym.sym == SDLK_s{
				
			}
			if(event.key.keysym.sym == SDLK_d{
				
			}
			if(event.key.keysym.sym == SDLK_f{
				
			}
			
		}	
	}

	
	void done(){
		a.destroy();
		Game::done();
	}
};
	
	


int main(int argc, char **argv)
{
	TrainGame g;
	g.init();
	g.run();
	g.done();
	return 0;

	
}

