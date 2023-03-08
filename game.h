#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include<string.h>
#include<conio.h>
#include<vector>
#include<math.h>

using namespace std;

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;
const string WINDOW_TITLE = "Window";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture( string path,SDL_Renderer* renderer );

