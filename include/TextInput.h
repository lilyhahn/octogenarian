#include <string>
#include <SDL_TTF.h>
#include <SDL.h>

class TextInput{
private:
	TTF_Font* font;
	std::string text;
	bool typing;
	SDL_Color color;
	bool newlines;
public:
	bool IsEnabled();
	SDL_Surface* Render();
	void Start();
	void Stop();
	void Update(SDL_Event* event);
	std::string GetText();
	void SetText(std::string newText);
	TextInput(TTF_Font* fnt, SDL_Color clr);
	TextInput(TTF_Font* fnt, SDL_Color clr, bool useNewlines);
	~TextInput();
};