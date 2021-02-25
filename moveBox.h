#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>

#define SIZE 10		//�������ͼ��С��
#define NUMBER 10	//�궨�����������Ŀ��(���Ը�������Լ������ĵ�ͼ�����޸������������)��������Ϊ10������Ӧ�ù��ˡ���

//������ʾ����������࣬���붨�������������ǰ�棬�����������з���Ϊʲô��
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
	int placeI;		//��¼������
	int placeJ;		//��¼������

	Player();

	int move(int command);
	int push(int command, Box box[], int);
};


//�����Ĺ�������
Player::Player()
{
	placeI = -1;
	placeJ = -1;
}

//������Ĺ�������
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

	int temp = 0;//���ڼ���box�����ÿ��Ԫ�ء�
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

int gettingData(int smallSquare[SIZE][SIZE], int number, Player* player, Box box[NUMBER], int* I, int star[NUMBER][2]);		//���ڼ�����Ϸ����
void printMap(int smallSquare[SIZE][SIZE], Player player, Box box[NUMBER], int I);	//��ӡ��ͼ
int getCommand();//�����û����롣
void detect(Player* player, Box box[], int smallSquare[SIZE][SIZE], int* pointerFirst, int* pointerSecond, int command, int I);		//����̽�����ָ����ǰ������������ݡ�
int menu();		//�����˵�����
int levelChoose();//�ؿ�ѡ��
void introduce();	//��Ϸ����
void voluationForStar(int star[NUMBER][2]);
int weatherPass(int star[NUMBER][2], Box box[NUMBER], int);

int main()
{
	int smallSquare[SIZE][SIZE];		//��ͼ,0��ʾǽ�ڣ�1��ʾ���ӣ�2��ʾ��·��3��ʾ���4��ʾʤ���յ�

	Player player;		//�������(���)
	Box box[10];

	int I;		//���ڼ�¼��ͼ���ж��ٸ����ӡ�

	int star[NUMBER][2];//��¼�յ��λ�á�


LOOP1:

	I = 0;
	voluationForStar(star);//��ʼ�����ǵ�λ�á����ڼ����Ϸ�Ƿ�ͨ��

	int level = menu();					//�ڲ˵���ѡ��ؿ�����

	if (!gettingData(smallSquare, level, &player, box, &I, star))		//��ʼ����ͼ
	{
		goto LOOP1;
	}

	int pointerFirst = -1, pointerSecond = -1;		//���ڼ�¼ָ����ҳ���ǰ��������������ݡ�
	int command;		//���ڽ���������������
	while (1)
	{
		printMap(smallSquare, player, box, I);//��ӡ��ͼ��

		//ע�������ģ������ߵ�ʱ���ڼ������ʱ���õģ���ҿ��Բο�ѧϰѧϰ��(������õ������Կ��ܻ���Щ�鷳���������ַ�ʽ�����˾��ñȽϺá�)
		//std::cout << "̽�⣺" << pointerFirst << "  " << pointerSecond << std::endl;
		//std::cout << "���λ�ã�" << player.placeJ << "  " << player.placeI << std::endl;
		//int temp;
		/*
		for( temp = 0 ; temp < I ; temp++ )
		{
			std::cout << "��" << temp << "�����ӵ����꣺" << box[temp].placeJ << "   " << box[temp].placeI << std::endl;
		}
		*/

		command = getCommand();

		if (5 == command)
		{
			goto LOOP1;
		}
		else if (command > 0)		//�û������룬��������ȷ��
		{
			detect(&player, box, smallSquare, &pointerFirst, &pointerSecond, command, I);

			if (2 == pointerFirst || 4 == pointerFirst)		//ǰ����·��
			{
				player.move(command);
			}
			else if (1 == pointerFirst && 1 == pointerSecond)
			{
				;//���ǰ������������,�����Ʋ��������䴦��
			}
			else if (1 == pointerFirst && (2 == pointerSecond || 4 == pointerSecond))
			{
				player.push(command, box, I);//ǰ�������ӣ���ǰ��һ����·���ǿ϶�Ҫ���硣
			}
		}

		if (weatherPass(star, box, I))//����Ƿ�ͨ��
		{
			printMap(smallSquare, player, box, I);
			std::cout << "��ʤ���ˣ���ϲ��!!!" << std::endl;
			system("pause");
			goto LOOP1;
		}


	}


	return 0;
}

