#include <iostream> 

using namespace std; 

class Cell {
	public:
		bool revealed;
		bool isBomb;
		Cell(bool isbomb){
			isBomb = isbomb;
			revealed = false;
		}

};


class Field {
	public:
		int lines;
		int columns;
		Field(int c, int l){
			lines = l;
			columns = c;
		}

}


int main() 
{
	return 0;
} 
