#include <iostream> 
#include <iterator> 
#include <sstream>
#include "stdlib.h"
#include "gameclasses.h"

using namespace std;

void Queue :: enqueue(string cellCoordinates){
	buffer.push_back(cellCoordinates);
}

string Queue :: dequeue(){
	string auxiliaryString = buffer[0];
	buffer.erase(buffer.begin());
	return auxiliaryString;
}

bool Queue :: isEmpty(){
	return buffer.size() == 0;
}

Cell :: Cell (bool isbomb)
    :isBomb(isbomb), revealed(false), isFlag(false), bombsInNeighborhood(0)
{}

void Cell :: reveal(){
	revealed = true;
}

bool Cell :: alreadyRevealed(){
	return revealed;
}

bool Cell :: getIsBomb(){
	return isBomb;
}

void Cell :: setFlag(){
	isFlag = true;
}

bool Cell :: getIsFlag(){
	return isFlag;
}

void Cell :: incrementBombsInNeighborhood(){
	if (!isBomb) {
		bombsInNeighborhood++;
	}
}

int Cell :: getBombsInNeighborhood(){
	return bombsInNeighborhood;
}

int Utils :: toInt(string str){
	//Simple cast operation

	stringstream auxiliary(str); 
	int output; 
    auxiliary >> output;
	return output; 
}

string Utils :: toStr(int number){
    //Simple cast operation

	string auxiliaryString;
	stringstream strstream;
	strstream << number;
	return strstream.str();
}

vector<int> Utils :: split(string str){
    //Auxilary method which breaks an coordinate string into two ints!
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


FieldManager :: FieldManager (int l, int c, int n)
    :utils(Utils()), lines(l), columns(c), numberOfBombs(n), revealedCells(0)
{
    // Generate, randomly, bomb positions and stores it at bombPositions map
	generateBombPositions();
}

void FieldManager :: initializeField(){
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
            key = utils.toStr(i) + "-" + utils.toStr(j);
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

void FieldManager :: generateBombPositions(){
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

void FieldManager :: incrementSingleNeighborCell(int l, int c){
    Cell cell = getCellByCoordinates(l, c);
    cell.incrementBombsInNeighborhood();
    updateCell(cell, l, c);
}

void FieldManager :: incrementNeighborCells(int l, int c){
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

void FieldManager :: printField(){
    //method which prints the entire field
    for (int i = 1; i <= lines; i++){
        for (int j = 1; j <= columns; j++){
            Cell auxiliaryCell = getCellByCoordinates(i,j);
            if (auxiliaryCell.alreadyRevealed()){
                //If the cell has been revealed, shown its value
                if (auxiliaryCell.getBombsInNeighborhood() > 0){
                    cout << auxiliaryCell.getBombsInNeighborhood() << "|";
                }
                else {
                    cout << auxiliaryCell.getBombsInNeighborhood() << "|";
                }
            }
            else {
                //Else show a # or a flag (if the cell is a flag)
                if (auxiliaryCell.getIsFlag()){
                    cout << "F|";
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


Cell FieldManager :: getCellByCoordinates(int line, int column){
    string key = utils.toStr(line) + "-" + utils.toStr(column);
    map<string, Cell>::iterator itr;
    itr = field.find(key);
    return itr->second;
}


void FieldManager :: updateCell(Cell updatedCell, int l, int c){
    map<string, Cell>::iterator itr;
    string key = utils.toStr(l) + "-" + utils.toStr(c);
    itr = field.find(key);
    itr->second = updatedCell;
}

void FieldManager :: revealCell(int l, int c){
    Cell cell = getCellByCoordinates(l, c);
    cell.reveal();
    revealedCells++;
    updateCell(cell, l, c);
}

int FieldManager :: chooseCell(int l, int c){
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
                        cout << "B|";
                    }
                    else {
                        //If the cell has been revealed, show its value.
                        if (auxiliaryCell.alreadyRevealed()){
                            if (auxiliaryCell.getBombsInNeighborhood() > 0){
                                cout << auxiliaryCell.getBombsInNeighborhood() << "|";
                            }
                            else {
                                cout << auxiliaryCell.getBombsInNeighborhood() << "|";
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

void FieldManager :: revealGroupOfCells(int starter_l, int starter_c){
    //This method traverse the field map to select the cells which will be showed
    //Its use an Breadth-First Search - BFS to traverse the field. the queue is the used datastructure
    Queue queue = Queue();
    string key = utils.toStr(starter_l) + "-" + utils.toStr(starter_c);
    vector<int> coordinates;
    queue.enqueue(key);
    int l;
    int c;

    while (!queue.isEmpty()) {
        key = queue.dequeue();
        coordinates = utils.split(key);
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
                queue.enqueue(utils.toStr(l-1) + "-" + utils.toStr(c-1));
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
                queue.enqueue(utils.toStr(l-1) + "-" + utils.toStr(c));
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
                queue.enqueue(utils.toStr(l-1) + "-" + utils.toStr(c+1));
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
                queue.enqueue(utils.toStr(l) + "-" + utils.toStr(c-1));
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
                queue.enqueue(utils.toStr(l) + "-" + utils.toStr(c+1));
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
                queue.enqueue(utils.toStr(l+1) + "-" + utils.toStr(c-1));
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
                queue.enqueue(utils.toStr(l+1) + "-" + utils.toStr(c));
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
                queue.enqueue(utils.toStr(l+1) + "-" + utils.toStr(c+1));
            }
            else{
                if (!getCellByCoordinates(l+1, c+1).alreadyRevealed()){
                    revealCell(l+1, c+1);
                }
            }
        }
    } 
}

bool FieldManager :: didUserWin(){
	return revealedCells + numberOfBombs == lines * columns;
}

void FieldManager :: setFlag(int l, int c){
    Cell cell = getCellByCoordinates(l, c);
    cell.setFlag();
    updateCell(cell, l, c);
}

