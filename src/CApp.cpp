#include <CApp.h>

CApp::CApp(){
	Surf_Display = NULL;
	Running = true;
	scale = 4;
};

int CApp::OnExecute(){
	if(!OnInit()){
		return -1;
	}

	SDL_Event Event;

	while(Running){
		while(SDL_PollEvent(&Event)){
			OnEvent(&Event);
		}

		HandleInput();
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


    for(int i = 0; i < 322; i++) { // init them all to false
   		KEYS[i] = false;
	}

	SDL_EnableKeyRepeat(0,0);

	InitColors();
	InitCA();

	return true;

}

void CApp::OnEvent(SDL_Event* Event){
	switch (Event->type) {
    // exit if the window is closed
    case SDL_QUIT:
        Running = false; // set game state to done
        break;
    // check for keypresses
    case SDL_KEYDOWN:
        KEYS[Event->key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        KEYS[Event->key.keysym.sym] = false;
        break;
    default:
        break;
    }
}

void CApp::HandleInput(){
	if(KEYS[SDLK_ESCAPE]) Running = false;
}

void CApp::OnLoop(){
	automaton.NextGeneration();
}

void CApp::OnRender(){
	std::vector<std::vector<int> > data = automaton.GetData();
	SDL_FillRect(Surf_Display, NULL, Color0);
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[0].size(); j++){
			//if(data[i][j]){
			SDL_Rect cell = {i * scale, j * scale, scale, scale};
			switch(data[i][j]){
				case 0:
					SDL_FillRect(Surf_Display, &cell, Color0);
					break;
				case 1:
					SDL_FillRect(Surf_Display, &cell, Color1);
					break;
				case 2:
					SDL_FillRect(Surf_Display, &cell, Color2);
					break;
				default: //if we don't have a color for this, do the last one
					SDL_FillRect(Surf_Display, &cell, Color2);
					break;
			}
			//}
		}
	}
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
	unsigned long seedPosX =  automaton.GetData().size() / 2;
	unsigned long seedPosY = automaton.GetData()[0].size() / 2;

	automaton.SetData(seedPosX, seedPosY, 1);
	automaton.SetData(seedPosX, seedPosY - 1, 1);
}

void CApp::InitColors(){
	Color0 = SDL_MapRGB(Surf_Display->format, 255, 255, 255);
	Color1 = SDL_MapRGB(Surf_Display->format, 227, 2, 84);
	Color2 = SDL_MapRGB(Surf_Display->format, 2, 227, 145);
}