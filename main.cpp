#include "Map.h"
#include <vector>


int main()
{
	Map GameMap;
	int map[MAPY][MAPX] ;
	
	bool quit = true;


	while (quit)
	{
		quit = GameMap.goingGame(map);
	}
	
	system("pause");

	return 0;
}