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


