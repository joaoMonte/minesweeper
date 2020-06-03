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
			nextBombsCounter = 0
		}

		void reveal(){
			revealed = true;
		}

		bool alreadyRevealed(){
			return revealed;
		}

		void setFlag(){
			isFlag = true
		}

		void incrementNextBombsCounter(){
			nextBombsCounter++;
		}

		int getNextBombsCounter(){
			return nextBombsCounter;
		}
		
	private:
		bool revealed;
		bool isFlag;
		bool isBomb;
		int nextBombsCounter;

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
			string key;
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					key = toStr(lines) + "-" + toStr(columns);
					field.insert(pair<string, Cell>(key, Cell(false))); 
				}
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
