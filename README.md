# minesweeper


This project is a classical minesweeper game implemented in terminal mode. The user plays giving the coordinate of the field which he wants to interact. To click or set a flag.
The objective is reveal all cells of the field without clicking on a bomb! Each cell has a counter indicating how many bombs are in the 8 cells next to it.

Read the following instructions and have fun! :)

## Running

To compile and run the game on linux, type:

```
>> g++ main.cpp gameclasses.cpp -o minesweeper 
>> ./minesweeper

```

To compile and run the game on Windows, type:

```
>> g++ main.cpp gameclasses.cpp -o minesweeper.exe 

```
 After that, just double click the generated executable.

## Playing


The game works in terminal mode. At the start menu the user has the options to Start the game, change the game settings and exit. To acess each of them, he must type (exactly) Start/Options/Exit depending on its choice.

```
-------------------------------
----------MINESWEEPER----------
-------------------------------
>> Type
>> Start - begin the game
>> Options - choose the game settings
>> Exit - closes the application
>> 


```


## Start

The game will start showing a grid with cells. The user will have 3 possible actions:
* Guess: Choice a cell, giving its coordinates in the format line-column (example 1-5). To guess a cell, th`e user must type G when the instructions asks. In following, he must give the coordinates respecting the format. If the selected cell is a bomb or not... the grid will show! 
* Flag: Define a cell as flag. When the user expect that a cell is a bomb, he can set the position as a flag to remember it. To set a flag, the user must type F when the instruction asks. In following, he must give the coordinates respecting the same format. The selected position will show an F during the game.
* Exit: Quit to the main menu, typing E when the instructions ask.

Typing a guess:

```
>> Type
>> G - Guess the line and the column of desired cell to click!
>> F - Set a flag on the field
>> E - Exit to the main menu
>> G
>> Type your guess using the format line-column
>> The field is indexed starting from the line and column 1!
>> 1-1
0|1|#|#|#|#|#|#|#|#|
1|2|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|

```

Typing a flag:

```
>> Type
>> G - Guess the line and the column of desired cell to click!
>> F - Set a flag on the field
>> E - Exit to the main menu
>> F
>> Type your flag location using the format line-column
>> The field is indexed starting from the line and column 1!
>> 6-7
0|1|#|#|#|#|#|#|#|#|
1|2|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|F|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|
#|#|#|#|#|#|#|#|#|#|

```

It is important to remember that the coordinates start from 1! The first line and first column are 1.


## Options

Typing Options at the main menu, the user can change some game settings. The game will asks for:
* Lines: number of lines of the grid. The default value is 10. 
* Columns: number of columns of the grid. The default value is 10.
* Number of bombs: number of the bombs spreaded among the field. The default value is 10. The user can change the difficult increasing or decreasing this value. But he needs to respect the number of cells on the field (lines * columns). 

Choosing game settings:
```
>> Options
>> Type the number of lines of your minesweeper field! (default: 10)
>> 5
>> Type the number of columns of your minesweeper field! (default: 10)
>> 5
>> Type the number of bombs of your minesweeper field! (default: 10)
>> 5
>> Settings updated! Returning to the main menu

```

Choosing an invalid group of settings!
```
>> Options
>> Type the number of lines of your minesweeper field! (default: 10)
>> 5
>> Type the number of columns of your minesweeper field! (default: 10)
>> 5
>> Type the number of bombs of your minesweeper field! (default: 10)
>> 30
>> Your setup is invalid. The field must have at least 1 cell which isn't a bomb.
>> Try again
>> Settings updated! Returning to the main menu
```

## Exit

Ends the application

```
>> Exit
>> Bye-bye. See you soon!
```

