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
			revealedCells = 0;
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
			map<int, string>::iterator iter;
			//The position counter will know when the specified position is a bomb position.
			//It reach this objective checking on the bombPositions map.
			int positionCounter = 1;
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					key = toStr(i) + "-" + toStr(j);
					iter = bombsPositions.find(positionCounter);
					//If the current position is a bomb position, we will create the cell as bomb
					if (iter != bombsPositions.end()){
						field.insert(pair<string, Cell>(key, Cell(true)));
						//Save its position at the bombPositions map
						iter->second = key;
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
			map<int, string>::iterator iter;
			int i = 1;
			while(i <= numberOfBombs){
				randomNumber = rand() % (lines*columns) + 1;
				iter = bombsPositions.find(randomNumber);
				//If the number isnt a bomb position, add it to the map.
				//If these number already exists on the map, we need to generate
				// other random number for a bomb position
				if (iter == bombsPositions.end()){
					bombsPositions.insert(pair<int, string>(randomNumber, " ")); 
					i++;
				}
			}


		}

		void incrementSingleNeighborCell(int l, int c){
			Cell cell = getCellByCoordinates(l, c);
			cell.incrementBombsInNeighborhood();
			updateCell(cell, l, c);
		}

		void incrementNeighborCells(int l, int c){
			//Check l-1 / c-1
			if (l-1 >= 1 && c-1 >= 1) {
				incrementSingleNeighborCell(l-1, c-1);
			}

			//Check l-1 / c
			if (l-1 >= 1) {
				incrementSingleNeighborCell(l-1, c);
			}

			//Check l-1 / c + 1
			if (l-1 >= 1 && c+1 <= columns) {
				incrementSingleNeighborCell(l-1, c+1);
			}

			//Check l / c - 1
			if (c-1 >= 1) {
				incrementSingleNeighborCell(l, c-1);
			}

			//Check l / c + 1
			if (c+1 <= columns) {
				incrementSingleNeighborCell(l, c+1);
			}

			//Check l+1 / c - 1
			if (l+1 <= lines && c-1 >= 1) {
				incrementSingleNeighborCell(l+1, c-1);
			}

			//Check l+1 / c
			if (l+1 <= lines) {
				incrementSingleNeighborCell(l+1, c);
			}

			//Check l+1 / c+1
			if (l+1 <= lines && c+1 <= columns) {
				incrementSingleNeighborCell(l+1, c+1);
			}
		}

		void printField(){
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					Cell auxiliaryCell = getCellByCoordinates(i,j);
					if (auxiliaryCell.getIsBomb()){
						cout << "B ";
					}
					else {
						cout << auxiliaryCell.getBombsInNeighborhood() << " ";
					}  
					
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

		void updateCell(Cell updatedCell, int l, int c){
			map<string, Cell>::iterator itr;
			string key = toStr(l) + "-" + toStr(c);
			itr = field.find(key);
			itr->second = updatedCell;
		}

		int chooseCell(int l, int c){
			int output;
			Cell cell = getCellByCoordinates(l, c)
			if cell.alreadyRevealed(){
				cout << "This cell have been already revealed! Choice other cell!"
			}
			else {
				if (cell.getIsBomb()){
					//show all bombs!
					//game over!
					for (int i = 1; i <= lines; i++){
						for (int j = 1; j <= columns; j++){
							Cell auxiliaryCell = getCellByCoordinates(i,j);
							//If the cell is a bomb, show it!
							if (auxiliaryCell.getIsBomb()){
								cout << "B ";
							}
							else {
								//If the cell has been revealed, show its value.
								if (auxiliaryCell.alreadyRevealed()){
									cout << auxiliaryCell.getBombsInNeighborhood() << " ";
								}
								else{
									//Else, stay it hidden, as the game does
									cout << "# ";
								}
							}
						}
						cout << endl;
           	 		}
					//output == 0 -> game over!	
					output = 0;
				}

				else if (cell.getBombsInNeighborhood() > 0){
					//Show only this cell!
				}

				else{
					//Show a group of cells!
				}
			}
		}


	private:
		int lines;
		int columns;
		int numberOfBombs;
		int revealedCells;
		map<string, Cell> field;
		map<int, string> bombsPositions;

};


int main() 
{
	FieldManager teste = FieldManager(15, 15, 20);
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
