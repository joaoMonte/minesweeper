#include <iostream> 

using namespace std; 

class Cell {
	public:
		bool revealed;
		bool isFlag;
		bool isBomb;
		Cell(bool isbomb){
			isBomb = isbomb;
			revealed = false;
			isFlag = false;
		}

};


class FieldCreator {
	public:
		Field(int c, int l){
			lines = l;
			columns = c;
			field = new Cell[l][c]
			
			for (int i = 0; i < l; i++){
				for (int j = 0; j < c; j++){
					field[i][j] = Cell(false);
				}
			}
		}


	private:
		int lines;
		int columns;
		Cell* field;

}


int main() 
{
	return 0;
} 
