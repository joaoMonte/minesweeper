#ifndef GAMECLASSES_H
#define GAMECLASSES_H

#include <map> 
#include <string> 
#include <vector> 

class Queue {
	//This class is a basic queue abstraction
	//It will helps when doing a BFS searching for cells which will be revealed
	public:
		void enqueue(std::string cellCoordinates);
		std::string dequeue();
        bool isEmpty();

	private:
		std::vector<std::string> buffer;
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
		Cell(bool isbomb);

		void reveal();

		bool alreadyRevealed();

		bool getIsBomb();

		void setFlag();

		bool getIsFlag();

		void incrementBombsInNeighborhood();

		int getBombsInNeighborhood();

	private:
		bool revealed;
		bool isFlag;
		bool isBomb;
		int bombsInNeighborhood;

};



class Utils {
	public:
		//Simple cast operation
		int toInt(std::string str);

		//Simple cast operation
		std::string toStr(int number);

		//Auxilary method which breaks an coordinate string into two ints!
		std::vector<int> split(std::string str);
	
};


class FieldManager {
	//This class manages the field;
	public:
		//The main variables are:
		// - lines/columns: number of lines/columns of the field. It can be defined by the user
		// - numberOfBombs: number of bombs defined by the user
		// - revealedCells: counts how many cells have been revealed. 
		//	 It will helps to know when the user won the game
		FieldManager(int l, int c, int n);

		//Fill the field with cell instances
		//The field array will be indexed by coordinates like "1-4" -> cell for example.
		//Its represents the position line 1 and column4. The content for this key will be a Cell
		void initializeField();

		//Generate a random map of bomb positions. Its keys are the random number. The content 
		//of this keys will be the position (str). This position will be defined at the method
		//initializeField. Its value will be updated
		void generateBombPositions();

		//This method increment the bombsInNeighborhood variable from a cell and save its 
		// state back to the field hashmap
		void incrementSingleNeighborCell(int l, int c);

		//This method increment the bombsInNeighborhood variables of all nearbyCells (if they exists).
		//this method is called when a bomb is deployed, these values needs to be updated for all nearby cells
		void incrementNeighborCells(int l, int c);

		void printField();

		//Return a cell object by its coordinates (like 1-2). It supports many other methods
		Cell getCellByCoordinates(int line, int column);

		//Save a cell object on given coordinates (like 1-2). It supports many other methods
		void updateCell(Cell updatedCell, int l, int c);

		//reveal a cell setting its bool "reveal" to true, giving its coordinates
		void revealCell(int l, int c);

		//The method called when the user guess a cell!
		int chooseCell(int l, int c);

		void revealGroupOfCells(int starter_l, int starter_c);
		
        //Check if the user won the game 
		bool didUserWin();
		//Set a flag in a cell
		
        void setFlag(int l, int c);

	private:
		int lines;
		int columns;
		int numberOfBombs;
		int revealedCells;
		Utils utils;
		std::map<std::string, Cell> field;
		std::map<int, std::string> bombsPositions;

};


#endif