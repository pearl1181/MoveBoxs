#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>

#define SIZE 10		//宏意义地图大小。
#define NUMBER 10	//宏定义最大箱子数目。(可以根据玩家自己制作的地图，而修改最大箱子数。)（个人认为10个箱子应该够了。）

//友情提示：箱子这个类，必须定义在玩家这个类的前面，请朋友们自行发掘为什么。
class Box
{
public:
	int placeI;
	int placeJ;

	Box();

	int move(int command);
};

class Player
{
public:
	int placeI;		//记录横坐标
	int placeJ;		//记录纵坐标

	Player();

	int move(int command);
	int push(int command, Box box[], int);
};


//玩家类的构造器。
Player::Player()
{
	placeI = -1;
	placeJ = -1;
}

//箱子类的构造器。
Box::Box()
{
	placeI = -1;
	placeJ = -1;
}

int Player::move(int command)
{
	switch (command)
	{
	case 1:
		placeI -= 1;
		break;

	case 2:
		placeJ -= 1;
		break;

	case 3:
		placeI += 1;
		break;

	case 4:
		placeJ += 1;

	default:
		break;
	}

	return 0;
}

int Player::push(int command, Box box[], int I)
{
	int tempI = placeI, tempJ = placeJ;

	switch (command)
	{
	case 1:
		tempI -= 1;
		break;

	case 2:
		tempJ -= 1;
		break;

	case 3:
		tempI += 1;
		break;

	case 4:
		tempJ += 1;
		break;

	default:
		break;
	}

	int temp = 0;//用于检索box里面的每个元素。
	while (temp < I)
	{
		if (box[temp].placeI == tempI && box[temp].placeJ == tempJ)
		{
			box[temp].move(command);
			break;
		}
		temp++;
	}

	move(command);

	return 0;
}

int Box::move(int command)
{
	switch (command)
	{
	case 1:
		placeI -= 1;
		break;

	case 2:
		placeJ -= 1;
		break;

	case 3:
		placeI += 1;
		break;

	case 4:
		placeJ += 1;
		break;

	default:
		break;
	}

	return 0;
}

int gettingData(int smallSquare[SIZE][SIZE], int number, Player* player, Box box[NUMBER], int* I, int star[NUMBER][2]);		//用于检索游戏数据
void printMap(int smallSquare[SIZE][SIZE], Player player, Box box[NUMBER], int I);	//打印地图
int getCommand();//接收用户输入。
void detect(Player* player, Box box[], int smallSquare[SIZE][SIZE], int* pointerFirst, int* pointerSecond, int command, int I);		//用于探测玩家指向方向前两块区域的内容。
int menu();		//创建菜单函数
int levelChoose();//关卡选择
void introduce();	//游戏介绍
void voluationForStar(int star[NUMBER][2]);
int weatherPass(int star[NUMBER][2], Box box[NUMBER], int);

int main()
{
	int smallSquare[SIZE][SIZE];		//地图,0表示墙壁，1表示箱子，2表示道路，3表示人物，4表示胜利终点

	Player player;		//定义对象(玩家)
	Box box[10];

	int I;		//用于记录地图上有多少个箱子。

	int star[NUMBER][2];//记录终点的位置。


LOOP1:

	I = 0;
	voluationForStar(star);//初始化星星的位置。用于检查游戏是否通关

	int level = menu();					//在菜单中选择关卡数。

	if (!gettingData(smallSquare, level, &player, box, &I, star))		//初始化地图
	{
		goto LOOP1;
	}

	int pointerFirst = -1, pointerSecond = -1;		//用于记录指向玩家朝向前的两个方格的内容。
	int command;		//用于接收玩家输入的内容
	while (1)
	{
		printMap(smallSquare, player, box, I);//打印地图。

		//注释起来的，是作者当时用于检查错误的时候用的，大家可以参考学习学习。(这里采用单步调试可能会有些麻烦，用我这种方式，个人觉得比较好。)
		//std::cout << "探测：" << pointerFirst << "  " << pointerSecond << std::endl;
		//std::cout << "玩家位置：" << player.placeJ << "  " << player.placeI << std::endl;
		//int temp;
		/*
		for( temp = 0 ; temp < I ; temp++ )
		{
			std::cout << "第" << temp << "个箱子的坐标：" << box[temp].placeJ << "   " << box[temp].placeI << std::endl;
		}
		*/

		command = getCommand();

		if (5 == command)
		{
			goto LOOP1;
		}
		else if (command > 0)		//用户有输入，且输入正确。
		{
			detect(&player, box, smallSquare, &pointerFirst, &pointerSecond, command, I);

			if (2 == pointerFirst || 4 == pointerFirst)		//前面是路。
			{
				player.move(command);
			}
			else if (1 == pointerFirst && 1 == pointerSecond)
			{
				;//玩家前面有两个箱子,明显推不动嘛，空语句处理。
			}
			else if (1 == pointerFirst && (2 == pointerSecond || 4 == pointerSecond))
			{
				player.push(command, box, I);//前面是箱子，再前面一个是路，那肯定要推噻。
			}
		}

		if (weatherPass(star, box, I))//检查是否通关
		{
			printMap(smallSquare, player, box, I);
			std::cout << "你胜利了，恭喜你!!!" << std::endl;
			system("pause");
			goto LOOP1;
		}


	}


	return 0;
}

