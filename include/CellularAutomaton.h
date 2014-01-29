#include <vector>
#include <rule.h>

class CellularAutomaton{
	private:
		std::vector<std::vector<int> > data;
		Rule rule;
		int NeighborhoodSum(int x, int y);
		bool CheckCondition(int value, std::vector<int> condition);

	public:
		CellularAutomaton();
		CellularAutomaton(Rule r, int sizex, int sizey);
		std::vector<std::vector<int> > GetData();
		std::vector<std::vector<int> > NextGeneration();
		void SetData(int x, int y, int d);
		void Clear();
};