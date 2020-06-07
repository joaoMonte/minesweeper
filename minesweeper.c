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
#define GREEN   "\033[32m" 

class Queue {
	//This class is a basic queue abstraction
	//It will helps when doing a BFS searching for cells which will be revealed
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
	//This class represents a cell in the minesweeper field
	//Its instances will be stored at the field map. 
	//Its variables are 
	// - revealed: If the cell is already revealed by the user
	// - isBomb: Says if the cell is a bomb
	// - isFlag: Says if the cell has a flag
	// - bombsInNeighborhood: folowing the game rules, each cell must say how many bombs are in the next 8 spaces 
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
		bool getIsFlag(){
			return isFlag;
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
	//This class manages the field;
	public:
		//The main variables are:
		// - lines/columns: number of lines/columns of the field. It can be defined by the user
		// - numberOfBombs: number of bombs defined by the user
		// - revealedCells: counts how many cells have been revealed. 
		//	 It will helps to know when the user won the game
		FieldManager(int l, int c, int n){
			lines = l;
			columns = c;
			numberOfBombs = n;
			revealedCells = 0;
			// Generate, randomly, bomb positions and stores it at bombPositions map
			generateBombPositions();

		}

		//Simple cast operation
		string toStr(int number){
			string auxiliaryString;
			stringstream strstream;
			strstream << number;
			return strstream.str();
		}

		void initializeField(){
			//Fill the field with cell instances
			//The field array will be indexed by coordinates like "1-4" -> cell for example.
			//Its represents the position line 1 and column4. The content for this key will be a Cell
			string key;
			map<int, string>::iterator iter;
			//The position counter will know when the specified position is a bomb position.
			//It reach this objective checking on the bombPositions map (generated at the constructor call).
			int positionCounter = 1;
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					key = toStr(i) + "-" + toStr(j);
					iter = bombsPositions.find(positionCounter);
					//If the current position is a bomb position, we will create the cell as bomb
					if (iter != bombsPositions.end()){
						field.insert(pair<string, Cell>(key, Cell(true)));
						//Save its position at the bombPositions map
						//I left this line below to show the bomb positions for debug objectives
						//cout << key << endl;
						iter->second = key;
					}
					else {
						//If this position is not a bomb position, we create the cell by the normal way
						field.insert(pair<string, Cell>(key, Cell(false)));
					}
					positionCounter++;

				}

			}
			// update bombsInTheNeighborHood. After the bombs were "deployed" on the field
			// made the increment on its nearby cells. The private cell's variable incremented is
			// bombsInNeighborhood
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					if (getCellByCoordinates(i,j).getIsBomb()){
						incrementNeighborCells(i,j); 
					}
				}
			}
		}

		//Generate a random map of bomb positions. Its keys are the random number. The content 
		//of this keys will be the position (str). This position will be defined at the method
		//initializeField. Its value will be updated
		void generateBombPositions(){
			int randomNumber;
			map<int, string>::iterator iter;
			int i = 1;
			srand(time(0)); 
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

		//This method increment the bombsInNeighborhood variable from a cell and save its 
		// state back to the field hashmap
		void incrementSingleNeighborCell(int l, int c){
			Cell cell = getCellByCoordinates(l, c);
			cell.incrementBombsInNeighborhood();
			updateCell(cell, l, c);
		}

		//This method increment the bombsInNeighborhood variables of all nearbyCells (if they exists).
		//this method is called when a bomb is deployed, these values needs to be updated for all nearby cells
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
			//method which prints the entire field
			for (int i = 1; i <= lines; i++){
				for (int j = 1; j <= columns; j++){
					Cell auxiliaryCell = getCellByCoordinates(i,j);
					if (auxiliaryCell.alreadyRevealed()){
						//If the cell has been revealed, shown its value
						if (auxiliaryCell.getBombsInNeighborhood() > 0){
							cout << BLUE << auxiliaryCell.getBombsInNeighborhood() << RESET << "|";
						}
						else {
							cout << WHITE << auxiliaryCell.getBombsInNeighborhood() << RESET << "|";
						}
					}
					else {
						//Else show a # or a flag (if the cell is a flag)
						if (auxiliaryCell.getIsFlag()){
							cout << YELLOW << "F" << RESET << "|";
						}
						else {
							cout << "#|";
						}
					}  
					
				}
				cout << endl;
            }
			cout << endl;
		}

		//Return a cell object by its coordinates (like 1-2). It supports many other methods
		Cell getCellByCoordinates(int line, int column){
				string key = toStr(line) + "-" + toStr(column);
				map<string, Cell>::iterator itr;
				itr = field.find(key);
				return itr->second;
		}

		//Save a cell object on given coordinates (like 1-2). It supports many other methods
		void updateCell(Cell updatedCell, int l, int c){
			map<string, Cell>::iterator itr;
			string key = toStr(l) + "-" + toStr(c);
			itr = field.find(key);
			itr->second = updatedCell;
		}

		//reveal a cell setting its bool "reveal" to true, giving its coordinates
		void revealCell(int l, int c){
			Cell cell = getCellByCoordinates(l, c);
			cell.reveal();
			revealedCells++;
			updateCell(cell, l, c);
		}

		//The method called when the user guess a cell!
		int chooseCell(int l, int c){
			//the variable output returns the consequences from the user choice. 
			//Depending on its return
			int output;
			Cell cell = getCellByCoordinates(l, c);
			if (cell.alreadyRevealed()){
				//If the cell is already revealed, shows a message to the user
				cout << ">> This cell have been already revealed! Choice other cell!" << endl;
				output = 1;
			}
			else {
				//if not... lets check what will happen
				if (cell.getIsBomb()){
					//If the cell is a bomb, show all bombs!
					//and game over! Traverse the field showing them.
					for (int i = 1; i <= lines; i++){
						for (int j = 1; j <= columns; j++){
							Cell auxiliaryCell = getCellByCoordinates(i,j);
							//If the cell is a bomb, show it!
							if (auxiliaryCell.getIsBomb()){
								cout << RED << "B" << RESET << "|";
							}
							else {
								//If the cell has been revealed, show its value.
								if (auxiliaryCell.alreadyRevealed()){
									if (auxiliaryCell.getBombsInNeighborhood() > 0){
										cout << BLUE << auxiliaryCell.getBombsInNeighborhood() << RESET << "|";
									}
									else {
										cout << WHITE << auxiliaryCell.getBombsInNeighborhood() << RESET << "|";
									}
								}
								else{
									//Else, stay it hidden, as the game does
									cout << "#|";
								}
							}
						}
						cout << endl;
           	 		}
					//output == 0 -> game over!	
					output = 0;
				}

				else {
					//If the cell is not a bomb...
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
			return output;
		}

		//Simple cast operation
		int toInt(string str){
			stringstream auxiliary(str); 
			int output; 
    		auxiliary >> output;
			return output; 
		}

		//Auxilary method which breaks an coordinate string into two ints!
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
			//add the last buffer to the output. 
			//Because the loop exits before did it
			number = toInt(buffer);
			output.push_back(number);
			return output;
		}


		void revealGroupOfCells(int starter_l, int starter_c){
			//This method traverse the field map to select the cells which will be showed
			//Its use an Breadth-First Search - BFS to traverse the field. the queue is the used datastructure
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
				//If it is a 0/empty cell we add it the queue (if it is not revealed yet)
				//to be analysed about its neighbor at next iteration.
				//Does the same operation for all neighbor cells
				//When a numered cell (>0) is found, we just reveal it. We dont add it to the queue.
				//The BFS happens only with the 0/empty cells
				if (l-1 >= 1 && c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l-1) + "-" + toStr(c-1));
					}
					else{
						if (!getCellByCoordinates(l-1, c-1).alreadyRevealed()){
							revealCell(l-1, c-1);
						}
					}

				}

				//Check l-1 / c
				if (l-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l-1) + "-" + toStr(c));
					}
					else{
						if (!getCellByCoordinates(l-1, c).alreadyRevealed()){
							revealCell(l-1, c);
						}
					}
				}

				//Check l-1 / c + 1
				if (l-1 >= 1 && c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l-1, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l-1) + "-" + toStr(c+1));
					}
					else{
						if (!getCellByCoordinates(l-1, c+1).alreadyRevealed()){
							revealCell(l-1, c+1);
						}
					}
				}

				//Check l / c - 1
				if (c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l) + "-" + toStr(c-1));
					}
					else{
						if (!getCellByCoordinates(l, c-1).alreadyRevealed()){
							revealCell(l, c-1);
						}
					}
				}

				//Check l / c + 1
				if (c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l) + "-" + toStr(c+1));
					}
					else{
						if (!getCellByCoordinates(l, c+1).alreadyRevealed()){
							revealCell(l, c+1);
						}
					}
				}

				//Check l+1 / c - 1
				if (l+1 <= lines && c-1 >= 1) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c-1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l+1) + "-" + toStr(c-1));
					}
					else{
						if (!getCellByCoordinates(l+1, c-1).alreadyRevealed()){
							revealCell(l+1, c-1);
						}
					}
				}

				//Check l+1 / c
				if (l+1 <= lines) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l+1) + "-" + toStr(c));
					}
					else{
						if (!getCellByCoordinates(l+1, c).alreadyRevealed()){
							revealCell(l+1, c);
						}
					}
				}

				//Check l+1 / c+1
				if (l+1 <= lines && c+1 <= columns) {
					Cell auxiliaryCell = getCellByCoordinates(l+1, c+1);
					if (auxiliaryCell.getBombsInNeighborhood() == 0 && !auxiliaryCell.alreadyRevealed()){
						queue.enqueue(toStr(l+1) + "-" + toStr(c+1));
					}
					else{
						if (!getCellByCoordinates(l+1, c+1).alreadyRevealed()){
							revealCell(l+1, c+1);
						}
					}
				}
			} 
		}

		//Check if the user won the game 
		bool didUserWin(){
			return revealedCells + numberOfBombs == lines * columns;
		}

		int getRevealed(){
			return revealedCells;
		}

		//Set a flag in a cell
		void setFlag(int l, int c){
			Cell cell = getCellByCoordinates(l, c);
			cell.setFlag();
			updateCell(cell, l, c);
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
	//Here we create the menu for the user
	int numberOfBombs = 20;
	int lines = 10;
	int columns = 10;
	string option = "";
	bool validSetup = false;

	while (option != "Exit"){
		cout << RED << "-------------------------------" << RESET << endl; 
		cout << RED << "----------" << YELLOW << "MINESWEEPER" << RED << "----------" << endl;
		cout << RED << "-------------------------------" << RESET << endl;
		cout << ">> Type" << endl << ">> Start - begin the game" << endl;
		cout << ">> Options - choose the game settings" << endl;
		cout << ">> Exit - closes the application" << endl;
		cout << ">> ";
		cin >> option;

		if (option == "Start"){
			//start the game
			string startOption = "";
			string flagPosition;
			string cellChoice;
			vector<int> userGuess;
			vector<int> flagChoice;
			int guessResult = 4;
			cout << ">> The game will start!" << endl;
			//using the user defined variables, we create and initialize the field. The variables have default values
			FieldManager userField = FieldManager(lines, columns, numberOfBombs);
			userField.initializeField();
			userField.printField();
			

			while (startOption != "E") {
				cout << ">> Type" << endl;
				cout << ">> G - Guess the line and the column of desired cell to click!" << endl;
				cout << ">> F - Set a flag on the field" << endl;
				cout << ">> E - Exit to the main menu" << endl << ">> ";
				cin >> startOption;

				//if the user choose Guess, he need to type a coordinate (format: line-column)
				if (startOption == "G"){
					cout << ">> Type your guess using the format line-column" << endl << ">> ";
					cin >> cellChoice;
					userGuess = userField.split(cellChoice);
					int userGuess_line = userGuess[0];
					int userGuess_column = userGuess[1];

					if (userGuess_line > lines || userGuess_column > columns){
						cout << ">> Invalid guess! Try again" << endl;
					}
					else {
						guessResult = userField.chooseCell(userGuess_line, userGuess_column);

						if (guessResult == 0){
							cout << YELLOW << "-------------------------------" << RESET << endl; 
							cout << YELLOW << "----------" << RED << "GAME OVER" << YELLOW << "------------" << endl;
							cout << YELLOW << "-------------------------------" << RESET << endl;
							startOption = "E";
						}

						else if (guessResult == 2){
							cout << BLUE << "-------------------------------" << RESET << endl; 
							cout << BLUE << "-----------" << GREEN << "YOU WIN!" << BLUE << "------------" << endl;
							cout << BLUE << "--------" << GREEN << "CONGRATULATIONS :)" << BLUE << "-----" << endl;
							cout << BLUE << "-------------------------------" << RESET << endl;
							startOption = "E";
						}
					}
				}
				else if (startOption == "F"){
					//if the user choose Flag, he need to type a coordinate for the flag (format: line-column)
					cout << ">> Type your flag location using the format line-column" << endl << ">> ";
					cin >> flagPosition;
					flagChoice = userField.split(flagPosition); 
					int flag_line = flagChoice[0];
					int flag_column = flagChoice[1];
					userField.setFlag(flag_line, flag_column);
					userField.printField();
					if (flag_line > lines || flag_column > columns){
						cout << ">> Invalid location! Try again" << endl;
					}

				}

				else {
					if (startOption != "E" && startOption != "F" && startOption != "G"){
						cout << ">> Invalid option!" << endl;
					}
				}
			} while (startOption != "E");
			
			cout << ">> Returning to the main menu" << endl;

		}
		else if (option == "Options"){
			do {
				//go to settings
				//Where the user can choice a number of lines, columns and bombs
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
					cout << ">> Your setup is invalid. The field must have at least 1 cell which isn't a bomb.";
					cout << ">> Try again" << endl;
				}

			} while(!validSetup);
			cout << ">> Settings updated! Returning to the main menu" << endl;
		}
		else if (option != "Start" && option != "Options" && option != "Exit"){
			//Invalid option
			cout << ">> Invalid option!" << endl;
		}
 
	}

	cout << ">> Bye-bye. See you soon!" << endl;
	return 0;
} 