int gettingData(int smallSquare[SIZE][SIZE], int number, Player* player, Box box[NUMBER], int* I, int star[NUMBER][2])
{
	char gameLevel[12] = { 'N' , 'u' , 'm' , 'b' , 'e' , 'r' ,0 , '.' , 't' , 'x' , 't' , 0 };		//用于检索游戏数据。
	gameLevel[6] = number + 48;			//整型转化为字符型，需要统一一下。


	std::ifstream fileOfGettingGameData;

	fileOfGettingGameData.open(gameLevel);	//打开游戏配置

	if (!fileOfGettingGameData)
	{
		std::cout << "未检测到关卡" << number << "的存在" << "\n请检查您在选择关卡时是否输入正确。" << std::endl;
		system("pause");
		return 0;
	}
	/*
	else
	{
		std::cout << "关卡初始化成功" << std::endl;
		Sleep( 500 );
	}
	*/

	//初始化地图，（检索游戏文件）
	int tempI, tempJ, temp = 0;//temp用于终点的计数。
	for (tempI = 0; tempI < SIZE; tempI++)
	{
		for (tempJ = 0; tempJ < SIZE; tempJ++)
		{
			fileOfGettingGameData >> smallSquare[tempI][tempJ];

			//人物位置单独计算
			if (3 == smallSquare[tempI][tempJ])
			{
				player->placeI = tempI;
				player->placeJ = tempJ;

				smallSquare[tempI][tempJ] = 2;
			}

			//箱子位置单独计算
			if (1 == smallSquare[tempI][tempJ])
			{
				box[(*I)].placeI = tempI;
				box[(*I)].placeJ = tempJ;

				smallSquare[tempI][tempJ] = 2;

				(*I)++;
			}

			//终点位置单独计算
			if (4 == smallSquare[tempI][tempJ])
			{
				star[temp][0] = tempI;
				star[temp][1] = tempJ;

				temp++;
			}
		}
	}

	return 1;
}

void printMap(int smallSquare[SIZE][SIZE], Player player, Box box[NUMBER], int I)
{
	int tempI, tempJ, temp;//temp用于检索数列box
	int weatherPrintBox = 0;	//0表示没有打印箱子，1表示打印了。

	system("cls");
	printf(" 0 1 2 3 4 5 6 7 8 9\n");
	for (tempI = 0; tempI < SIZE; tempI++)
	{
		printf("%d", tempI);
		for (tempJ = 0; tempJ < SIZE; tempJ++)
		{
			weatherPrintBox = 0;
			for (temp = 0; temp < I; temp++)
			{
				if (tempI == box[temp].placeI && tempJ == box[temp].placeJ)
				{
					printf("■");			//打印箱子。
					weatherPrintBox = 1;
					break;
				}
			}

			if (tempI == player.placeI && tempJ == player.placeJ)
			{
				std::cout << "▼";				//打印人物。
			}
			else if (2 == smallSquare[tempI][tempJ] && 0 == weatherPrintBox)
			{
				std::cout << "  ";				//打印道路。
			}
			else if (0 == smallSquare[tempI][tempJ])
			{
				std::cout << "▓";				//打印墙壁。
			}
			else if (4 == smallSquare[tempI][tempJ] && 0 == weatherPrintBox)
			{
				std::cout << "☆";				//打印终点。
			}
		}
		std::cout << "\n";
	}
}

