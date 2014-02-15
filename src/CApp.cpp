#include <CApp.h>


CApp::CApp(){
	Surf_Display = NULL;
	Running = true;
	paused = true;
	scale = 4;
	brush = 1;
}

int CApp::OnExecute(){
	if(!OnInit()){
		return -1;
	}

	SDL_Event Event;

	while(Running){
		while(SDL_PollEvent(&Event)){
			OnEvent(&Event);
		}

		OnRender();
		OnLoop();
	}

	OnCleanup();

	return 0;

}

bool CApp::OnInit(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
 	
 	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
 	screenWidth = videoInfo->current_w;
 	screenHeight = videoInfo->current_h;
 	//screenWidth = 640;
 	//screenHeight = 480;
    if((Surf_Display = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL) {
        return false;
    }

    cursor = Cursor((screenWidth / scale) / 2, (screenHeight / scale) / 2);

    for(int i = 0; i < 322; i++) { // init them all to false
   		KEYS[i] = false;
	}

	SDL_EnableKeyRepeat(0,0);

	InitColors();
	InitCA();

	return true;

}

void CApp::OnEvent(SDL_Event* Event){
    CEvent::OnEvent(Event);
}

void CApp::HandleInput(){
	/*if(KEYS[SDLK_ESCAPE]) Running = false;
	if(KEYS[SDLK_UP]) cursor.Move(0, 1);
	if(KEYS[SDLK_DOWN]) cursor.Move(0, -1);
	if(KEYS[SDLK_RIGHT]) cursor.Move(1, 0);
	if(KEYS[SDLK_LEFT]) cursor.Move(-1, 0);
	if(KEYS[SDLK_SPACE]) cursor.Draw(automaton, 1);
	if(KEYS[SDLK_RETURN]) paused = !paused;*/
}

void CApp::OnLoop(){
	if(!paused)
		automaton.NextGeneration();
}

void CApp::OnRender(){
	std::vector<std::vector<int> > data = automaton.GetData();
	SDL_FillRect(Surf_Display, NULL, Colors[0]);
	SDL_Rect cur = {cursor.GetX() * scale, cursor.GetY() * scale, scale, scale};
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[0].size(); j++){
			SDL_Rect cell = {i * scale, j * scale, scale, scale};
			if(data[i][j])
				SDL_FillRect(Surf_Display, &cell, Colors[data[i][j]]);
		}
	}
	if(paused) SDL_FillRect(Surf_Display, &cur, CursorColor);
	//SDL_Delay(1000);
	SDL_Flip(Surf_Display);
}

void CApp::OnCleanup(){
	SDL_Quit();
}

void CApp::InitCA(){
	Rule rule;
	rule.s.push_back(0);
	rule.b.push_back(2);
	rule.c.push_back(3);
	automaton = CellularAutomaton(rule, screenWidth / scale, screenHeight / scale);
	/*unsigned long seedPosX =  automaton.GetData().size() / 2;
	unsigned long seedPosY = automaton.GetData()[0].size() / 2;

	automaton.SetData(seedPosX, seedPosY, 1);
	automaton.SetData(seedPosX, seedPosY - 1, 1);*/
}

void CApp::InitColors(){
	Colors[0] = SDL_MapRGB(Surf_Display->format, 255, 255, 255);
	Colors[1] = SDL_MapRGB(Surf_Display->format, 2, 227, 145);
	Colors[2] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[3] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[4] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[5] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[6] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[7] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[8] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Colors[9] = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	CursorColor = SDL_MapRGBA(Surf_Display->format, 105, 105, 105, 100);
}

void CApp::OnExit(){
	Running = false;
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch(sym){
		case SDLK_ESCAPE:
			Running = false;
			break;
		case SDLK_RETURN:
			paused = !paused;
			break;
		case SDLK_UP:
			cursor.Move(0, 1);
			break;
		case SDLK_DOWN:
			cursor.Move(0, -1);
			break;
		case SDLK_RIGHT:
			cursor.Move(1, 0);
			break;
		case SDLK_LEFT:
			cursor.Move(-1, 0);
			break;
		case SDLK_SPACE:
			cursor.Draw(automaton, brush);
			break;
		case SDLK_n:
			automaton.NextGeneration();
			break;
		case SDLK_1:
			brush = 1;
			break;
		case SDLK_2:
			brush = 2;
			break;
		case SDLK_3:
			brush = 3;
			break;
		case SDLK_4:
			brush = 4;
			break;
		case SDLK_5:
			brush = 5;
			break;
		case SDLK_6:
			brush = 6;
			break;
		case SDLK_7:
			brush = 7;
			break;
		case SDLK_8:
			brush = 8;
			break;
		case SDLK_9:
			brush = 9;
			break;
		case SDLK_0:
			brush = 0;
			break;
		case SDLK_c:
			automaton.Clear();
			break;
		case SDLK_e:
			automaton.SaveMCL("test.mcl");
			break;
	}
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
	if(sym == SDLK_w)
		cursor.Move(0, 5);
	if(sym == SDLK_s)
		cursor.Move(0, -5);
	if(sym == SDLK_d)
		cursor.Move(5, 0);
	if(sym == SDLK_a)
		cursor.Move(-5, 0);
}
