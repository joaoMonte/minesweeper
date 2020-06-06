#include <iostream> 
#include <iterator> 
#include <map> 
#include <string> 
#include <vector> 
#include <sstream>
#include "stdlib.h"




using namespace std; 

#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define YELLOW  "\033[33m" 

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
						if (auxiliaryCell.getBombsInNeighborhood() > 0){
							cout << BLUE << auxiliaryCell.getBombsInNeighborhood() << " " << RESET;
						}
						else {
							cout << WHITE << auxiliaryCell.getBombsInNeighborhood() << " " << RESET;
						}
					}
					else {
						cout << "# ";
					}  
					
				}
				cout << endl;
            }
			cout << endl;
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
				cout << "This cell have been already revealed! Choice other cell!" << endl;
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
								cout << RED << "B " << RESET;
							}
							else {
								//If the cell has been revealed, show its value.
								if (auxiliaryCell.alreadyRevealed()){
									if (auxiliaryCell.getBombsInNeighborhood() > 0){
										cout << BLUE << auxiliaryCell.getBombsInNeighborhood() << " " << RESET;
									}
									else {
										cout << WHITE << auxiliaryCell.getBombsInNeighborhood() << " " << RESET;
									}
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

		int toInt(string str){
			stringstream auxiliary(str); 
			int output; 
    		auxiliary >> output;
			return output; 
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
					number = toInt(buffer);
					output.push_back(number);
					buffer = "";
				}
				i++;
			}
			//add the last buffer to the outpu. 
			//Because the loop exits before did it
			number = toInt(buffer);
			output.push_back(number);
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
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l-1) + "-" + toStr(c-1));
					}
					else{
						revealCell(l-1, c-1);
					}

				}

				//Check l-1 / c
				if (l-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l-1) + "-" + toStr(c));
					}
					else{
						revealCell(l-1, c);
					}
				}

				//Check l-1 / c + 1
				if (l-1 >= 1 && c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l-1) + "-" + toStr(c+1));
					}
					else{
						revealCell(l-1, c+1);
					}
				}

				//Check l / c - 1
				if (c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l) + "-" + toStr(c-1));
					}
					else{
						revealCell(l, c-1);
					}
				}

				//Check l / c + 1
				if (c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l) + "-" + toStr(c+1));
					}
					else{
						revealCell(l, c+1);
					}
				}

				//Check l+1 / c - 1
				if (l+1 <= lines && c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l+1) + "-" + toStr(c-1));
					}
					else{
						revealCell(l+1, c-1);
					}
				}

				//Check l+1 / c
				if (l+1 <= lines) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l+1) + "-" + toStr(c));
					}
					else{
						revealCell(l+1, c);
					}
				}

				//Check l+1 / c+1
				if (l+1 <= lines && c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
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
	//teste.initializeField();
	//teste.chooseCell(1,1);
	//teste.chooseCell(1,1);
	//teste.chooseCell(1,2);
	//teste.chooseCell(1,3);
	//teste.chooseCell(15,3);
	//teste.chooseCell(5,15);
	//teste.chooseCell(2,12);
	//teste.chooseCell(3,5);

	int numberOfBombs = 20;
	int lines = 10;
	int columns = 10
	string option = "";
	bool validSetup = false;

	while (option != "Exit"){
		cout << RED << "-------------------------------" << RESET << endl; 
		cout << RED << "----------" << YELLOW << "MINESWEEPER" << RED << "----------" << endl;
		cout << RED << "-------------------------------" << RESET << endl;
		cout << ">> Type" << endl << ">> Start - begin the game" << ">> Options - choose the game settings" << endl;
		cout << ">> Exit - closes the application" << endl;
		cout << ">> "
		cin >> option;

		if (option == "Start"){
			//start the game
			cout << ">> The game will start!" << endl;
		}
		else if (option == "Options"){
			do {
				//go to settings
				cout << ">> Type the number of lines of your minesweeper field! (default: 10)" << endl << ">> ";
				cin >> lines;
				cout << ">> Type the number of columns of your minesweeper field! (default: 10)" << endl << ">> ";
				cin >> columns;
				cout << ">> Type the number of bombs of your minesweeper field! (default: 10)" << endl << ">> ";
				cin >> numberOfBombs;

				if (numberOfBombs < lines * columns){
					validSetup = true;
				}
				else{
					cout << endl << ">> Your setup is invalid. The field must have at least 1 cell which isn't a bomb."
					count << endl << ">> Try again" << endl;
				}

			} while(!validSetup)
		}
		else if (option != "Start" && option != "Options" && option != "Exit"){
			//Invalid option
			cout << ">> Invalid option!" << endl;
		}
 
	}

	cout << ">> Bye-bye. See you soon!"
	return 0;
} 