int getCommand()
{
	int commandReturn = -1;		//表示没有输入

	switch (_getch())
	{
	case 'W':
	case 'w':
		commandReturn = 1;		//表示向上
		break;

	case 'A':
	case 'a':
		commandReturn = 2;		//表示向左
		break;

	case 'S':
	case 's':
		commandReturn = 3;		//表示向下
		break;

	case 'D':
	case 'd':
		commandReturn = 4;		//表示向右
		break;

	case 'B':
	case 'b':
		commandReturn = 5;		//表示返回选关界面
		break;

	case 10:
	case 13:
		commandReturn = 6;		//表示回车
		break;

	default:
		commandReturn = -2;		//表示用户错误输入
		break;
	}

	return (commandReturn);
}

void detect(Player* player, Box box[], int smallSquare[SIZE][SIZE], int* pointerFirst, int* pointerSecond, int command, int I)
{
	int tempFirstI, tempFirstJ, tempSecondI, tempSecondJ;		//用于记录玩家位置的前两个位置的坐标。
	int temp;		//用于检索box里的每一个元素。

	switch (command)
	{
	case 1:
		//计算玩家朝向的两个方向的方块的坐标，并且将其赋值。
		tempFirstI = player->placeI - 1;
		tempFirstJ = player->placeJ;

		tempSecondI = player->placeI - 2;
		tempSecondJ = player->placeJ;

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//检索范围未超出地图的情况。
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//范围超出地图的区块，将其按墙壁计算。
		else
		{
			*pointerFirst = 0;
		}

		if (tempSecondI >= 0 && tempSecondJ >= 0)
		{
			*pointerSecond = smallSquare[tempSecondI][tempSecondJ];
		}
		else
		{
			*pointerSecond = 0;
		}

		for (temp = 0; temp < I; temp++)
		{
			if (box[temp].placeI == tempFirstI && box[temp].placeJ == tempFirstJ)
			{
				*pointerFirst = 1;
			}
			else if (box[temp].placeI == tempSecondI && box[temp].placeJ == tempSecondJ)
			{
				*pointerSecond = 1;
			}
		}
		break;

	case 2:
		tempFirstI = player->placeI;
		tempFirstJ = player->placeJ - 1;

		tempSecondI = player->placeI;
		tempSecondJ = player->placeJ - 2;

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//检索范围未超出地图的情况。
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//范围超出地图的区块，将其按墙壁计算。
		else
		{
			*pointerFirst = 0;
		}

		if (tempSecondI >= 0 && tempSecondJ >= 0)
		{
			*pointerSecond = smallSquare[tempSecondI][tempSecondJ];
		}
		else
		{
			*pointerSecond = 0;
		}

		for (temp = 0; temp < I; temp++)
		{
			if (box[temp].placeI == tempFirstI && box[temp].placeJ == tempFirstJ)
			{
				*pointerFirst = 1;
			}
			else if (box[temp].placeI == tempSecondI && box[temp].placeJ == tempSecondJ)
			{
				*pointerSecond = 1;
			}
		}
		break;

	case 3:
		tempFirstI = player->placeI + 1;
		tempFirstJ = player->placeJ;

		tempSecondI = player->placeI + 2;
		tempSecondJ = player->placeJ;

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//检索范围未超出地图的情况。
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//范围超出地图的区块，将其按墙壁计算。
		else
		{
			*pointerFirst = 0;
		}

		if (tempSecondI >= 0 && tempSecondJ >= 0)
		{
			*pointerSecond = smallSquare[tempSecondI][tempSecondJ];
		}
		else
		{
			*pointerSecond = 0;
		}

		for (temp = 0; temp < I; temp++)
		{
			if (box[temp].placeI == tempFirstI && box[temp].placeJ == tempFirstJ)
			{
				*pointerFirst = 1;
			}
			else if (box[temp].placeI == tempSecondI && box[temp].placeJ == tempSecondJ)
			{
				*pointerSecond = 1;
			}
		}
		break;

	case 4:
		tempFirstI = player->placeI;
		tempFirstJ = player->placeJ + 1;

		tempSecondI = player->placeI;
		tempSecondJ = player->placeJ + 2;

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//检索范围未超出地图的情况。
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//范围超出地图的区块，将其按墙壁计算。
		else
		{
			*pointerFirst = 0;
		}

		if (tempSecondI >= 0 && tempSecondJ >= 0)
		{
			*pointerSecond = smallSquare[tempSecondI][tempSecondJ];
		}
		else
		{
			*pointerSecond = 0;
		}

		for (temp = 0; temp < I; temp++)
		{
			if (box[temp].placeI == tempFirstI && box[temp].placeJ == tempFirstJ)
			{
				*pointerFirst = 1;
			}
			else if (box[temp].placeI == tempSecondI && box[temp].placeJ == tempSecondJ)
			{
				*pointerSecond = 1;
			}
		}
		break;

	default:
		break;
	}
}

