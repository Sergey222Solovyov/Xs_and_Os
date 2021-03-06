#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

//Displays the menu
int menu();

// Game process 
void setup(int mode);


void outputBoard(char board[5][5]); 

void searchEmptyCell(char board[5][5], int& row, int& column);


bool isMovesLeft(char board[5][5]);


void input(char board[5][5], int& row, int& column, char xo); 


void aiMove(char board[5][5], char ai, char player, int& row, int& column, int moves);


int evaluate(char board[5][5], char ai, char player);


int minimax(char board[5][5], char ai, char player, int moves, bool isMax);


void findBestPosition(char board[5][5], char ai, char player, int& row, int& column, int moves);

int main()
{

	while (1)
	{
		system("cls");

		switch (menu())
		{
		case '1':

			setup(1);

			break;

		case '2':

			setup(0);

			break;

		case '3':

			return 1;

		default:

			cout << "Incorrect input." << endl << "Press any key to continue...";

			break;
		}

		_getch();

		system("cls");
	}
}
//Displays the menu
int menu()
{
	int press_key;

	cout << "Start menu: ";
	cout << endl << "1. Play vs computer.";
	cout << endl << "2. Play vs friend.";
	cout << endl << "3. Exit." << endl;
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "To move symbol use: " << endl;
	cout << endl << "       'W' to move UP " << endl;
	cout << "'A' to move LEFT ";
	cout << "   'D' to move RIGHT ";
	cout << endl << "       'S' to move DOWN ";
	cout << endl << endl << "To put symbol use: 'F'. " << endl << endl;
	cout << "Use the english layout." << endl << endl;

	press_key = _getch();

	return press_key;
}
// Game process
void setup(int mode)
{
	
	int row = 0;
	int column = 0;

	char board[5][5]; 
	
	int press_key; // The variable in which the key pressed by the user will be stored

	char xo = 'O'; //  Determines whose symbol to check
	char player = ' '; // Symbol for player 
	char ai = 'O'; // Symbol for AI
	bool turn = true; // Determines whose move, if true it is a player 
	
	int moves = 0;
	
	// Create board
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j == 1 || j == 3)
			{
				board[i][j] = '|';
				continue;
			}

			if (i == 1 || i == 3)
			{
				board[i][j] = '-';
				continue;
			}

			board[i][j] = ' ';
		}
	}
	// Check what game mode is select if mode = 1 game with computer else with person.
	if (mode == 1)
	{
		do
		{
			system("cls");
			cout << "Select X or 0" << endl;
			cout << "1. X" << endl;
			cout << "2. O" << endl;

			press_key = _getch();
			switch (press_key)
			{
			case '1':

				player = 'X';
				ai = 'O';
				turn = true;
				break;

			case '2':

				player = 'O';
				ai = 'X';

				// Set initial position for AI, no matter what his first move is.
				board[2][2] = ai;
				moves++;
				break;

			default:

				cout << "Incorrect input." << endl << "Press any key to continue...";
				_getch();
				system("cls");

				break;
			}

		} while (player == ' ');

		// Beginning of the game
		do
		{
			if (turn)
			{
				input(board, row, column, player);
				turn = false;
				xo = player;
			}
			else
			{
				aiMove(board, ai, player, row, column, moves);
				turn = true;
				xo = ai;
			}

			moves++;
		} while (evaluate(board, ai, player) == 0 && moves != 9);

	} 
	else
	{
		while (evaluate(board, xo, player = 'X') == 0 && moves != 9)
		{
			// Players change, player X always goes first
			if (xo == 'X')
				xo = 'O';
			else xo = 'X';

			input(board, row, column, xo);

			moves++;
		}
		player = xo;
	}

	outputBoard(board);

	if (evaluate(board, ai, player) != 0)
		cout << endl << "Player '" << xo << "'  win the game!";
	else cout << endl << "It's a draw! ";

}
// Displays the board on the screen
void outputBoard(char board[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}
//Search and put indices in empty cell in array
void searchEmptyCell(char board[5][5], int& row, int& column)
{
	for (int i = 0; i <= 4; i += 2)
	{
		for (int j = 0; j <= 4; j += 2)
		{
			if (board[i][j] == ' ')
			{
				row = i;
				column = j;
				i = 5;
				break;
			}
		}
	}

};
//Check if moves left
bool isMovesLeft(char board[5][5])
{
	for (int i = 0; i <= 4; i += 2)
		for (int j = 0; j <= 4; j += 2)
			if (board[i][j] == ' ')
				return true;
	return false;
}
// Manage user's input
void input(char board[5][5], int& row, int& column, char xo) 
{
	char press_key;

	do
	{
		outputBoard(board);

		// Cycle for flashing symbol
		while (!_kbhit())
		{
			system("cls");

			if (board[row][column] == xo)
				board[row][column] = ' ';
			else board[row][column] = xo;

			outputBoard(board);

			Sleep(150);
		}

		press_key = _getch();

		system("cls");

		// Put symbol 
		if (press_key == 'f' || press_key == 'F')
		{
			board[row][column] = xo;

			//Setting a new position 
			searchEmptyCell(board, row, column);
		}

		// Move Down
		if (press_key == 's' || press_key == 'S')
		{
			//Set space to the current position where was the symbol
			board[row][column] = ' ';

			// Checking if a symbol is in a last row
			if (row == 4)
			{
				row -= 2;
			}

			// If not we are moving symbol by two rows down
			// Two rows because in a two - dimensional array some cells contain parts of the grid
			int i = row + 2;
			int j = column;

			//Variable count - counts how many columns(or rows) were checked
			int count = 0;

			// Finding a free array cell
			while (board[i][j] != ' ')
			{
				//If we are in the last row we are moving to the next column
				if (i == 4)
				{
					//If we are in the last column we are moving to the first column
					if (j == 4)
					{
						j = 0;
					} else  j += 2;

					count++;
					i = row;
				}
				// If all columns (or rows) have been checked, the cycle ends
				if (count == 3)
				{
					i = row;
					j = column;
					break;
				}

				i += 2;
			}

			//Sets the symbol position
			row = i;
			column = j;
			board[row][column] = xo;
		}

		// Move Up
		if (press_key == 'w' || press_key == 'W')
		{
			board[row][column] = ' ';

			if (row == 0)
				row += 2;
		

			int i = row - 2;
			int j = column;
			int count = 0;

			while (board[i][j] != ' ')
			{
				if (i == 0)
				{
					if (j == 4)
					{
						j = 0;
					} else j += 2;

					count++;
					i = row;
				}
				if (count == 3)
				{
					i = row;
					j = column;
					break;
				}
				i -= 2;

			}

			row = i;
			column = j;
			board[row][column] = xo;
		}

		// Move Right
		if (press_key == 'd' || press_key == 'D')
		{
			board[row][column] = ' ';

			if (column == 4)
				column -= 2;
		
			int i = row;
			int j = column + 2;
			int count = 0;

			while (board[i][j] != ' ')
			{
				if (j == 4)
				{
					if (i == 4)
					{
						i = 0;
					} else i += 2;

					count++;
					j = column;
				}

				if (count == 3)
				{
					i = row;
					j = column;
					break;
				}
				j += 2;
			}

			row = i;
			column = j;
			board[row][column] = xo;
		}

		// Move left
		if (press_key == 'a' || press_key == 'A')
		{
			board[row][column] = ' ';
			if (column == 0)
			{
				column += 2;
			}

			int i = row;
			int j = column - 2;

			int count = 0;

			while (board[i][j] != ' ')
			{
				if (j == 0)
				{
					if (i == 4)
					{
						i = 0;
					} else i += 2;

					count++;
					j = column;
				}

				if (count == 3)
				{
					i = row;
					j = column;
					break;
				}

				j -= 2;

			}

			row = i;
			column = j;
			board[row][column] = xo;
		}
	} while ((press_key != 'f' && press_key != 'F'));

}
// Manage AI's input
void aiMove(char board[5][5], char ai, char player, int& row, int& column, int moves)
{
	findBestPosition(board, ai, player, row, column, moves);
	board[row][column] = ai;
	searchEmptyCell(board, row, column);
}
// Based on Minimax Algorithm this function defines value for maximizer and minimizer 
void findBestPosition(char board[5][5], char ai, char player, int& row, int& column, int moves)
 {
	int bestVal = -1000;
	int moveVal = -1000;
	    
		// Traverse all cells, evaluate minimax function for
		// all empty cells. And return the cell with optimal
		// value.
		for (int i = 0; i <= 4; i += 2)
		{
			for (int j = 0; j <= 4; j += 2)
			{
			    // Check if cell is empty
				// Make the move
				if (board[i][j] == ' ')
				{
					board[i][j] = ai;
					
					// Compute evaluation function for this move. 
					moveVal =minimax(board, ai, player, moves + 1, false);

					// Undo the move
					board[i][j] = ' ';
				}

			    // If the value of the current move	
				// more than the best value, then update
				// best
				if (moveVal > bestVal)
				{
				row = i;
				column = j;
				bestVal = moveVal;
				}
			}
		}
}
// This will return the best possible move for the AI
int evaluate(char board[5][5], char ai, char player)
{
	// Checking for Rows and Columns for X or O victory. 
	for (int i = 0; i < 2; i += 2)
	{
		for (int j = 0; j < 5; j += 2)
		{
			if (board[i][j] == ai && board[i + 2][j] == ai && board[i + 4][j] == ai)
			{
				return +10;
			}
			else if (board[i][j] == player && board[i + 2][j] == player && board[i + 4][j] == player)
			{
				return -10;
			}

			if (board[j][i] == ai && board[j][i + 2] == ai && board[j][i + 4] == ai)
			{
				return +10;
			}
			else if (board[j][i] == player && board[j][i + 2] == player && board[j][i + 4] == player)
			{
				return -10;
			}

		}
	}
	
	// Checking for Diagonals for X or O victory. 
	if ((board[0][0] == ai && board[2][2] == ai) && board[4][4] == ai)
	{
		return + 10;
	}

	if ((board[0][0] == player && board[2][2] == player) && board[4][4] == player)
	{
		return - 10;
	}

	if ((board[0][4] == ai && board[2][2] == ai) && board[4][0] == ai)
	{
		return + 10;
	}

	if ((board[0][4] == player && board[2][2] == player) && board[4][0] == player)
	{
		return - 10;
	}

	return 0;
}
// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[5][5], char ai, char player, int moves, bool isMax)
{
	int score = evaluate(board, ai, player);
	// If Maximizer has won the game return his
	 // evaluated score 
	if (score == 10)
		return score;

	// If Minimizer has won the game return his 
	// evaluated score 
	if (score == -10)
		return score;

	// If there are no more moves and no winner then 
	// it is a tie 
	if (isMovesLeft(board) == false)
		return 0;

	// If isMax is true then it is the Maximizer move
	if (isMax)
	{
		int best = -1000;
		int bestVal = -1000;
		// Traverse all cells 
		for (int i = 0; i <= 4; i += 2)
		{
			for (int j = 0; j <= 4; j += 2)
			{
				// Check if cell is empty 
				if (board[i][j] == ' ')
				{
					// Make the move 
					board[i][j] = ai;
			
					// Call minimax recursively and choose 
					// the maximum value 
					best = max(best, minimax(board, ai, player, moves + 1, !isMax)) - moves;

					// Undo the move 
					board[i][j] = ' ';
					
					if (best > bestVal)
					{
						bestVal = best;
						best = -1000;
					}
				}
			}
		}	
		return bestVal;
	}

	// If this minimizer's move 
	else
	{
		int best = 1000;
		int bestVal = 1000;
		// Traverse all cells 
		for (int i = 0; i <= 4; i += 2)
		{
			for (int j = 0; j <= 4; j += 2)
			{
				// Check if cell is empty 
				if (board[i][j] == ' ')
				{
					// Make the move 
					board[i][j] = player;

					// Call minimax recursively and choose 
					// the minimum value 
					best = min(best, minimax(board, ai, player, moves + 1, !isMax)) + moves;

					// Undo the move 
					board[i][j] = ' ';

					if (best < bestVal)
					{
						bestVal = best;
						best = 1000;
					}
				}
			}
		}
		return bestVal;
	}

}

