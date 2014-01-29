#include <SDL.h>
#include <vector>
#include <Cursor.h>
#include <CEvent.h>

class CApp : public CEvent{
private:
	bool Running;

	SDL_Surface* Surf_Display;

	int scale;

	void InitCA();

	void InitColors();

	CellularAutomaton automaton;

	Uint32 Color0;
	Uint32 Color1;
	Uint32 Color2;

	Uint32 CursorColor;

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

	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

};