int menu()
{
	char ch[8] = { '-' , ' ' , ' ' , ' ' , '>' , ' ' , ' ' , ' ' };
	int pointer = 0, pointerBefore;
	static int level = 0;		//记录你选择的关卡数。
	int command = 0;

	while (1)
	{
		system("cls");		//实现清屏。
		printf("**************************************\n");
		printf("             %c%c开始游戏             \n", ch[0], ch[4]);
		printf("**************************************\n");
		printf("             %c%c选择关卡             \n", ch[1], ch[5]);
		printf("**************************************\n");
		printf("             %c%c游戏引导             \n", ch[2], ch[6]);
		printf("**************************************\n");
		printf("             %c%c退出游戏             \n", ch[3], ch[7]);

		pointerBefore = pointer;
		command = getCommand();
		switch (command)
		{
			//向上的情况
		case 1:
			if (0 == pointer)		//特殊情况。
			{
				pointer = 3;
			}
			else
			{
				pointer--;
			}
			break;

			//向下的情况
		case 3:
			if (3 == pointer)
			{
				pointer = 0;
			}
			else
			{
				pointer++;
			}
			break;

		case 6:

			if (0 == pointer)
			{
				if (0 == level)
				{
					system("cls");
					std::cout << "您没有选择任何关卡" << std::endl;
					system("pause");
					break;
				}
				else
				{
					return (level);
				}
			}
			else if (1 == pointer)			//游戏关卡选择
			{
				level = levelChoose();
			}
			else if (2 == pointer)			//游戏介绍
			{
				introduce();
			}
			else if (3 == pointer)
			{
				exit(0);		//表示退出程序。
			}


			break;


		default:
			std::cout << "输入错误" << std::endl;
			break;
		}

		ch[pointerBefore] = ' ';
		ch[pointerBefore + 4] = ' ';

		ch[pointer] = '-';
		ch[pointer + 4] = '>';
	}
}

int levelChoose()
{
	char peek = 0;		//用于防止玩家乱输入。
	static int number = 1;

	if (number > 1)
	{
		std::cin.ignore(100, '\n');
	}

	system("cls");

	int level = 0;
	while (level < 1)
	{
	LOOP1:
		std::cout << "乱输入要打屁屁哟!!!" << std::endl;
		std::cout << "您所要选择的关卡数：";

		//printf("peek:%d\n",peek);

		peek = std::cin.peek();
		if ((peek > 57 || peek < 49))
		{
			std::cin.ignore(10000, '\n');//	清空缓冲区数据。
			std::cout << "\n";
			goto LOOP1;
		}

		std::cin >> level;
	}

	number++;
	return (level);
}

void introduce()
{
	system("cls");
	printf("推箱子是一个来自日本的古老游戏，目的是在训练你的逻辑思考能力。\n");
	system("pause");

	system("cls");
	printf("在一个狭小的仓库中，要求把木箱放到指定的位置。\n");
	system("pause");

	system("cls");
	printf("稍不小心就会出现箱子无法移动或者通道被堵住的情况。\n");
	system("pause");

	system("cls");
	printf("所以需要巧妙的利用有限的空间和通道，合理安排移动的次序和位置，才能顺利的完成任务。\n");
	system("pause");
}

int weatherPass(int star[NUMBER][2], Box box[NUMBER], int I)
{
	int temp, tempStar;

	for (temp = 0; temp < I; temp++)
	{
		for (tempStar = 0; star[tempStar - 1][0] != -1; tempStar++)
		{
			if (box[temp].placeI == star[tempStar][0] && box[temp].placeJ == star[tempStar][1])
			{
				break;
			}
			else if (star[tempStar][0] != -1)
			{
				continue;
			}
			else if (star[tempStar][0] == -1)
			{
				return 0;//表示未成功。
			}

		}
	}
	return 1;			//表示成功

}

void voluationForStar(int star[NUMBER][2])
{
	int I, J;

	for (I = 0; I < NUMBER; I++)
	{
		for (J = 0; J < 2; J++)
		{
			star[I][J] = -1;
		}
	}
}