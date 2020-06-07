#include <iostream> 
#include <iterator> 
#include <sstream>
#include "stdlib.h"
#include "gameclasses.h"

using namespace std;


void Queue :: enqueue(string cellCoordinates){
	buffer.push_back(cellCoordinates);
}

string Queue :: dequeue(){
	string auxiliaryString = buffer[0];
	buffer.erase(buffer.begin());
	return auxiliaryString;
}

bool Queue :: isEmpty(){
	return buffer.size() == 0;
}

Cell :: Cell (bool isbomb)
    :isBomb(isbomb), revealed(false), isFlag(false), bombsInNeighborhood(0)
{}

void Cell :: reveal(){
	revealed = true;
}

bool Cell :: alreadyRevealed(){
	return revealed;
}

bool Cell :: getIsBomb(){
	return isBomb;
}

void Cell :: setFlag(){
	isFlag = true;
}

bool Cell :: getIsFlag(){
	return isFlag;
}

void Cell :: incrementBombsInNeighborhood(){
	if (!isBomb) {
		bombsInNeighborhood++;
	}
}

int Cell :: getBombsInNeighborhood(){
	return bombsInNeighborhood;
}


