#include <iostream> 
#include <iterator> 
#include <sstream>
#include "stdlib.h"
#include "gameclasses.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define YELLOW  "\033[33m" 
#define GREEN   "\033[32m" 


int main() 
{
	//Here we create the menu for the user
	int numberOfBombs = 20;
	int lines = 10;
	int columns = 10;
	string option = "";
	bool validSetup = false;
	Utils utils = Utils();

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
					cout << ">> Type your guess using the format line-column" << endl;
					cout << ">> The field is indexed starting from the line and column 1!" << endl << ">> ";
					
					cin >> cellChoice;
					userGuess = utils.split(cellChoice);
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
					cout << ">> Type your flag location using the format line-column" << endl;
					cout << ">> The field is indexed starting from the line and column 1!" << endl << ">> ";
					cin >> flagPosition;
					flagChoice = utils.split(flagPosition); 
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
