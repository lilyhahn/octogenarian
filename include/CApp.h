#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <Cursor.h>
#include <CEvent.h>
#include <TextInput.h>

class CApp : public CEvent{
private:
	bool Running;

	SDL_Window *sdlWindow;
	SDL_Renderer *renderer;
	SDL_Texture *sdlTexture;
	SDL_Surface* Surf_Display;

	int scale;

	void InitCA();

	void InitColors();

	CellularAutomaton automaton;

	Uint32 Colors[10];

	Uint32 CursorColor;

	Cursor cursor;

	bool paused;

	int brush;

	std::string text;

	bool typing;

	TextInput* textInput;

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