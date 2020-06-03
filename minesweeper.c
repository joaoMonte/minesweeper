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
		FieldCreator(int c, int l){
			lines = l;
			columns = c;
			field = new Cell[l][c];
			
			for (int i = 0; i < l; i++){
				for (int j = 0; j < c; j++){
					field[i][j] = Cell(false);
				}
			}
		}
		void printField(){
			Cell auxiliaryCell;
			 for (int i = 0; i < lines; i++){
                                for (int j = 0; j < columns; j++){
                                        auxiliaryCell = field[i][j];
					cout << auxiliaryCell.revealed;
                                }
				cout << endl;
                        }
			
		}


	private:
		int lines;
		int columns;
		Cell** field;

};


int main() 
{
	return 0;
} 
