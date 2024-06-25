#include <iostream>
#include <iomanip>	//For pretty output of arrays
#include <vector>	//Arrays
#include <Windows.h>//For color in console
#include <chrono>   //For counting time
using namespace std;

class cell
{
private:
	bool state;//0-closed 1-opened
	bool flag;//0-no flag 1-flag placed
	int number;//0-8 number of  mines 9-mine
public:
	cell() :state(0), number(0), flag(0) {}
	//Set
	void SetState(bool state)
	{
		this->state = state;
	}
	void SetFlag(bool flag)
	{
		this->flag = flag;
	}
	void SetNumber(int number)
	{
		this->number = number;
	}
	//Get
	bool GetState() { return state; }
	bool GetFlag()  { return flag; }
	int GetNumber() { return number; }
	//NumUp
	void NumUp()
	{
		number+=1;
	}
	//Show
	void ShowNumber()
	{
		cout << " "<< number;
	}
	void ShowState()
	{
		cout <<" " << state;
	}
};

//Main functions
//Art
void DrawLogo(HANDLE cons)
{
	SetConsoleTextAttribute(cons, 7);
	cout << "      __  ________   ______________       __________________  __________ \n";
	cout << "     /  |/  /  _/ | / / ____/ ___/ |     / / ____/ ____/ __ \\/ ____/ __ \\\n";
	cout << "    / /|_/ // //  |/ / __/  \\__ \\| | /| / / __/ / __/ / /_/ / __/ / /_/ /\n";
	cout << "   / /  / // // /|  / /___ ___/ /| |/ |/ / /___/ /___/ ____/ /___/ _, _/ \n";
	cout << "  /_/  /_/___/_/ |_/_____//____/ |__/|__/_____/_____/_/   /_____/_/ |_|    C++ console edition\n";
}
void ShowCredits(HANDLE cons)
{
	cout << "Code: Myroslav D.\n";
	cout << "Idea: Robert Donner\n";
	cout << "THX you for plaing\n";
	Sleep(2000);
}
//PreGame
void DrawField(vector<vector<cell>> obj, int const size, HANDLE cons)
{
	int bgColor = 128;
	SetConsoleTextAttribute(cons, 7);
	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		cout << i << " ";
	}
	cout << "Y\n";
	for (int i = 0; i < size; i++)
	{
		SetConsoleTextAttribute(cons, 7);
		if (i < 10) cout << i << "  ";
		else if (i < 99) cout << i << " ";
		for (int j = 0; j < size; j++)
		{
			if (obj[i][j].GetState() == 0)
			{
				if (obj[i][j].GetFlag() == 0)
				{
					SetConsoleTextAttribute(cons, bgColor + 7);
					cout << "|_";
				}
				else
				{
					SetConsoleTextAttribute(cons, bgColor + 4);
					cout << "//";
				}
			}
			else
			{
				if (obj[i][j].GetNumber() == 1)
				{
					SetConsoleTextAttribute(cons, bgColor + 1);
					cout << " 1";
				}
				else if (obj[i][j].GetNumber() == 2)
				{
					SetConsoleTextAttribute(cons, bgColor + 2);
					cout << " 2";
				}
				else if (obj[i][j].GetNumber() == 3)
				{
					SetConsoleTextAttribute(cons, bgColor + 4);
					cout << " 3";
				}
				else if (obj[i][j].GetNumber() == 4)
				{
					SetConsoleTextAttribute(cons, bgColor + 9);
					cout << " 4";
				}
				else if (obj[i][j].GetNumber() == 5)
				{
					SetConsoleTextAttribute(cons, bgColor + 12);
					cout << " 3";
				}
				else if (obj[i][j].GetNumber() == 6)
				{
					SetConsoleTextAttribute(cons, bgColor + 11);
					cout << " 6";
				}
				else if (obj[i][j].GetNumber() == 7)
				{
					SetConsoleTextAttribute(cons, bgColor + 5);
					cout << " 7";
				}
				else if (obj[i][j].GetNumber() == 8)
				{
					SetConsoleTextAttribute(cons, bgColor +8);
					cout << " 8";
				}
				//FOR DEBUGGING PURPUSE
				else if (obj[i][j].GetNumber() == 9)
				{
					SetConsoleTextAttribute(cons, bgColor + 0);
					cout << " *";
				}
				/////
				else
				{
					SetConsoleTextAttribute(cons, bgColor + 0);
					cout << "  ";
				}

			}
		}
		cout << "\n";

	}
	SetConsoleTextAttribute(cons, 7);
	cout << "X\n";
}
void FillBombs(vector<vector<cell>>& obj, int const size)
{
	int x;
	int y;
	int numBomb;
	bool loop=1;

	if (size == 8) numBomb = 10;
	else if (size == 16) numBomb = 32;
	else numBomb = size;

	for (int i = 0; i < numBomb; i++)
	{
		loop = 1;
		do
		{
			x = rand() % size;
			y = rand() % size;
			if (obj[x][y].GetNumber() != 9)
			{
				obj[x][y].SetNumber(9);
				loop = 0;
			}
		} while (loop);
		
	}
}
void SetNumbers(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (obj[i][j].GetNumber() == 9)
			{
				if (i > 0)
					if (obj[i - 1][j].GetNumber() != 9)
						obj[i - 1][j].NumUp();

				if (j > 0)
					if (obj[i][j - 1].GetNumber() != 9)
						obj[i][j - 1].NumUp();
				
				if (i > 0 and j > 0)
					if (obj[i - 1][j - 1].GetNumber() != 9)
						obj[i - 1][j - 1].NumUp();

				if (i < size-1)
					if (obj[i + 1][j].GetNumber() != 9)
						obj[i + 1][j].NumUp();

				if (j < size-1)
					if (obj[i][j + 1].GetNumber() != 9)
						obj[i][j + 1].NumUp();

				if (i < size-1 and j < size-1)
					if (obj[i + 1][j + 1].GetNumber() != 9)
						obj[i + 1][j + 1].NumUp();

				if (i > 0 and j < size-1)
					if (obj[i - 1][j + 1].GetNumber() != 9)
						obj[i - 1][j + 1].NumUp();

				if (i < size-1 and j > 0)
					if (obj[i + 1][j - 1].GetNumber() != 9)
						obj[i + 1][j - 1].NumUp();
			}
		}
	}
}
void ClearField(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			obj[i][j].SetNumber(0);
			obj[i][j].SetFlag(0);
		}
	}
}
void SetFieldState(vector<vector<cell>>& obj, int const size, int state)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			obj[i][j].SetState(state);
		}
}
void PreGame(cell Cell, vector<vector<cell>>& Field, int const size)
{
	for (int i = 0; i < size; i++)
	{
		vector<cell>column;
		for (int j = 0; j < size; j++)
			column.push_back(Cell);
		Field.push_back(column);
	}

	ClearField(Field, size);

	FillBombs(Field, size);
	SetNumbers(Field, size);

	SetFieldState(Field, size, 0);
}
//Game functions
int GameWon(vector<vector<cell>>& obj, int const size)
{
	int numBomb = 0;
	int numFlag = 0;
	int numFlagIs = 0;
	if (size == 8) { numBomb = 10; numFlagIs = 10; }
	else if (size == 16) { numBomb = 32; numFlagIs = 32; }
	else numBomb = size;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (obj[i][j].GetNumber() == 9 and obj[i][j].GetFlag() == 1) { numBomb--; numFlag++; }
		}
	}
	if (numBomb == 0 and numFlag==numFlagIs)
	{
		return 1;//game won
	}
	else
	{
		return 0;//continue
	}
}
int OpenCell(vector<vector<cell>>& obj, int const size, int x, int y)
{
	if (obj[x][y].GetState() == 0)
	{
		if (obj[x][y].GetNumber() == 9)
		{
			obj[x][y].SetState(1);
			return 1;//Game over
		}
		else if (obj[x][y].GetNumber() == 0)
		{
			obj[x][y].SetState(1);

			if (x > 0)
				OpenCell(obj, size, x - 1, y);
			if (y > 0)
				OpenCell(obj, size, x, y - 1);
			if (x > 0 and y > 0)
				OpenCell(obj, size, x - 1, y - 1);
			if (x < size - 1)
				OpenCell(obj, size, x + 1, y);
			if(y<size-1)
				OpenCell(obj, size, x, y + 1);
			if (x < size-1 and y < size-1)
				OpenCell(obj, size, x + 1, y + 1);
			if (x > 0 and y < size - 1)
				OpenCell(obj, size, x - 1, y + 1);
			if (x > 0 and y < size - 1)
				OpenCell(obj, size, x - 1, y + 1);
			if (x < size - 1 and y>0)
				OpenCell(obj, size, x + 1, y - 1);
		}
		else
		{
			obj[x][y].SetState(1);
			return 0;
			//Stop opening
		}
	}
	else
	{
		return 0;
		//Stop opening
	}
}
void PutFlag(vector<vector<cell>>& obj, int x, int y)
{
	if (obj[x][y].GetFlag() == 0)
	{
		obj[x][y].SetFlag(1);
	}
	else
	{
		obj[x][y].SetFlag(0);
	}
}
void EndGame(int state, int start, int end, HANDLE cons)
{
	if (state == 1)
	{
		SetConsoleTextAttribute(cons, 4);
		cout << "Game over\n";
	}
	else if (state == 2)
	{
		SetConsoleTextAttribute(cons, 2);
		cout << "Congratulations! Game won!\n";
	}
	SetConsoleTextAttribute(cons, 7);
	cout << "Time:";
	SetConsoleTextAttribute(cons, 3);
	cout << (end - start) / 1000 << "\n";
	SetConsoleTextAttribute(cons, 7);
}
//Main game proccess
void Game(vector<vector<cell>>& obj, int const size, HANDLE cons)
{
	int x, y;
	int choice;
	bool loop=1;

	int start = clock();

	while (loop)
	{
		DrawLogo(cons);
		DrawField(obj, size, cons);
		cout << "1-Open Cell\n2-Put/TakeOut Flag\n0-Surrender\n";
		cout << "Input Choice:"; cin >> choice;
		switch (choice)
		{
		case 1: 
		{
			do
			{ 
				cout << "Input X:"; cin >> x;
			} while (x<0 or x>size-1);
			do
			{
				cout << "Input Y:"; cin >> y;
			} while (y<0 or y>size-1);
			if (OpenCell(obj, size, x, y)==1)
			{
				
				loop = 0; 
				SetFieldState(obj, size, 1);

				int end = clock();
				EndGame(1, start, end, cons);
				DrawField(obj, size, cons); 
				Sleep(3000);
			}

		} break;
		case 2: 
		{
			do
			{
				cout << "Input X:"; cin >> x;
			} while (x<0 or x>size-1);
			do
			{
				cout << "Input Y:"; cin >> y;
			} while (y<0 or y>size-1);
			PutFlag(obj, x, y);
			if (GameWon(obj, size) == 1)
			{
				
				loop = 0;
				SetFieldState(obj, size, 1);
				system("cls");
				DrawField(obj, size, cons);

				int end = clock();
				EndGame(2, start, end, cons);
				Sleep(3000);
			}
		} break;
		case 0: 
		{ 
			
			loop = 0; 
			SetFieldState(obj, size, 1);

			int end = clock();
			EndGame(0, start, end, cons);
			DrawField(obj, size, cons);
			Sleep(3000);
			
		}break;
		default:cout << "Wrong input\n"; break;
		}
		system("cls");
	}
}

