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
					if (auxiliaryCell.alreadyRevealed()){
						cout << auxiliaryCell.getBombsInNeighborhood() << " ";
					}
					else {
						cout << "# ";
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

		void revealCell(int l, int c){
			Cell cell = getCellByCoordinates(l, c);
			cell.reveal();
			revealedCells++;
			updateCell(cell, l, c);
		}

		int chooseCell(int l, int c){
			int output;
			Cell cell = getCellByCoordinates(l, c);
			if (cell.alreadyRevealed()){
				cout << "This cell have been already revealed! Choice other cell!";
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

				else {

					//Show only this cell!
					revealCell(l, c);

					if (cell.getBombsInNeighborhood() == 0){
						//if this cell hasn't a number, we need to check if
						//there are more cells to reveal! it will be did by the method
						//revealgroupofCells
						revealGroupOfCells(l, c);
					}

					printField();
					//output == 1 -> still playing
					//output == 2 -> user won!
					if (didUserWin()) {
						output = 2;
					}
					else {
						output = 1;
					}

				}
			}
		}

		vector<int> split(string str){
			vector<int> output;
			string buffer = "";
			int i = 0;
			int number;
			while (i < str.length()){
				if (str[i] != '-'){
					buffer += str[i];
				}
				else{
					number = std::stoi(buffer)
					output.push_back(number);
					buffer = "";
				}
				i++;
			}
			return output;
		}


		void revealGroupOfCells(int starter_l, int starter_c){
			//This method traverse the field map to select the cells which will be showed
			//Its use an
			Queue queue = Queue();
			string key = toStr(starter_l) + "-" + toStr(starter_c);
			vector<int> coordinates;
			queue.enqueue(key);
			int l;
			int c;

			while (!queue.isEmpty()) {
				
				key = queue.dequeue();
				coordinates = split(key);
				l = coordinates[0];
				c = coordinates[1];

				Cell currentCell = getCellByCoordinates(l,c);
				if (!currentCell.alreadyRevealed()){
					//If the cell has not been revealed, reveal it!
					revealCell(l, c);
				}

				//Check l-1 / c-1
				//If it is a 0/empty cell we add it the queue to ve analysed about its neighbor at next iteration
				//else, we just reveal it
				if (l-1 >= 1 && c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l-1) + "-" + toStr(c-1));
					}
					else{
						revealCell(l-1, c-1);
					}

				}

				//Check l-1 / c
				if (l-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l-1) + "-" + toStr(c));
					}
					else{
						revealCell(l-1, c);
					}
				}

				//Check l-1 / c + 1
				if (l-1 >= 1 && c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l-1) + "-" + toStr(c+1));
					}
					else{
						revealCell(l-1, c+1);
					}
				}

				//Check l / c - 1
				if (c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l) + "-" + toStr(c-1));
					}
					else{
						revealCell(l, c-1);
					}
				}

				//Check l / c + 1
				if (c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l) + "-" + toStr(c+1));
					}
					else{
						revealCell(l, c+1);
					}
				}

				//Check l+1 / c - 1
				if (l+1 <= lines && c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l+1) + "-" + toStr(c-1));
					}
					else{
						revealCell(l+1, c-1);
					}
				}

				//Check l+1 / c
				if (l+1 <= lines) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l+1) + "-" + toStr(c));
					}
					else{
						revealCell(l+1, c);
					}
				}

				//Check l+1 / c+1
				if (l+1 <= lines && c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0){
						queue.enqueue(toStr(l+1) + "-" + toStr(c+1));
					}
					else{
						revealCell(l+1, c+1);
					}
				}
			} 
		}


		bool didUserWin(){
			return revealedCells + numberOfBombs == lines * columns;
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
	teste.split("12-12");
	//teste.initializeField();
	//teste.printField();
	//Cell t1 = Cell(false);
	//map<int, Cell> teste; 
	//map<int, Cell>::iterator itr;
	
	//teste.insert(pair<int, Cell>(1, t1)); 
	//itr = teste.find(1);
	//cout << itr->second.isBomb;

	return 0;
} 
