//MediaManager
#ifdef MEDIAMANAGER_HPP
#define MEDIAMANAGER_HPP
#include <string>
#include <map>
#include "SDL.h"
using namespace std;

class MediaManager {
	map<string,SDL_Texture*>images;
	public:
	SDL_Texture *readImage(SDL_Renderer *renderer, string filename);
};
extern MediaManager media;
