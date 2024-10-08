#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<fstream>
using namespace std;
fstream savegrid;
int grid[9][9] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
bool edit[9][9];
void save(char * path) 
{
	savegrid.open(path);
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			savegrid << grid[i][j] << edit[i][j]<<" ";
		}
		savegrid << "\n";
	}
	savegrid.close();
}
bool load(char * path) 
{
	ifstream loadgrid;
	loadgrid.open(path);
	if (loadgrid.peek() == std::ifstream::traits_type::eof()) 
	{
		loadgrid.close();
		return false;
	}
	int x;
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			loadgrid >> x;
			grid[i][j] = x / 10;
			edit[i][j] = x % 10;
		}
	}
	loadgrid.close();
	return true;
}
bool checkwin()
{
	for (int a = 0; a < 9; a++)
	{
		for (int b = 0; b < 9; b++)
		{
			if (grid[a][b] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
void myRectangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B)); //Fill color can also be passed as parameter to the function!!!
	SelectObject(device_context, brush);
	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void print()
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	//myRectangle(1, 1, 10000, 10000, 128, 128, 128);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	cout << "  0   1   2   3   4   5   6   7   8\n";
	for (int i = 0; i < 9; i++)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
		cout << "_____________________________________\n";
		for (int j = 0; j < 9; j++)
		{
			SetConsoleTextAttribute(h, FOREGROUND_GREEN);
			if (grid[i][j] == 0)
				cout << "|" << " " << " " << " ";
			else {
				cout << "|" << " ";
				if (edit[i][j] == true) 
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE);
				}
				else 
				{
					SetConsoleTextAttribute(h, FOREGROUND_RED);
				}
				cout << grid[i][j] << " ";
			}
		}
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
		cout << "|"<<" " << i;
		cout << endl;
	}
}
bool isvalid(int row, int col, int num)
{
	int r, c;
	if (grid[row][col] != 0)
	{
		return false;
	}
	for (c = 0; c < 9; c++)
	{
		if (grid[row][c] == num)
		{
			return false;
		}
	}
	for (r = 0; r < 9; r++)
	{
		if (grid[r][col] == num)
		{
			return false;
		}
	}
	row = row - (row % 3);
	col = col - (col % 3);
	for (int i = row; i < row + 3; i++)
	{
		for (int j = col; j < col + 3; j++)
		{
			if (grid[i][j] == num)
			{
				return false;
			}
		}
	}
	return true;
}
bool checkinput(int x, int y, int n)
{
	int r, c;
	// checking row
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
		{
			if (r == x && c == y)
			{
				for (int a = 0; a < 9; a++)
				{
					if (grid[x][a] == n)
					{
						return false;
					}
				}
			}
		}
	}
	// checking column
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
		{
			if (r == x && c == y)
			{
				for (int a = 0; a < 9; a++)
				{
					if (grid[a][y] == n)
					{
						return false;
					}
				}
			}
		}
	}
	x = x - (x % 3);
	y = y - (y % 3);
	// checking board 3 by 3
	for (int i = x; i < x + 3; i++)
	{
		for (int j = y; j < y + 3; j++)
		{
			if (grid[i][j] == n)
			{
				return false;
			}
		}
	}
	return true;
}
void generaterandomnumber()
{
	srand(time(0));
	int i, j, n;
	for (int x = 0; x < 20; x++)
	{
		do {
			i = rand() % 9;
			j = rand() % 9;
			n = rand() % 9 + 1;

		} while (isvalid(i, j, n) == false);
		grid[i][j] = n;
		edit[i][j] = false;
	}
	print();
}
void fiLLboard(char *path)
{
	int x, y, i, j;
	int m;
	bool win = true;
	while (checkwin() == false)
	{
		save(path);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
		cout << "Enter -1 to save and exit the game\nEnter row number from 0 to 8 = ";
		cin >> x;
		if (x == -1) 
		{
			win = false;
			break;
		}
		cout << "Enter column number from 0 to 8 = ";
		cin >> y;
		cout << "Enter number between 1 to 9 which you want to insert = ";
		cin >> m;
		cout << endl;
		if (m > 0 && m < 10 && x >= 0 && x < 9 && y >= 0 && y < 9)
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED);
			if (checkinput(x, y, m) && edit[x][y] == true)
			{
				grid[x][y] = m;
				if (edit[x][y] == true)
				{
					SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED);
				}
				else 
				{
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				}
				print();
			}
			else
			{
				cout << "try again\n";
			}
		}
		else
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, FOREGROUND_RED);
			cout << "Enter valid data\n";
		}
	}
	if (win == true) 
	{
		cout << "Congratulations you win!!\n";
		savegrid.open(path, std::ifstream::out | std::ifstream::trunc);
	}
	else
		cout << "You saved and exit the game\n";
}
char* select_path() 
{
	int choice;
	cout << "Enter the 1 to select slot 1 " << endl;
	cout << "Enter the 2 to select slot 2 " << endl;
	cout << "Enter the 3 to select slot 3 " << endl;
	cin >> choice;
	while (choice < 1 || choice>3) 
	{
		cout << "Please enter valid input\n";
		cout << "Enter the 1 to select slot 1 " << endl;
		cout << "Enter the 2 to select slot 2 " << endl;
		cout << "Enter the 3 to select slot 3 " << endl;
		cin >> choice;
	}
	if (choice == 1) 
	{
		return "save/slot1.txt";
	}
	if (choice == 2) 
	{
		return "save/slot2.txt";
	}
	if (choice == 3) 
	{
		return "save/slot3.txt";
	}
}

int main()
{
	for (int n = 0; n < 9; n++) 
	{
		for (int x = 0; x < 9; x++) 
		{
			edit[n][x] = true;
		}
	}
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	cout << "---------------WELCOME TO SUDOKU---------------\n";
	SetConsoleTextAttribute(h, FOREGROUND_RED);

	cout << "Before Using The Game You Are Given The Following Instructions\n";
	SetConsoleTextAttribute(h, FOREGROUND_BLUE);
	cout << "-> You Will Be Given A Board Of 9 By 9\n-> You Will Have To Filled The Board By Entering The Numbers Between 1 And 9\n";
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "Enter 1 For Load The Game\n";
	cout << "Enter 2 For Start The Game\n";
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN);
	int Choice;
	char * path;
	cout << "Enter Your Choice\n";
	cin >> Choice;
	while (Choice != 1 && Choice != 2) 
	{
		cout << "Please enter valid input\n";
		cin >> Choice;
	}
	if (Choice == 1)
	{
		path = select_path();
		bool status = load(path);
		if (status == true) 
		{
			print();
			fiLLboard(path);
		}
		else 
		{
			cout << "Not Save File Found";
			cout << endl;
		}
	}
	else if (Choice == 2)
	{

		path = select_path();
		generaterandomnumber();
		fiLLboard(path);
	}
	else
	{
		cout << "User has enter invalid data";
		cout << endl;
	}
	system("pause");
	return 0;
}




