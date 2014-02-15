#include <CellularAutomaton.h>
#include <iostream>
#include <RLE.h>


CellularAutomaton::CellularAutomaton(){

}

CellularAutomaton::CellularAutomaton(Rule r, int sizex, int sizey){
	rule = r;
	data.resize(sizex);
	for(int i = 0; i < data.size(); i++){
		data[i].resize(sizey);
	}
}

std::vector<std::vector<int> > CellularAutomaton::GetData(){
	return data;
}

void CellularAutomaton::SetData(int x, int y, int d){
	data[x][y] = d;
}

int CellularAutomaton::NeighborhoodSum(int x, int y){
	int neighborhoodSum = 0;
	if(data[x-1][y] == 1) neighborhoodSum++;
	if(data[x+1][y] == 1) neighborhoodSum++;
	if(data[x][y-1] == 1) neighborhoodSum++;
	if(data[x][y+1] == 1) neighborhoodSum++;
	if(data[x-1][y+1] == 1) neighborhoodSum++;
	if(data[x+1][y+1] == 1) neighborhoodSum++;
	if(data[x-1][y-1] == 1) neighborhoodSum++;
	if(data[x+1][y-1] == 1) neighborhoodSum++;
	/*neighborhoodSum += data[x-1][y];
	neighborhoodSum += data[x+1][y];
	neighborhoodSum += data[x][y-1];
	neighborhoodSum += data[x][y+1];
	neighborhoodSum += data[x-1][y+1];
	neighborhoodSum += data[x+1][y+1];
	neighborhoodSum += data[x-1][y-1];
	neighborhoodSum += data[x+1][y-1];*/
	return neighborhoodSum;
}

bool CellularAutomaton::CheckCondition(int value, std::vector<int> condition){
	for(int i = 0; i < condition.size(); i++){
		if(value == condition[i]) return true;
	}
	return false;
}

std::vector<std::vector<int> > CellularAutomaton::NextGeneration(){
	std::vector<std::vector<int> > nextData = data;
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[0].size(); j++){
			if(j < data[0].size()-1 && i < data.size()-1 && j > 1 && i > 1){ //if we are not at the edge
				int nsum = NeighborhoodSum(i, j);

				//if current cell is at the last count, set it to 0. if it's not at a stay position increment
				if(data[i][j] == (rule.c[rule.c.size() - 1] - 1)) nextData[i][j] = 0;
				else if(!CheckCondition(data[i][j], rule.s) && data[i][j]){
					nextData[i][j] += 1;
				}

				else if(CheckCondition(nsum, rule.b) && !data[i][j]){
					nextData[i][j] = 1;
				}
			}
		}
	}
	data = nextData;
	return data;
}

void CellularAutomaton::Clear(){
	int size = data.size();
	for(int i = 0; i < size; i++){
		data[i].clear();
	}
	for(int i = 0; i < size; i++){
		data[i].resize(size);
	}
}
Rule CellularAutomaton::GetRule(){
	return rule;
}

bool IsEmpty(std::vector<int> arr){
	for(int i = 0; i < arr.size(); i++){
		if(arr[i]) return false;
	}
	return true;
}

void CellularAutomaton::SaveMCL(std::string file){
	bool empty = false;
	std::ofstream out (file.c_str(), std::ofstream::out);
	out << "#MCell 4.00\n";
	out << "#GAME Generations\n";
	out << "#BOARD " << data.size() << "x" << data[0].size() << std::endl;
	//out << "#RULE " << rule.s << "/" << rule.b << "/" << rule.c << std::endl;
	std::string to_encode = "";
	for(int i = 0; i < data.size(); i++){
		if(encode(to_encode).size() >= 50){
			out << "#L " << encode(to_encode) << std::endl;
			to_encode = "";
		}
		for(int j = 0; j < data[0].size(); j++){
			if(IsEmpty(data[i])){
				empty = true;
				break;
			}
			if(!data[i][j]) to_encode += ".";
			else{
				to_encode += char(data[i][j] + 64);
			}
		}
		//if(!empty)
			to_encode += "$";
	}
	out << "#L " << encode(to_encode);
}