#include "MyLib.h"
#include <iostream>
using namespace std;

#define MAX 100

struct  Snake
{
	int x[MAX];
	int y[MAX];
	int Length;
	int Score;
};

void CreateMap();
void InitSnake(Snake&);
void DrawSnake(Snake);

void Add(Snake&, int [], int);
void Del(Snake&, int [], int);
void DelDrawSnake(Snake&);

void SnakeWorks(Snake&, int, int, int&, int&);
bool CrashWall(int, int);
bool BiteTail(Snake);

void CreateFood(Snake, int&, int&);
bool FoodOverideSnake(Snake, int, int);
bool EatFood(int, int, int, int);

void RunGame();
int Menu();
void GameOver(Snake);
void Nocursortype(); //Hàm ẩn con trỏ trên màn hình console

void CreateMap2();
void CreateFood2(Snake, int&, int&);
bool CrashWall2(int, int);
void RunGame2();

int main()
{
	Nocursortype();
	int choice;
	choice = Menu();
	switch (choice)
	{
	case 1:
		RunGame();
		break;
	case 2:
		RunGame2();
		break;
	default:
		RunGame2();
		break;
	}
	return 0;
}

void CreateMap()
{
	SetColor(10);
	//Tường trên.
	int x = 10, y = 1;
	while (x < 100)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
		Sleep(5);
	}
	//Tường phải.
	x = 100; y = 1;
	while (y < 26)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
		Sleep(9);
	}
	//Tường dưới.
	x = 100; y = 26;
	while (x >=10)
	{
		gotoXY(x, y);
		cout << "+";
		x--;
		Sleep(5);
	}
	//Tường trái.
	x = 10; y = 26;
	while (y >= 1)
	{
		gotoXY(x, y);
		cout << "+";
		y--;
		Sleep(9);
	}
	Sleep(200);
}

void DrawSnake(Snake s)
{
	for (int i = 0; i < s.Length; i++)
	{
		gotoXY(s.x[i], s.y[i]);
		if(i==0) // Đầu rắn.
			cout << "0";
		else
			cout << "o";
	}
}

void InitSnake(Snake &s)
{
	//Rắn ban đầu nằm ở giữa map và hường từu trái sang phải.
	int x = 50, y = 13;
	s.Length = 4;
	s.Score = 0;
	for (int i = 0; i < s.Length; i++)
	{
		s.x[i] = x;
		s.y[i] = y;
		x--;
	}
}

void SnakeWorks(Snake &s, int x, int y, int& xqua, int& yqua)
{
	Add(s, s.x, x);
	Add(s, s.y, y);
	if (!EatFood(s.x[0], s.y[0], xqua, yqua))
	{
		Del(s,s.x, s.Length-1);
		Del(s,s.y, s.Length-1);
	}
	else
	{
		CreateFood(s, xqua, yqua);
		s.Length++;
		s.Score = s.Score + 10;
	}
	DrawSnake(s);
}