int gettingData(int smallSquare[SIZE][SIZE], int number, Player* player, Box box[NUMBER], int* I, int star[NUMBER][2])
{
	char gameLevel[12] = { 'N' , 'u' , 'm' , 'b' , 'e' , 'r' ,0 , '.' , 't' , 'x' , 't' , 0 };		//���ڼ�����Ϸ���ݡ�
	gameLevel[6] = number + 48;			//����ת��Ϊ�ַ��ͣ���Ҫͳһһ�¡�


	std::ifstream fileOfGettingGameData;

	fileOfGettingGameData.open(gameLevel);	//����Ϸ����

	if (!fileOfGettingGameData)
	{
		std::cout << "δ��⵽�ؿ�" << number << "�Ĵ���" << "\n��������ѡ��ؿ�ʱ�Ƿ�������ȷ��" << std::endl;
		system("pause");
		return 0;
	}
	/*
	else
	{
		std::cout << "�ؿ���ʼ���ɹ�" << std::endl;
		Sleep( 500 );
	}
	*/

	//��ʼ����ͼ����������Ϸ�ļ���
	int tempI, tempJ, temp = 0;//temp�����յ�ļ�����
	for (tempI = 0; tempI < SIZE; tempI++)
	{
		for (tempJ = 0; tempJ < SIZE; tempJ++)
		{
			fileOfGettingGameData >> smallSquare[tempI][tempJ];

			//����λ�õ�������
			if (3 == smallSquare[tempI][tempJ])
			{
				player->placeI = tempI;
				player->placeJ = tempJ;

				smallSquare[tempI][tempJ] = 2;
			}

			//����λ�õ�������
			if (1 == smallSquare[tempI][tempJ])
			{
				box[(*I)].placeI = tempI;
				box[(*I)].placeJ = tempJ;

				smallSquare[tempI][tempJ] = 2;

				(*I)++;
			}

			//�յ�λ�õ�������
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
	int tempI, tempJ, temp;//temp���ڼ�������box
	int weatherPrintBox = 0;	//0��ʾû�д�ӡ���ӣ�1��ʾ��ӡ�ˡ�

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
					printf("��");			//��ӡ���ӡ�
					weatherPrintBox = 1;
					break;
				}
			}

			if (tempI == player.placeI && tempJ == player.placeJ)
			{
				std::cout << "��";				//��ӡ���
			}
			else if (2 == smallSquare[tempI][tempJ] && 0 == weatherPrintBox)
			{
				std::cout << "  ";				//��ӡ��·��
			}
			else if (0 == smallSquare[tempI][tempJ])
			{
				std::cout << "��";				//��ӡǽ�ڡ�
			}
			else if (4 == smallSquare[tempI][tempJ] && 0 == weatherPrintBox)
			{
				std::cout << "��";				//��ӡ�յ㡣
			}
		}
		std::cout << "\n";
	}
}

int getCommand()
{
	int commandReturn = -1;		//��ʾû������

	switch (_getch())
	{
	case 'W':
	case 'w':
		commandReturn = 1;		//��ʾ����
		break;

	case 'A':
	case 'a':
		commandReturn = 2;		//��ʾ����
		break;

	case 'S':
	case 's':
		commandReturn = 3;		//��ʾ����
		break;

	case 'D':
	case 'd':
		commandReturn = 4;		//��ʾ����
		break;

	case 'B':
	case 'b':
		commandReturn = 5;		//��ʾ����ѡ�ؽ���
		break;

	case 10:
	case 13:
		commandReturn = 6;		//��ʾ�س�
		break;

	default:
		commandReturn = -2;		//��ʾ�û���������
		break;
	}

	return (commandReturn);
}

