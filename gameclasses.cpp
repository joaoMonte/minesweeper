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

int Utils :: toInt(string str){
	//Simple cast operation

	stringstream auxiliary(str); 
	int output; 
    auxiliary >> output;
	return output; 
}

string Utils :: toStr(int number){
    //Simple cast operation

	string auxiliaryString;
	stringstream strstream;
	strstream << number;
	return strstream.str();
}

vector<int> Utils :: split(string str){
    //Auxilary method which breaks an coordinate string into two ints!
    vector<int> output;
    string buffer = "";
    int i = 0;
    int number;
    while (i < str.length()){
        if (str[i] != '-'){
            buffer += str[i];
        }
        else{
            number = toInt(buffer);
            output.push_back(number);
            buffer = "";
        }
        i++;
    }
    //add the last buffer to the output. 
    //Because the loop exits before did it
    number = toInt(buffer);
    output.push_back(number);
    return output;
}

