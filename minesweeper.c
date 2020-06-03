#include <iostream> 
#include <iterator> 
#include <map> 
#include <string> 


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


class FieldManager {
	public:
		FieldManager(int c, int l){
			lines = l;
			columns = c;
			field = new Cell[l][c];
			
			for (int i = 1; l < i; i++){
				for (int j = 1; j < i; j++){
					teste.insert(pair<int, Cell>(1, Cell(false))); 
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
		map<string, Cell> field;

};


int main() 
{
	Cell t1 = Cell(false);
	map<int, Cell> teste; 
	map<int, Cell>::iterator itr;
	
	teste.insert(pair<int, Cell>(1, t1)); 
	itr = teste.find(1);
	cout << itr->second.isBomb;

	return 0;
} 
