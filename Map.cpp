#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}


void Map::Initdestination(int destination[BOXMAXMUN][2])
{
	for (int i = 0; i < BOXMAXMUN; i++)
		for (int j = 0; j < 2; j++)
			destination[i][j] = -1;

	return;
}


bool Map::openFile(int map[MAPY][MAPX], int *custom)
{
	system("cls");
	cout << "请输入你想玩的关数：   1-5关" << endl;
	cin >> *custom;

	char gameLevel[11] = { 'm' , 'a' , 'p' , '_' , '0' , 0 , '.' , 't' , 'x' , 't' , 0 };
	gameLevel[5] = *custom + 48;

	ifstream fileOfGettingGameData;
	fileOfGettingGameData.open(gameLevel);

	if (!fileOfGettingGameData)
	{
		std::cout << "未检测到关卡" << *custom << "的存在" << "\n请检查您在选择关卡时是否输入正确。" << std::endl;
		system("pause");
		return true;
	}

	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			fileOfGettingGameData >> map[i][j];

	return false;
}

bool Map::goingGame(int map[MAPY][MAPX])
{
LOOP1:
	int playerPos[2] = { 0 };
	int destinationPos[BOXMAXMUN][2] = { 0 };
	int desvalue = 0;
	int custom = 0;
	int step = 0;
	int num = 0;
	int i, j;

	bool isplayerdes = false;
	bool isboxdes = false;
	bool quit = false;

	vector<Box> boxs;


	while (openFile(map, &custom));

	for (i = 0; i < MAPY; i++)
	{
		for (j = 0; j < MAPX; j++)
		{
			if (map[i][j] == PLAYER)
			{
				playerPos[0] = i;
				playerPos[1] = j;
			}
			if (map[i][j] == BOX)
			{
				boxs.push_back(Box(i, j, isboxdes));
			}
			if (map[i][j] == DESTINATION)
			{
				destinationPos[desvalue][0] = i;
				destinationPos[desvalue][1] = j;
				desvalue++;
			}
		}
	}
	
	Player player(playerPos[1], playerPos[0], isplayerdes);

	printMap(map, custom);
	//start
	while (true)
	{
		if (getCommand(&player, boxs, map) == -1)
		{
			cout << "温馨提示 ：  您已选择退出游戏。" << endl;			
			return false;
		}
			
		printMap(map, custom);
		step += num;
		cout << "步数： " << step << endl;

		if (GameOver(map, boxs))
		{
			system("cls");
			cout << "\n\n\t\t\t\t\t恭喜通关， 智商真高\n";

			Sleep(500);
			cout << "是否继续？y/n" << endl;
			while (1)
			{			
				char ch = _getch();
				cout << ch << endl;
				if (ch == 'y')
					goto LOOP1;
				else if (ch == 'n')
					return false;
				else
					cout << "输入错误，请重新输入：";
			}
			
		}
			
	}
	
	return true;
}

void Map::printMap(int gameMap[MAPY][MAPX], int num)
{
	system("cls");
	cout << "\n\n************************ 第 " << num << " 关 ************************" << endl;
	cout << "\n*************** W - w:向上        S - s: 向下 ******************" << endl;
	cout << "*************** A - a:向左        D - d: 向右 ******************" <<"\n\n" << endl;


	for (int i = 0; i < MAPY; i++)
	{
		cout << "               ";
		for (int j = 0; j < MAPX; j++)
		{
			char gamestr[8] = { ' ' , 'O' , '#' , '&' , '?' ,  '!' , '$', 0 };
			cout << gamestr[gameMap[i][j]];
		}
		cout << endl;
	}
}

