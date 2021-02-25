#include <iostream>
#include <conio.h>
using namespace std;
//0: area
//1: wall
//2: box
//3: people
//4: destination
//5: the box overlaps with the destination
//6: the people overlaps with the destination



#define MAPX 12
#define MAPY 9

#define KEY_UP     'w'
#define KEY_DOWN   's'
#define KEY_LEFT   'a'
#define KEY_RIGHT  'd'
#define KEY_QUIT   'q'

bool quit = false;

int map[MAPY][MAPX] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 4, 0, 4, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0},
	{0, 1, 4, 2, 3, 0, 0, 0, 1, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0},
	{0, 1, 4, 0, 2, 0, 0, 1, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// draw a map
void drawMap(int map[MAPY][MAPX])
{
	for (int i = 0; i < MAPY; i++)
	{
		cout << "     ";
		for (int j = 0; j < MAPX; j++)
		{
			switch (map[i][j])
			{
			case 0: cout << ' '; break;
			case 1: cout << '@'; break;
			case 2: cout << '*'; break;
			case 3: cout << '&'; break;
			case 4: cout << '?'; break;
			case 5: cout << '!'; break;
			default:
				break;
			}
		}
		cout << endl;
	}
}


void Postion(int map[MAPY][MAPX], int* x, int* y) 
{
	for (int i = 0; i < MAPY; i++)
	{
		for(int j = 0; j < MAPX; j++)
			if (map[i][j] == 3)
			{
				*x = j;
				*y = i;
				return;
			}
	}
	return;
}

bool gameOver(int map[MAPY][MAPX])
{
	for (int i = 0; i < MAPY; i++)
	{
		for (int j = 0; j < MAPX; j++)
			if (map[i][j] == 4)
			{
			
				return false;
			}
	}
	system("cls");
	cout << "    恭喜你,游戏通关！" << endl;
	return true;
}


//change the map
bool changeMap(int map[MAPY][MAPX], int x1, int y1, int x2, int y2)
{
	//先找到人
	int posx, posy;
	Postion(map, &posx, &posy);
	
	//wall
	if (map[posy + y1][posx + x1] == 1) 	
		return false;			
	
	//area
	if (map[posy + y1][posx + x1] == 0)						
	{
		//go
		map[posy + y1][posx + x1] = map[posy][posx];
		map[posy][posx] = 0;
		return true;
	}
	
	// box 
	if ( map[posy + y1][posx + x1] == 2) {
		// wall
		if ( map[posy + y2][posx + x2] == 1)
			return false;
		//area
		if (map[posy + y2][posx + x2] == 0)
		{
			//doing
			map[posy + y2][posx + x2] = map[posy + y1][posx + x1];
			map[posy + y1][posx + x1] = map[posy][posx];
			map[posy][posx] = 0;
			return true;
		}
		//destination
		if ( map[posy + y2][posx + x2] == 4)
		{
			//doing
			map[posy + y2][posx + x2] = 5;//map[posy + y1][posx + x1];
			map[posy + y1][posx + x1] = map[posy][posx];
			map[posy][posx] = 0;
			return true;
		}


	}
		
	//box + area
	

	return false;
}


//move box
int moveBox(int map[MAPY][MAPX], char ch)
{
	
	int x1, y1, x2, y2;
	int posx, posy;
	Postion(map, &posx, &posy);
	switch (ch)
	{
	case KEY_UP:
		x1 = 0, y1 = -1, x2 = 0, y2 = -2;
		if (changeMap(map, x1, y1, x2, y2))
			return 1;
		return 0;
		
	case KEY_DOWN:
		x1 = 0, y1 = 1, x2 = 0, y2 = 2;
		if (changeMap(map, x1, y1, x2, y2))
			return 1;
		return 0;

	case KEY_LEFT:
		x1 = -1, y1 = 0, x2 = -2, y2 = 0;
		if (changeMap(map, x1, y1, x2, y2))
			return 1;
		return 0;

	case KEY_RIGHT:
		x1 = 1, y1 = 0, x2 = 2, y2 = 0;
		if (changeMap(map, x1, y1, x2, y2))
			return 1;
		return 0;

	case KEY_QUIT:
		quit = true;
	default:
		cout << "input error!!!" << endl;
		break;
	}

	return 0;
}

int main1() 
{
	drawMap(map);
	bool quit = false;
	int step = 0;
	char ch;
	do {
		cout << "   步数：" << step << endl;
		ch = _getch();
		step += moveBox(map, ch);
		system("cls");
		drawMap(map);
		quit = gameOver(map);

	} while (quit == false);


	
	system("pause");
	return 0;
}

