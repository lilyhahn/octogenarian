#include <CellularAutomaton.h>

class Cursor{
private:
	int x, y;

public:
	Cursor();
	Cursor(int x_, int y_);
	int GetX();
	int GetY();
	void Move(int amountX, int amountY);
	void Draw(CellularAutomaton& ca, int state);
	void SetPos(int posX, int posY);
};