void Add(Snake &s, int a[], int x)
{
	for (int i = s.Length; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
	s.Length++;
}

void Del(Snake &s, int a[], int vt)
{
	for (int i = vt; i < s.Length; i++)
	{
		a[i] = a[i + 1];
	}
	s.Length--;
}

void DelDrawSnake(Snake &s)
{
	for (int i = 0; i < s.Length; i++)
	{
		gotoXY(s.x[i], s.y[i]);
		cout << " "; //In ra khoảng trắng để xóa đi rắn trước khi in ra một rắn mới.
	}
}

bool CrashWall(int x, int y)
{
	//Kiểm tra đầu rắn trùng với tọa của tường.
	if (y == 1 && (x >= 10 && x <= 100))
		return true;
	if (y == 26 && (x >= 10 && x <= 100))
		return true;
	if (x == 100 && (y >= 1 && y <= 26))
		return true;
	if (x == 10 && (y >= 1 && y <= 26))
		return true;
	return false;
}

bool BiteTail(Snake s)
{
	//Kiểm tra đầu rắn chạm trừng với tọa độ của rắn.
	for (int i = 1; i < s.Length; i++)
	{
		if ((s.x[0] == s.x[i]) && (s.y[0] == s.y[i]))
			return true;
	}
	return false;
}

void CreateFood(Snake s, int &x, int &y)
{
	do
	{
		x = rand() % 89 + 11;
		y = rand() % 24 + 2;
	} while (FoodOverideSnake(s, x, y)); 
	int i = rand() % 15 + 1;
	SetColor(i);
	gotoXY(x, y);
	cout << "$";
}

bool FoodOverideSnake(Snake s, int x, int y)
{
	//Kiểm tra food được tạo ra trừng với tọa độ của rắn.
	for (int i = 0; i < s.Length; i++)
	{
		if (x == s.x[i] && y == s.y[i])
			return true;
	}
	return false;
}

bool EatFood(int x0, int y0, int xqua, int yqua)
{
	//Kiểm tra đầu rắn trùng với tọa độ food.
	if (x0 == xqua && y0 == yqua)
		return true;
	return false;
}

void RunGame()
{
	system("cls");
	bool Over = false;
	Snake s;
	int x = 50, y = 13;
	int xq = 0, yq = 0;
	int check = 2;
	int Time = 5;
	CreateMap();
	InitSnake(s);
	DrawSnake(s);
	SetColor(10);
	while(Time > -1)
	{
		gotoXY(40, 20);
		cout << "Start in: " << Time << " seconds";
		Sleep(1000);
		gotoXY(40, 20);
		cout << "                   ";
		Time--;
	}
	srand(time(NULL));
	CreateFood(s, xq, yq);
	while (!Over)
	{
		DelDrawSnake(s);
		if (_kbhit())
		{
			char kitu = _getch();
			if (kitu == -32)
			{
				kitu = _getch();
				if (kitu == 72 && check != 0)
				{
					check = 1;
				}
				else if (kitu == 80 && check != 1)
				{
					check = 0;
				}
				else if (kitu == 77 && check != 3)
				{
					check = 2;
				}
				else if (kitu == 75 && check != 2)
				{
					check = 3;
				}
			}
		}
		if (check == 0)
		{
			y++;
		}
		else if (check == 1)
		{
			y--;
		}
		else if (check == 2)
		{
			x++;
		}
		else if (check == 3)
		{
			x--;
		}
		SnakeWorks(s, x, y, xq, yq);
		Over = BiteTail(s);
		if (Over)
			continue;
		Over = CrashWall(s.x[0], s.y[0]);
		Sleep(110);
	}
	GameOver(s);
}

int Menu()
{
	int choice = 0, i;
	srand(time(NULL));
	while (choice==0)
	{
		if (_kbhit())
			choice = _getch();
		system("cls");
		i = rand() % 15 + 1;
		SetColor(i);
		cout << "   ===     =      =      =      ==    ==  ========" << endl;
		cout << " ==   ==   ==     =     = =     ==   =    ==" << endl;
		cout << "==         =  =   =    == ==    ==  =     ==" << endl;
		cout << "   ===     =   =  =   ==   ==   ====      ======" << endl;
		cout << "       ==  =    = =  === = ===  ==  =     ==" << endl;
		cout << " ==   ==   =     ==  =       =  ==   =    ==" << endl;
		cout << "   ===     =      =  ==     ==  ==    ==  ========" << endl;
		cout << endl;
		cout << "     PRESS ANY KEY TO CONTINUE :V" << endl;
		cout << endl;
		Sleep(300);
	}
	cout << "1_Classic" << endl;
	cout << "2_Obstacle" << endl;
	cout << "TYPE YOUR CHOICE: ";
	cin >> choice;
	return choice;
}

void GameOver(Snake s)
{
	gotoXY(10, 30);
	cout << "  =====        =      =      =    =====     =        =  ========  =======" << endl;
	gotoXY(10, 31);
	cout << "==     ==     = =     ==    ==  ==     ==   =        =  ==        ==     =" << endl;
	gotoXY(10, 32);
	cout << "==     ==    == ==    = =  = =  ==     ==   ==      ==  ==        ==     =" << endl;
	gotoXY(10, 33);
	cout << "==          ==   ==   =  ==  =  ==     ==    ==    ==   ======    == ====       SCORE: "<<s.Score << endl;
	gotoXY(10, 34);
	cout << "==   ====  === = ===  =      =  ==     ==     ==  ==    ==        == ==" << endl;
	gotoXY(10, 35);
	cout << "==     ==  =       =  =      =  ==     ==      ====     ==        ==  ==" << endl;
	gotoXY(10, 36);
	cout << "  =====    ==     ==  =      =    =====         ==      ========  ==   ==" << endl;
	gotoXY(10, 37);
}

void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void CreateMap2()
{
	SetColor(10);
	//Tường trên.
	int x = 10, y = 1;
	while (x < 100)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
		Sleep(5);
	}
	//Tường phải.
	x = 100; y = 1;
	while (y < 26)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
		Sleep(9);
	}
	//Tường dưới.
	x = 100; y = 26;
	while (x >= 10)
	{
		gotoXY(x, y);
		cout << "+";
		x--;
		Sleep(5);
	}
	//Tường trái.
	x = 10; y = 26;
	while (y >= 1)
	{
		gotoXY(x, y);
		cout << "+";
		y--;
		Sleep(9);
	}
	x = 11; y = 9;
	while (x<=40)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
	}
	x = 65; y = 2;
	while (y<=13)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
	}
	x = 28; y = 20;
	while (x<=75)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}

