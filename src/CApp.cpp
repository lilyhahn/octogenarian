#include <CApp.h>


CApp::CApp(){
	//Surf_Display = NULL;
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
 	
 	SDL_DisplayMode videoInfo; 
 	SDL_GetCurrentDisplayMode(0, &videoInfo);
 	screenWidth = videoInfo.w;
 	screenHeight = videoInfo.h;
 	//screenWidth = 640;
 	//screenHeight = 480;
    sdlWindow = SDL_CreateWindow("Octogenarian",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             0, 0,
                            SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(sdlWindow, -1, 0);

    cursor = Cursor((screenWidth / scale) / 2, (screenHeight / scale) / 2);

    for(int i = 0; i < 322; i++) { // init them all to false
   		KEYS[i] = false;
	}

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
	SDL_SetRenderDrawColor(renderer, Colors[0].r,  Colors[0].b, Colors[0].g, 255);
	SDL_RenderClear(renderer);
	SDL_Rect cur = {cursor.GetX() * scale, cursor.GetY() * scale, scale, scale};
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[0].size(); j++){
			SDL_Rect cell = {i * scale, j * scale, scale, scale};
			if(data[i][j])
				SDL_SetRenderDrawColor(renderer, Colors[data[i][j]].r,  Colors[data[i][j]].b, Colors[data[i][j]].g, 255);
				SDL_RenderFillRect(renderer, &cell);
		}
	}
	if(paused){
		SDL_SetRenderDrawColor(renderer, CursorColor.r,  CursorColor.b, CursorColor.g, 255);
		SDL_RenderDrawRect(renderer, &cur);
	}
	//SDL_Delay(1000);
	SDL_RenderPresent(renderer);
	//SDL_Flip(Surf_Display);
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
	Colors[0].r = 255;
	Colors[0].b = 255;
	Colors[0].g = 255;
	Colors[1].r = 2;
	Colors[1].b = 227;
	Colors[1].g = 145;
	Colors[2].r = 227;
	Colors[2].b = 2;
	Colors[2].g = 84;
	Colors[3] = Colors[2];
	Colors[4] = Colors[2];
	Colors[5] = Colors[2];
	Colors[6] = Colors[2];
	Colors[7] = Colors[2];
	Colors[8] = Colors[2];
	Colors[9] = Colors[2];
	CursorColor.r = 105;
	CursorColor.b = 105;
	CursorColor.g = 105;
}

void CApp::OnExit(){
	Running = false;
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod){
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

void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod){
	if(sym == SDLK_w)
		cursor.Move(0, 5);
	if(sym == SDLK_s)
		cursor.Move(0, -5);
	if(sym == SDLK_d)
		cursor.Move(5, 0);
	if(sym == SDLK_a)
		cursor.Move(-5, 0);
}
