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
		}

		void initializeField(){
			string key;
			for (int i = 1; i <= l; i++){
				for (int j = 1; j <= c; j++){
					key = to_string(l) + "-" + to_string(c)
					field.insert(pair<key, Cell>(1, Cell(false))); 
				}
			}
		}

		void printField(){
			Cell auxiliaryCell;

			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					auxiliaryCell = getCellByCoordinates(i, j);
					cout << auxiliaryCell.revealed;
				}
				cout << endl;
            }
			
		}

		Cell getCellByCoordinates(int line, int column){
				string key = to_string(line) + "-" + to_string(column)
				map<string, Cell>::iterator itr;
				itr = field.find(key);
				return itr->second;
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