int Map::getCommand(Player *player, vector<Box> &boxs, int map[MAPY][MAPX])
{
	int posY = player->getPosY();
	int posX = player->getPosx();
	int posFirstY = 0, posFirstX = 0;
	int posSecondY = 0, posSecondX = 0;
	
	switch (_getch())
	{
	case 'W': case 'w':
		posFirstY = posY - 1;
		posFirstX = posX;

		posSecondY = posY - 2;
		posSecondX = posX;
		break;

	case 'A': case 'a':
		posFirstY = posY; 
		posFirstX = posX- 1;

		posSecondY = posY;
		posSecondX = posX - 2;
		break;


	case 'S': case 's':
		posFirstY = posY + 1;
		posFirstX = posX;

		posSecondY = posY + 2;
		posSecondX = posX;
		break;

	case 'D': case 'd':
		posFirstY = posY;
		posFirstX = posX + 1;

		posSecondY = posY ;
		posSecondX = posX + 2;
		break;

	case 'Q': case 'q':
		return -1;
		
	default:
		 //input error
		return 0;
	}

	if (map[posFirstY][posFirstX] == AREA)
	{
		if (player->getIsOnDestinationP())
		{
			map[posY][posX] = DESTINATION;
			map[posFirstY][posFirstX] = PLAYER;
			player->setNoDestinationP();
			player->setPos(posFirstY, posFirstX);
			return 1;
		}
		else {
			map[posY][posX] = AREA;
			map[posFirstY][posFirstX] = PLAYER;
			player->setPos(posFirstY, posFirstX);
			return 1;
		}
	}
	if (map[posFirstY][posFirstX] == DESTINATION)
	{
		if (player->getIsOnDestinationP())
		{
			map[posY][posX] = DESTINATION;
			map[posFirstY][posFirstX] = PLAYERDESTINATION;
			player->setPos(posFirstY, posFirstX);
			return 1;
		}
		else {
			map[posY][posX] = AREA;
			map[posFirstY][posFirstX] = PLAYERDESTINATION;
			player->setOnDestinationP();
			player->setPos(posFirstY, posFirstX);
			return 1;
		}
	}
	if (map[posFirstY][posFirstX] == BOX || map[posFirstY][posFirstX] == BOXDESTINATION)
	{
		if (map[posSecondY][posSecondX] == BOX || map[posSecondY][posSecondX] == WALL) return 0;

		if (map[posSecondY][posSecondX] == AREA)
		{
			if (player->getIsOnDestinationP())
			{
				for (int i = 0; i < boxs.size(); i++)
				{
					if (boxs[i].getPosX() == posFirstX && boxs[i].getPosY() == posFirstY)
					{
						if (boxs[i].getIsOnDestinationB())
						{
							map[posY][posX] = DESTINATION;
							map[posFirstY][posFirstX] = PLAYERDESTINATION;
							map[posSecondY][posSecondX] = BOX;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							boxs[i].setNoDestinationB();
							return 1;
						}
						else {
							map[posY][posX] = DESTINATION;
							map[posFirstY][posFirstX] = PLAYER;
							map[posSecondY][posSecondX] = BOX;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							player->setNoDestinationP();
							return 1;
						}
					}
				}
			}
			else {
				for (int i = 0; i < boxs.size(); i++)
				{
					if (boxs[i].getPosX() == posFirstX && boxs[i].getPosY() == posFirstY)
					{
						if (boxs[i].getIsOnDestinationB())
						{
							map[posY][posX] = AREA;
							map[posFirstY][posFirstX] = PLAYERDESTINATION;
							map[posSecondY][posSecondX] = BOX;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							player->setOnDestinationP();
							boxs[i].setNoDestinationB();
							return 1;
						}
						else {
							map[posY][posX] = AREA;
							map[posFirstY][posFirstX] = PLAYER;
							map[posSecondY][posSecondX] = BOX;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							return 1;
						}
					}
				}
			}
		}

		if (map[posSecondY][posSecondX] == DESTINATION)
		{
			if (player->getIsOnDestinationP())
			{
				for (int i = 0; i < boxs.size(); i++)
				{
					if (boxs[i].getPosX() == posFirstY && boxs[i].getPosY() == posFirstY)
					{
						if (boxs[i].getIsOnDestinationB())
						{
							map[posY][posX] = DESTINATION;
							map[posFirstY][posFirstX] = PLAYERDESTINATION;
							map[posSecondY][posSecondX] = BOXDESTINATION;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							return 1;
						}
						else {
							map[posY][posX] = DESTINATION;
							map[posFirstY][posFirstX] = PLAYER;
							map[posSecondY][posSecondX] = BOXDESTINATION;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							player->setNoDestinationP();
							return 1;
						}
					}
				}
			}
			else {
				for (int i = 0; i < boxs.size(); i++)
				{
					if (boxs[i].getPosX() == posFirstX && boxs[i].getPosY() == posFirstY)
					{
						if (boxs[i].getIsOnDestinationB())
						{
							map[posY][posX] = AREA;
							map[posFirstY][posFirstX] = PLAYERDESTINATION;
							map[posSecondY][posSecondX] = BOXDESTINATION;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							player->setOnDestinationP();
							return 1;
						}
						else {
							map[posY][posX] = AREA;
							map[posFirstY][posFirstX] = PLAYER;
							map[posSecondY][posSecondX] = BOXDESTINATION;
							player->setPos(posFirstY, posFirstX);
							boxs[i].setPos(posSecondY, posSecondX);
							boxs[i].setOnDestinationB();
							return 1;
						}
					}
				}
			}
		}
	}
	if (map[posFirstY][posFirstX] == WALL) return 0;

	return 0;	
}


bool Map::GameOver(int map[MAPY][MAPX], vector<Box> &boxs)
{
	for (int i = 0; i < boxs.size(); i++)
	{
		int y = boxs[i].getPosY();
		int x = boxs[i].getPosX();
		if (map[y][x] == BOX) 
			return false;			
	}
	return true;
}