void CreateFood2(Snake s, int &x, int &y)
{
	do
	{
		x = rand() % 89 + 11;
		y = rand() % 24 + 2;
	} while (FoodOverideSnake(s, x, y) || (y == 9 && x >= 11 && x <= 40) || (x == 65 && y >= 2 && y <= 13) || (y == 20 && x >= 28 && x <= 75));
	int i = rand() % 15 + 1;
	SetColor(i);
	gotoXY(x, y);
	cout << "$";
}

bool CrashWall2(int x, int y)
{
	//Kiểm tra đầu rắn trùng với tọa của tường.
	if (y == 1 && (x >= 10 && x <= 100))
		return true;
	if (y == 26 && (x >= 10 && x <= 100))
		return true;
	if (x == 100 && (y >= 1 && y <= 26))
		return true;
	if (x == 10 && (y >= 1 && y <= 26))
		return true;
	if ((y == 9 && x >= 11 && x <= 40) || (x == 65 && y >= 2 && y <= 13) || (y == 20 && x >= 28 && x <= 75))
		return true;
	return false;
}

void RunGame2()
{
	system("cls");
	bool Over = false;
	Snake s;
	int x = 50, y = 13;
	int xq = 0, yq = 0;
	int check = 2;
	int Time = 5;
	CreateMap2();
	InitSnake(s);
	DrawSnake(s);
	SetColor(10);
	while (Time > -1)
	{
		gotoXY(40, 22);
		cout << "Start in: " << Time << " seconds";
		Sleep(1000);
		gotoXY(40, 22);
		cout << "                   ";
		Time--;
	}
	srand(time(NULL));
	CreateFood2(s, xq, yq);
	while (!Over)
	{
		DelDrawSnake(s);
		if (_kbhit())
		{
			char kitu = _getch();
			if (kitu == -32)
			{
				kitu = _getch();
				if (kitu == 72 && check != 0)
				{
					check = 1;
				}
				else if (kitu == 80 && check != 1)
				{
					check = 0;
				}
				else if (kitu == 77 && check != 3)
				{
					check = 2;
				}
				else if (kitu == 75 && check != 2)
				{
					check = 3;
				}
			}
		}
		if (check == 0)
		{
			y++;
		}
		else if (check == 1)
		{
			y--;
		}
		else if (check == 2)
		{
			x++;
		}
		else if (check == 3)
		{
			x--;
		}
		SnakeWorks(s, x, y, xq, yq);
		Over = BiteTail(s);
		if (Over)
			continue;
		Over = CrashWall2(s.x[0], s.y[0]);
		Sleep(110);
	}
	GameOver(s);
}