//Development functions
void ShowStateAll(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			obj[i][j].ShowState();
		}
		cout << "\n";
	}
	cout << "\n";
}
void ShowNumberAll(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			obj[i][j].ShowNumber();
		}
		cout << "\n";
	}
	cout << "\n";
}


int main()
{
	int const size_easy = 8;
	int const size_medium = 16;
	bool flag = 1;
	int choice=0;
	cell Cell;
	vector<vector<cell>>Field;

	HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	SetConsoleTextAttribute(cons, 135);

	while (flag)
	{
		Field.clear();
		DrawLogo(cons);

		cout << "1 - easy(10 mines)\n2 - normal(32 mines)\n0 - exit\n";
		cout << "Input your choice:"; cin >> choice;

		switch (choice)
		{
		case 0:
			system("cls");
			flag = 0;
			break;
		case 1:

			system("cls");
			PreGame(Cell, Field, size_easy);
			Game(Field, size_easy, cons);

			break;
		case 2:

			system("cls");
			PreGame(Cell, Field, size_medium);
			Game(Field, size_medium, cons);

			break;
		default:system("cls"); cout << "Wrong choice\n"; break;
		}
	}
	ShowCredits(cons);
}

//      __  ________   ______________       __________________  __________ 
//     /  |/  /  _/ | / / ____/ ___/ |     / / ____/ ____/ __ \/ ____/ __ \
//    / /|_/ // //  |/ / __/  \__ \| | /| / / __/ / __/ / /_/ / __/ / /_/ /
//   / /  / // // /|  / /___ ___/ /| |/ |/ / /___/ /___/ ____/ /___/ _, _/ 
//  /_/  /_/___/_/ |_/_____//____/ |__/|__/_____/_____/_/   /_____/_/ |_|  
//                                                                         
