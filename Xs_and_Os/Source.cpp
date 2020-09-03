#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

void OutputBoard(char board[5][5]);// Displays the table on the screen
void Input(char board[5][5],  int& index, int& jndex, char xo);// Manage user's input
bool GameOver(char board[5][5], char xo);// Determines the end of the game
int Menu(); //Displays the menu
void ControlTutorial();// Displays the  Control tutorial
void Setup();// Game process



int main()
{
	while (1)
	{
		system("cls");

		switch (Menu())
		{
			case '1':
				
				Setup();

			break;

		case '2':

				ControlTutorial();

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
	while (!(endGame = GameOver(board, xo)) && move != 9)
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
	move = 0;

	endGame = false;

	xo = 'O';

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
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
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


bool GameOver(char board[5][5], char xo)
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

int Menu()
{
	int a;

	cout << "Start menu: ";
	cout << endl << "1. Play a game.";
	cout << endl << "2. See how to play.";
	cout << endl << "3. Exit." << endl;

	a = _getch();

	return a;
}


void ControlTutorial()
{
	system("cls");
	cout << "To move symbol use: " << endl;
	cout << endl << "       'W' to move UP " << endl;
	cout << "'A' to move LEFT ";
	cout << "   'D' to move RIGHT ";
	cout << endl << "       'S' to move DOWN ";
	cout << endl << endl << "To put symbol use: 'F'. " << endl << endl;
	cout << "Use english layout." << endl << endl;
	cout << "Press any key to continue...";
}

