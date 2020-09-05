#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

//Displays the menu
int Menu();

// Game process 
void Setup(int mode);

// Displays the board on the screen
void OutputBoard(char board[5][5]); 

//Search and put indices in empty cell in array
void SearchEmptyCell(char board[5][5], int& index, int& jndex);

//Check if moves left
bool IsMovesLeft(char board[5][5]);

// Manage user's input
void Input(char board[5][5], int& index, int& jndex, char xo); 

// Manage AI's input
void AImove(char board[5][5], char ai, char player, int& index, int& jndex, int moves);

// Based on Minimax Algorithm this function defines value for maximizer and minimizer 
int Evaluate(char board[5][5], char ai, char player);

// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int Minimax(char board[5][5], char ai, char player, int moves, bool isMax);

// This will return the best possible move for the AI
void FindBestPosition(char board[5][5], char ai, char player, int& index, int& jndex, int moves);

int main()
{

	while (1)
	{
		system("cls");

		switch (Menu())
		{
		case '1':

			Setup(1);

			break;

		case '2':

			Setup(0);

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

int Menu()
{
	int pressKey;

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

	pressKey = _getch();

	return pressKey;
}

void Setup(int mode)
{
	// The Indexes indicates the location of the X or O
	// index indicates row on the grid, jndex - column
	int index = 0;
	int jndex = 0;

	int move = 0;// Counts how many moves was made
	
	char board[5][5]; //Initialization of the game board
	
	int press; // The variable in which the key pressed by the user will be stored

	char xo = 'O'; //  Determines whose symbol to check
	char player = 'O'; // Symbol for player 
	char ai = 'O'; // Symbol for AI
	bool turn = true; // Determines whose move, if true it is a player 
	
	int moves = 0; // Counts how many moves was made
	
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

			press = _getch();
			switch (press)
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
				Input(board, index, jndex, player);
				turn = false;
				xo = player;
			}
			else
			{
				AImove(board, ai, player, index, jndex, moves);
				turn = true;
				xo = ai;
			}

			moves++;
		} while (Evaluate(board, ai, player) == 0 && moves != 9);

	} 
	else
	{
		while (Evaluate(board, xo, player) == 0 && move != 9)
		{
			// Players change, player X always goes first
			if (xo == 'X')
				xo = 'O';
			else xo = 'X';

			Input(board, index, jndex, xo);

			move++;
		}
		player = xo;
	}

	OutputBoard(board);

	if (Evaluate(board, ai, player) != 0)
		cout << endl << "Player '" << xo << "'  win the game!";
	else cout << endl << "It's a draw! ";

}

void OutputBoard(char board[5][5])
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

void SearchEmptyCell(char board[5][5], int& index, int& jndex)

{
	for (int i = 0; i <= 4; i += 2)
	{
		for (int j = 0; j <= 4; j += 2)
		{
			if (board[i][j] == ' ')
			{
				index = i;
				jndex = j;
				i = 5;
				break;
			}
		}
	}

};

bool IsMovesLeft(char board[5][5])
{
	for (int i = 0; i <= 4; i += 2)
		for (int j = 0; j <= 4; j += 2)
			if (board[i][j] == ' ')
				return true;
	return false;
}

void Input(char board[5][5], int& index, int& jndex, char xo) {

	// The symbol that you press to move the X or O
	char press_key;

	do
	{
		OutputBoard(board);

		// Cycle for flashing symbol
		while (!_kbhit())
		{
			system("cls");

			if (board[index][jndex] == xo)
				board[index][jndex] = ' ';
			else board[index][jndex] = xo;

			OutputBoard(board);

			Sleep(150);
		}

		press_key = _getch();

		system("cls");

		// Put symbol 
		if (press_key == 'f' || press_key == 'F')
		{
			board[index][jndex] = xo;

			//Setting a new position 
			SearchEmptyCell(board, index, jndex);
		}

		// Move Down
		if (press_key == 's' || press_key == 'S')
		{
			//Set space to the current position where was the symbol
			board[index][jndex] = ' ';

			// Checking if a symbol is in a last row
			if (index == 4)
			{
				index -= 2;
			}

			// If not we are moving symbol by two rows down
			// Two rows because in a two - dimensional array some cells contain parts of the grid
			int i = index + 2;
			int j = jndex;

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
					i = index;
				}
				// If all columns (or rows) have been checked, the cycle ends
				if (count == 3)
				{
					i = index;
					j = jndex;
					break;
				}

				i += 2;
			}

			//Sets the symbol position
			index = i;
			jndex = j;
			board[index][jndex] = xo;
		}

		// Move Up
		if (press_key == 'w' || press_key == 'W')
		{
			board[index][jndex] = ' ';

			if (index == 0)
				index += 2;
		

			int i = index - 2;
			int j = jndex;
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
					i = index;
				}
				if (count == 3)
				{
					i = index;
					j = jndex;
					break;
				}
				i -= 2;

			}

			index = i;
			jndex = j;
			board[index][jndex] = xo;
		}

		// Move Right
		if (press_key == 'd' || press_key == 'D')
		{
			board[index][jndex] = ' ';

			if (jndex == 4)
				jndex -= 2;
		

			int i = index;
			int j = jndex + 2;
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
					j = jndex;
				}

				if (count == 3)
				{
					i = index;
					j = jndex;
					break;
				}
				j += 2;
			}

			index = i;
			jndex = j;
			board[index][jndex] = xo;
		}

		// Move left
		if (press_key == 'a' || press_key == 'A')
		{
			board[index][jndex] = ' ';
			if (jndex == 0)
			{
				jndex += 2;
			}

			int i = index;
			int j = jndex - 2;

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
					j = jndex;
				}

				if (count == 3)
				{
					i = index;
					j = jndex;
					break;
				}

				j -= 2;

			}

			index = i;
			jndex = j;
			board[index][jndex] = xo;
		}
	} while ((press_key != 'f' && press_key != 'F'));

}

void AImove(char board[5][5], char ai, char player, int& index, int& jndex, int moves)
{
	FindBestPosition(board, ai, player, index, jndex, moves);
	board[index][jndex] = ai;
	SearchEmptyCell(board, index, jndex);
}

void FindBestPosition(char board[5][5], char ai, char player, int& index, int& jndex, int moves)
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
					moveVal = Minimax(board, ai, player, moves + 1, false);

					// Undo the move
					board[i][j] = ' ';
				}

			    // If the value of the current move	
				// more than the best value, then update
				// best
				if (moveVal > bestVal)
				{
				index = i;
				jndex = j;
				bestVal = moveVal;
				}
			}
		}
}

int Evaluate(char board[5][5], char ai, char player)
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

int Minimax(char board[5][5], char ai, char player, int moves, bool isMax)
{
	
	int score = Evaluate(board, ai, player);
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
	if (IsMovesLeft(board) == false)
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
					best = max(best, Minimax(board, ai, player, moves + 1, !isMax)) - moves;

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
					best = min(best, Minimax(board, ai, player, moves + 1, !isMax)) + moves;

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