void detect(Player* player, Box box[], int smallSquare[SIZE][SIZE], int* pointerFirst, int* pointerSecond, int command, int I)
{
	int tempFirstI, tempFirstJ, tempSecondI, tempSecondJ;		//���ڼ�¼���λ�õ�ǰ����λ�õ����ꡣ
	int temp;		//���ڼ���box���ÿһ��Ԫ�ء�

	switch (command)
	{
	case 1:
		//������ҳ������������ķ�������꣬���ҽ��丳ֵ��
		tempFirstI = player->placeI - 1;
		tempFirstJ = player->placeJ;

		tempSecondI = player->placeI - 2;
		tempSecondJ = player->placeJ;

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//������Χδ������ͼ�������
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//��Χ������ͼ�����飬���䰴ǽ�ڼ��㡣
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

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//������Χδ������ͼ�������
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//��Χ������ͼ�����飬���䰴ǽ�ڼ��㡣
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

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//������Χδ������ͼ�������
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//��Χ������ͼ�����飬���䰴ǽ�ڼ��㡣
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

		if (tempFirstI >= 0 && tempFirstJ >= 0)		//������Χδ������ͼ�������
		{
			*pointerFirst = smallSquare[tempFirstI][tempFirstJ];
		}
		//��Χ������ͼ�����飬���䰴ǽ�ڼ��㡣
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
	static int level = 0;		//��¼��ѡ��Ĺؿ�����
	int command = 0;

	while (1)
	{
		system("cls");		//ʵ��������
		printf("**************************************\n");
		printf("             %c%c��ʼ��Ϸ             \n", ch[0], ch[4]);
		printf("**************************************\n");
		printf("             %c%cѡ��ؿ�             \n", ch[1], ch[5]);
		printf("**************************************\n");
		printf("             %c%c��Ϸ����             \n", ch[2], ch[6]);
		printf("**************************************\n");
		printf("             %c%c�˳���Ϸ             \n", ch[3], ch[7]);

		pointerBefore = pointer;
		command = getCommand();
		switch (command)
		{
			//���ϵ����
		case 1:
			if (0 == pointer)		//���������
			{
				pointer = 3;
			}
			else
			{
				pointer--;
			}
			break;

			//���µ����
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
					std::cout << "��û��ѡ���κιؿ�" << std::endl;
					system("pause");
					break;
				}
				else
				{
					return (level);
				}
			}
			else if (1 == pointer)			//��Ϸ�ؿ�ѡ��
			{
				level = levelChoose();
			}
			else if (2 == pointer)			//��Ϸ����
			{
				introduce();
			}
			else if (3 == pointer)
			{
				exit(0);		//��ʾ�˳�����
			}


			break;


		default:
			std::cout << "�������" << std::endl;
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
	char peek = 0;		//���ڷ�ֹ��������롣
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
		std::cout << "������Ҫ��ƨƨӴ!!!" << std::endl;
		std::cout << "����Ҫѡ��Ĺؿ�����";

		//printf("peek:%d\n",peek);

		peek = std::cin.peek();
		if ((peek > 57 || peek < 49))
		{
			std::cin.ignore(10000, '\n');//	��ջ��������ݡ�
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
	printf("��������һ�������ձ��Ĺ�����Ϸ��Ŀ������ѵ������߼�˼��������\n");
	system("pause");

	system("cls");
	printf("��һ����С�Ĳֿ��У�Ҫ���ľ��ŵ�ָ����λ�á�\n");
	system("pause");

	system("cls");
	printf("�Բ�С�ľͻ���������޷��ƶ�����ͨ������ס�������\n");
	system("pause");

	system("cls");
	printf("������Ҫ������������޵Ŀռ��ͨ�����������ƶ��Ĵ����λ�ã�����˳�����������\n");
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
				return 0;//��ʾδ�ɹ���
			}

		}
	}
	return 1;			//��ʾ�ɹ�

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