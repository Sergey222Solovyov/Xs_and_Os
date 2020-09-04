#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

<<<<<<< HEAD
void OutputBoard(char board[5][5]);// Displays the table on the screen
void Input(char board[5][5],  int& index, int& jndex, char xo);// Manage user's input
bool GameOver(char board[5][5], char xo);// Determines the end of the game
int Menu(); //Displays the menu
void ControlTutorial();// Displays the  Control tutorial
void Setup();// Game process


=======
void OutputBoard(char board[5][5]); // Displays the board on the screen
void Input(char board[5][5], int& index, int& jndex, char xo); // Manage user's input
bool Winner(char board[5][5], char xo);// Determines the winner 
int Menu(); //Displays the menu
void Setup(); // Game process
void SetupWith_AI(); // Game process vs AI
void AImove(char board[5][5], char ai, char player, int& index, int& jndex, int moves); // Logic for the AI
void SearchEmptyCell(char board[5][5], int& index, int& jndex); //Search and put indices in empty cell in array
bool IsMovesLeft(char board[5][5]);
int Evaluate(char board[5][5], char ai, char player);// Based on Minimax Algorithm 
													// this function defines value for maximizer (In our case maximizer is AI)
int Minimax(char board[5][5], char ai, char player, int moves, bool isMax);


void FindBestPosition(char board[5][5], char ai, char player, int& index, int& jndex, int moves);
>>>>>>> add-featureAI

int main()
{

	while (1)
	{
		system("cls");

		switch (Menu())
		{
		case '1':

			SetupWith_AI();

			break;

		case '2':

			Setup();

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



void Setup()
{
	bool endGame = false;

	// The Indexes indicates the location of the X or O
	// index indicates row on the grid, jndex - column
	int index = 0;
	int jndex = 0;

	// Counts how many moves was made
	int move = 0;

	// Sets the starting character 
	char xo = 'O';


	char board[5][5];

	// Creat board
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

	// Beginning of the game
	while (!(endGame = Winner(board, xo)) && move != 9)
	{
		// Players change, player X always goes first
		if (xo == 'X')
		{
			xo = 'O';
		}
		else xo = 'X';

		Input(board, index, jndex, xo);

		move++;

	}

	OutputBoard(board);

	if (endGame)
	{
		cout << endl << "Player '" << xo << "'  win the game!";
	}
	else cout << endl << "It's a draw! ";

	// After the end of the session, everything is reset
}

void SetupWith_AI()
{
	char board[5][5];
	int a;
	char xo = ' '; //  Determines whose symbol to check
	bool endGame = false;
	char player = ' ';
	char ai = ' ';
	bool turn = false; // Determines whose move, if true it is a person
	int index = 0;// The Indexes indicates the location of the X or O
	int jndex = 0;	// index indicates row on the grid, jndex - column
	int moves = 0; // Counts how many moves was made



	do
	{
		system("cls");
		cout << "Select X or 0" << endl;
		cout << "1. X" << endl;
		cout << "2. O" << endl;

		a = _getch();
		switch (a)
		{
		case '1':

			player = 'X';
			ai = 'O';
			turn = true;
			break;

		case '2':

			player = 'O';
			ai = 'X';
			turn = false;
			break;

		default:

			cout << "Incorrect input." << endl << "Press any key to continue...";
			_getch();
			system("cls");

			break;
		}

	} while (player == ' ');

	

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
	} while (!(endGame = Winner(board, xo)) && moves != 9);

	OutputBoard(board);

	if (endGame)
	{
		cout << endl << "Player '" << xo << "'  win the game!";
	}
	else cout << endl << "It's a draw! ";

}

<<<<<<< HEAD

=======
>>>>>>> add-featureAI
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


<<<<<<< HEAD
=======
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

bool IsMovesLeft(char board[5][5])
{
	for (int i = 0; i <= 4; i += 2)
		for (int j = 0; j <= 4; j += 2)
			if (board[i][j] == ' ')
				return true;
	return false;
}



>>>>>>> add-featureAI
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

			// Checking if a symbol is on a last row
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
					}
					else  j += 2;

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
			{
				index += 2;
			}

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
					}
					else j += 2;

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
			{
				jndex -= 2;
			}

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
					}
					else i += 2;

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
					}
					else i += 2;

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

<<<<<<< HEAD

bool GameOver(char board[5][5], char xo)
=======
bool Winner(char board[5][5], char xo)
>>>>>>> add-featureAI
{
	for (int i = 0; i < 2; i += 2)
	{
		for (int j = 0; j < 5; j += 2)
		{
			if (board[i][j] == xo && board[i + 2][j] == xo && board[i + 4][j] == xo)
			{
				board[i][j] = '+';
				board[i + 2][j] = '+';
				board[i + 4][j] = '+';
				return true;
			}

			if (board[j][i] == xo && board[j][i + 2] == xo && board[j][i + 4] == xo)
			{
				board[j][i] = '+';
				board[j][i + 2] = '+';
				board[j][i + 4] = '+';
				return true;
			}
		}
	}

	if ((board[0][0] == xo && board[2][2] == xo) && board[4][4] == xo)
	{
		board[0][0] = '+';
		board[2][2] = '+';
		board[4][4] = '+';
		return  true;
	}

	if ((board[0][4] == xo && board[2][2] == xo) && board[4][0] == xo)
	{
		board[0][4] = '+';
		board[2][2] = '+';
		board[4][0] = '+';
		return true;
	}

	return false;
}

<<<<<<< HEAD
int Menu()
=======
void SearchEmptyCell(char board[5][5], int& index, int& jndex)
>>>>>>> add-featureAI
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
					
					// compute evaluation function for this move. 
					moveVal = Minimax(board, ai, player, moves + 1, false);

					// Undo the move
					board[i][j] = ' ';
				}

			    // If the value of the current move	
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
				index = i;
				jndex = j;
				bestVal = moveVal;
				}
			}
		}
}


<<<<<<< HEAD
void ControlTutorial()
=======

int Evaluate(char board[5][5], char ai, char player)
>>>>>>> add-featureAI
{
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

void AImove(char board[5][5], char ai, char player, int& index, int& jndex, int moves)
{
	if(moves == 0)
	{
		system("cls");
		cout << "AI is thinking...";
	}
	FindBestPosition(board, ai, player, index, jndex, moves);
	board[index][jndex] = ai;
	SearchEmptyCell(board, index, jndex);
}