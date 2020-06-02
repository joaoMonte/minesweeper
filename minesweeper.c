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


int main() 
{
	return 0;
} 
