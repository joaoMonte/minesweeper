#include <iostream> 
#include <iterator> 
#include <map> 
#include <string> 
#include <vector> 
#include <sstream>


using namespace std; 

class Queue {
	public:
		void enqueue(string cellCoordinates){
			buffer.push_back(cellCoordinates);
		}

		string dequeue(){
			string auxiliaryString = buffer[0];
			buffer.erase(buffer.begin());
			return auxiliaryString;
		}

		bool isEmpty(){
			return buffer.size() == 0;
		}

	private:
		vector<string> buffer;
};

class Cell {
	public:
		Cell(bool isbomb){
			isBomb = isbomb;
			revealed = false;
			isFlag = false;
			bombsInNeighborhood = 0
		}

		void reveal(){
			revealed = true;
		}

		bool alreadyRevealed(){
			return revealed;
		}

		bool getIsBomb(){
			return isBomb;
		}

		void setFlag(){
			isFlag = true
		}

		void incrementBombsInNeighborhood(){
			if !isBomb {
				bombsInNeighborhood++;
			}
		}

		int getBombsInNeighborhood(){
			return bombsInNeighborhood;
		}

	private:
		bool revealed;
		bool isFlag;
		bool isBomb;
		int bombsInNeighborhood;

};


class FieldManager {
	public:

		FieldManager(int l, int c){
			lines = l;
			columns = c;
		}

		string toStr(int number){
			string auxiliaryString;
			stringstream strstream;
			strstream << number;
			return strstream.str();
		}

		void initializeField(){
			//Fill the field with cell instances
			string key;
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					key = toStr(lines) + "-" + toStr(columns);
					field.insert(pair<string, Cell>(key, Cell(false))); 
				}
			}
			// update bombsInTheNeighborHood
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					if getCellByCoordinates(l,c).getIsBomb(){
						incrementNeighborCells(l, c); 
					}
				}
			}


		}

		void incrementNeighborCells(l, c){
			//Check l-1 / c-1
			if l-1 >= 1 && c-1 >= 1 {
				getCellByCoordinates(l-1, c-1).incrementBombsInNeighborhood();
			}

			//Check l-1 / c
			if l-1 >= 1 {
				getCellByCoordinates(l-1, c).incrementBombsInNeighborhood();
			}

			//Check l-1 / c + 1
			if l-1 >= 1 && c+1 <= columns {
				getCellByCoordinates(l-1, c+1).incrementBombsInNeighborhood();
			}

			//Check l / c - 1
			if c-1 >= 1 {
				getCellByCoordinates(l, c-1).incrementBombsInNeighborhood();
			}

			//Check l / c + 1
			if c+1 <= columns {
				getCellByCoordinates(l, c+1).incrementBombsInNeighborhood();
			}

			//Check l+1 / c - 1
			if l+1 <= lines && c-1 >= 1 {
				getCellByCoordinates(l+1, c-1).incrementBombsInNeighborhood();
			}

			//Check l+1 / c
			if l+1 <= lines {
				getCellByCoordinates(l+1, c).incrementBombsInNeighborhood();
			}

			//Check l+1 / c+1
			if l+1 <= lines && c+1 <= columns {
				getCellByCoordinates(l+1, c+1).incrementBombsInNeighborhood();
			}
		}

		void printField(){

			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					cout << getCellByCoordinates(i, j).revealed;
				}
				cout << endl;
            }
			
		}

		Cell getCellByCoordinates(int line, int column){
				string key = toStr(line) + "-" + toStr(column);
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
	FieldManager teste = FieldManager(9, 5);
	teste.initializeField();
	teste.printField();
	//Cell t1 = Cell(false);
	//map<int, Cell> teste; 
	//map<int, Cell>::iterator itr;
	
	//teste.insert(pair<int, Cell>(1, t1)); 
	//itr = teste.find(1);
	//cout << itr->second.isBomb;

	return 0;
} 
