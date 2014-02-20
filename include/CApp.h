#include <SDL.h>
#include <vector>
#include <Cursor.h>
#include <CEvent.h>

class CApp : public CEvent{
private:
	bool Running;

	SDL_Window *sdlWindow;
	SDL_Renderer *renderer;
	SDL_Texture *sdlTexture;

	int scale;

	void InitCA();

	void InitColors();

	CellularAutomaton automaton;

	SDL_Color Colors[10];

	SDL_Color CursorColor;

	Cursor cursor;

	bool paused;

	int brush;


public:
	int screenWidth, screenHeight;

	bool KEYS[322];
	
	CApp();

	int OnExecute();

	bool OnInit();

	void OnEvent(SDL_Event* Event);

	void HandleInput();

	void OnLoop();

	void OnRender();

	void OnCleanup();

	void OnExit();

	void OnKeyUp(SDL_Keycode sym, Uint16 mod);

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

};