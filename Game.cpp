#include <iostream>
#include <conio.h>

using namespace std;

int lastKey;
bool walls;
int tailX[100], tailY[100];
int nTail;
bool gameOver;
int width = 20;
const int height = 20;
int x, y, fruitX, fruitY;
int howManyFruits = 0;
bool bigfru = false;
int score;
enum  eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
	int levelDfclt;
	char h;
	cout << "Приветствую вас в игре snakePlusPlus \nЕсли вы страдаете от эпилепсии, то закроете приложение"<< endl <<"w,a,s,d - управление, х - Выход, p - Пауза" << endl;
	cout << "1: Easy\n2: Medium\n3: Hard\n Выберите уровень сложности: ";
	cin >> levelDfclt;
	switch (levelDfclt)
	{
	case 1:
		width = 40;
		break;
	case 2:
		width = 20;
		break;
	case 3:
		width = 10;
		break;
	}
	cout << endl << "Желаете усложнить задачy и сделать смертельные преграды (y/n)?";
	cin >> h;
	if (h == 'y')
		walls = true;
	else
		walls = false;
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % (width - 2);
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i <= width; i++) {
		if (i <= width)
			cout << "#";
		
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";

			}
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				if (howManyFruits % 5 == 0 && howManyFruits != 0)
				{ 
					cout << "O";
					bigfru = true;
				}
				else
					cout << "*";
			
			else{
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (print == false)
					cout << " ";
			}
		}
		cout << endl;
		
		
	}


	for (int i = 0; i <= width; i++) {
		cout << "#";
	}
	cout << " Score: " << score << endl;
	cout << endl;
}

void Input() {
	if (_kbhit()) {
		char temp = _getch();
		if (temp == 'a' && lastKey != 1)
		{
			dir = LEFT;
			lastKey = 2;
		}
		else if (temp == 'd' && lastKey != 2)
		{
			dir = RIGHT;
			lastKey = 1;
		}
		else if (temp == 's' && lastKey != 3)
		{
			dir = DOWN;
			lastKey = 4;
		}
		else if (temp == 'w' && lastKey != 4)
		{
			dir = UP;
			lastKey = 3;
		}
		else if (temp == 'p') {
			dir = STOP;
		}
		else if (temp == 'x')
			gameOver = true;
		
	}
}

void Logic() {
	int prefX = tailX[0];
	int prefY = tailY[0];
	int pref2x, pref2y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		pref2x = tailX[i];
		pref2y = tailY[i];
		tailX[i] = prefX;
		tailY[i] = prefY;
		prefX = pref2x;
		prefY = pref2y;
	}

	switch (dir) {
	case  LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (!walls) {
		if (x < 0)
			x = width - 2;
		if (y <  0)
			y = height - 1;
		if (x > width - 2)
			x = 0;
		if (y > height)
			y = 0;
	}

	

	else if ((walls == true) && (x > width - 2 || x < 0 || y > height || y < 0))
		gameOver = true;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
			cout << "Ты врезался в свой хвост!" << endl;
		}
	}

	if (x == fruitX && y == fruitY && bigfru == false)
	{ 
		howManyFruits++;
		score += 10;
		fruitX = rand() % (width - 2);
		fruitY = rand() % height;
		nTail++;
	}
	else if (x == fruitX && y == fruitY && bigfru == true)
	{
		howManyFruits++;
		score += 20;
		bigfru = false;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

int main() {
	
	
		setlocale(0, "");

		Setup();
		while (!gameOver) {
			Draw();
			Input();
			Logic();
		}

		cout << endl << "Игра окончена."<< endl <<"Good luck!";
		cout << endl << "Нажми А и ентер, чтобы выйти";
		string bob;
		cin >> bob;
	return 0;
	
}