#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;
// Displays the table on the screen
void OutputTable(char table[], const int grid);

// Manage user's input
void Input(char table[], const int grid, int& index, int& jndex, char xo);

// Determines the end of the game
bool GameOver(char table[], char xo);

//Displays the menu
int Menu();

// Displays the  Control tutorial
void ControlTutorial();

// Game process
void Setup();



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


// Game process
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

	const int grid = 5;
	char table[grid][grid];

	// Creat table
	for (int i = 0; i < grid; i++)
	{
		for (int j = 0; j < grid; j++)
		{
			if (j == 1 || j == 3)
			{
				table[i][j] = '|';
				continue;
			}

			if (i == 1 || i == 3)
			{
				table[i][j] = '-';
				continue;
			}

			table[i][j] = ' ';
		}
	}

	// Beginning of the game
	while (!(endGame = GameOver(reinterpret_cast<char*>(table), xo)) && move != 9)
	{
		// Players change, player X always goes first
		if (xo == 'X')
		{
			xo = 'O';
		}
		else xo = 'X';

		Input(reinterpret_cast<char*>(table), grid, index, jndex, xo);

		move++;

	}

	OutputTable(reinterpret_cast<char*>(table), grid);

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

// Displays the table on the screen
void OutputTable(char table[], const int grid)
{
	for (int i = 0; i < grid; i++)
	{
		for (int j = 0; j < grid; j++)
		{
			cout << table[i * grid + j];
		}
		cout << endl;
	}
}

// Manage user's input
void Input(char table[], const int grid, int& index, int& jndex, char xo) {

	// The symbol that you press to move the X or O
	char press;

	do
	{
		OutputTable(table, grid);

		// Cycle for flashing symbol
		while (!_kbhit())
		{
			system("cls");

			if (table[index * grid + jndex] == xo)
				table[index * grid + jndex] = ' ';
			else table[index * grid + jndex] = xo;

			OutputTable(table, grid);

			Sleep(150);
		}

		press = _getch();

		system("cls");

		// Put symbol 
		if (press == 'f' || press == 'F')
		{
			table[index * grid + jndex] = xo;
			for (int i = 0; i < grid; i++)
			{
				for (int j = 0; j < grid; j++)
				{
					if (table[i * grid + j] == ' ')
					{
						index = i;
						jndex = j;
						i = grid;
						break;
					}
				}
			}
		}

		// Move Down
		if (press == 's' || press == 'S')
		{
			//Set space to the current position where was the symbol
			table[index * grid + jndex] = ' ';

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
			while (table[i * grid + j] != ' ')
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
			table[index * grid + jndex] = xo;
		}

		// Move Up
		if (press == 'w' || press == 'W')
		{
			table[index * grid + jndex] = ' ';

			if (index == 0)
			{
				index += 2;
			}

			int i = index - 2;
			int j = jndex;
			int count = 0;

			while (table[i * grid + j] != ' ')
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
			table[index * grid + jndex] = xo;
		}

		// Move Right
		if (press == 'd' || press == 'D')
		{
			table[index * grid + jndex] = ' ';

			if (jndex == 4)
			{
				jndex -= 2;
			}

			int i = index;
			int j = jndex + 2;
			int count = 0;

			while (table[i * grid + j] != ' ')
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
			table[index * grid + jndex] = xo;
		}

		// Move left
		if (press == 'a' || press == 'A')
		{
			table[index * grid + jndex] = ' ';
			if (jndex == 0)
			{
				jndex += 2;
			}
			int i = index;
			int j = jndex - 2;

			int count = 0;

			while (table[i * grid + j] != ' ')
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
			table[index * grid + jndex] = xo;
		}
	} while ((press != 'f' && press != 'F'));

}

// Determines the end of the game
bool GameOver(char table[], char xo)
{
	for (int i = 0; i < 5; i += 2)
	{
		for (int j = 0; j < 2; j += 2)
		{
			if (table[i * 5] == xo && table[i * 5 + 2] == xo && table[i * 5 + 4] == xo)
			{
				table[i * 5] = '+';
				table[i * 5 + 2] = '+';
				table[i * 5 + 4] = '+';
				return true;
			}
			if (table[0 + i] == xo && table[10 + i] == xo && table[20 + i] == xo)
			{
				table[0 + i] = '+';
				table[10 + i] = '+';
				table[20 + i] = '+';
				return true;
			}
		}
	}

	if ((table[0] == xo && table[12] == xo) && table[24] == xo)
	{
		table[0] = '+';
		table[12] = '+';
		table[24] = '+';
		return  true;
	}
	if ((table[4] == xo && table[12] == xo) && table[20] == xo)
	{
		table[4] = '+';
		table[12] = '+';
		table[20] = '+';
		return true;
	}

	return false;
}

//Displays the menu
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

// Displays the  Control tutorial
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

