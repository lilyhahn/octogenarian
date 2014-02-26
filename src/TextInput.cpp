#include <TextInput.h>
#include <cstdlib>

void TextInput::Start(){
	SDL_StartTextInput();
	typing = true;
}

void TextInput::Stop(){
	SDL_StopTextInput();
	typing = false;
}

std::string TextInput::GetText(){
	return text;
}

void TextInput::SetText(std::string newText){
	text = newText;
}

void TextInput::Update(SDL_Event* event){
	if(!typing)
		return;
	switch(event->type){
		case SDL_TEXTINPUT:
			text += event->text.text;
			break;
		case SDL_KEYDOWN:
			if(event->key.keysym.sym == SDLK_RETURN && newlines)
				text += "\n";
			if(event->key.keysym.sym == SDLK_BACKSPACE)
				text = text.substr(0, text.length() - 1);
			break;
	}
}

SDL_Surface* TextInput::Render(){
	return TTF_RenderText_Blended(font, text.c_str(), color);
}

TextInput::TextInput(TTF_Font* fnt, SDL_Color clr){
	newlines = true;
	font = fnt;
	color = clr;
	typing = false;
}

TextInput::TextInput(TTF_Font* fnt, SDL_Color clr, bool useNewlines){
	newlines = useNewlines;
	font = fnt;
	color = clr;
	typing = false;
}

TextInput::~TextInput(){
	free(font);
}

bool TextInput::IsEnabled(){
	return typing;
}