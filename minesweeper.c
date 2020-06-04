#include <iostream> 
#include <iterator> 
#include <map> 
#include <string> 
#include <vector> 
#include <sstream>
#include "stdlib.h"


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
			bombsInNeighborhood = 0;
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
			isFlag = true;
		}

		void incrementBombsInNeighborhood(){
			if (!isBomb) {
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

		FieldManager(int l, int c, int n){
			lines = l;
			columns = c;
			numberOfBombs = n;
			generateBombPositions();

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
			map<int, bool>::iterator iter;
			//The position counter will know when the specified position is a bomb position.
			//It reach this objective checking on the bombPositions map.
			int positionCounter = 1;
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					key = toStr(lines) + "-" + toStr(columns);
					iter = bombsPositions.find(positionCounter);
					//If the current position is a bomb position, we will create the cell as bomb
					if (iter != bombsPositions.end()){
						field.insert(pair<string, Cell>(key, Cell(true)));
					}
					else {
						field.insert(pair<string, Cell>(key, Cell(false)));
					}
					positionCounter++;

				}
			}
			// update bombsInTheNeighborHood
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					if (getCellByCoordinates(i,j).getIsBomb()){
						incrementNeighborCells(i,j); 
					}
				}
			}
		}

		void generateBombPositions(){
			int randomNumber;
			map<int, bool>::iterator iter;
			int i = 1;
			while(i <= numberOfBombs){
				randomNumber = rand() % (lines*columns) + 1;
				iter = bombsPositions.find(randomNumber);
				//If the number isnt a bomb position, add it to the map.
				//If these number already exists on the map, we need to generate
				// other random number for a bomb position
				if (iter == bombsPositions.end()){
					bombsPositions.insert(pair<int, bool>(randomNumber, true)); 
					i++;
				}
			}


		}

		void incrementNeighborCells(int l, int c){
			//Check l-1 / c-1
			if (l-1 >= 1 && c-1 >= 1) {
				getCellByCoordinates(l-1, c-1).incrementBombsInNeighborhood();
			}

			//Check l-1 / c
			if (l-1 >= 1) {
				getCellByCoordinates(l-1, c).incrementBombsInNeighborhood();
			}

			//Check l-1 / c + 1
			if (l-1 >= 1 && c+1 <= columns) {
				getCellByCoordinates(l-1, c+1).incrementBombsInNeighborhood();
			}

			//Check l / c - 1
			if (c-1 >= 1) {
				getCellByCoordinates(l, c-1).incrementBombsInNeighborhood();
			}

			//Check l / c + 1
			if (c+1 <= columns) {
				getCellByCoordinates(l, c+1).incrementBombsInNeighborhood();
			}

			//Check l+1 / c - 1
			if (l+1 <= lines && c-1 >= 1) {
				getCellByCoordinates(l+1, c-1).incrementBombsInNeighborhood();
			}

			//Check l+1 / c
			if (l+1 <= lines) {
				getCellByCoordinates(l+1, c).incrementBombsInNeighborhood();
			}

			//Check l+1 / c+1
			if (l+1 <= lines && c+1 <= columns) {
				getCellByCoordinates(l+1, c+1).incrementBombsInNeighborhood();
			}
		}

		void printField(){

			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					cout << getCellByCoordinates(i, j).getBombsInNeighborhood() << " ";
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
		int numberOfBombs;
		map<string, Cell> field;
		map<int, bool> bombsPositions;

};


int main() 
{
	FieldManager teste = FieldManager(9, 5, 10);
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
