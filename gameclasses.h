#ifndef GAMECLASSES_H
#define GAMECLASSES_H

class Queue {
	//This class is a basic queue abstraction
	//It will helps when doing a BFS searching for cells which will be revealed
	public:
		void enqueue(string cellCoordinates);
		string dequeue();
        bool isEmpty();

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


#endif