#include <Cursor.h>

Cursor::Cursor(){
	x = 0;
	y = 0;
}

Cursor::Cursor(int x_, int y_){
	x = x_;
	y = y_;
}

int Cursor::GetX(){
	return x;
}

int Cursor::GetY(){
	return y;
}

void Cursor::Draw(CellularAutomaton& ca, int state){
	ca.SetData(x, y, state);
}

void Cursor::Move(int amountX, int amountY){
	x += amountX;
	y -= amountY; //for some reason y is backwards?
}

void Cursor::SetPos(int posX, int posY){
	x = posX;
	y = posY;
}