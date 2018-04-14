#include <iostream>
#include <time.h>
#include <cstring>
#include <conio.h>
#include <windows.h>

using namespace std;

void Intro();
int RNG(int);

class Map
{
	public:
		string* map = new string[23];
		//Constructor
		Map()
		{
					//			 10		   20		 30		   40		 50		   60		 70		
					// 0123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567
			map[0]  = "##############################################################################";
			map[1]  = "#                                                                            #";
			map[2]  = "#                                                                            #";
			map[3]  = "#                                                                            #";
			map[4]  = "#                                                                            #";
			map[5]  = "#                                                                            #";
			map[6]  = "#                                                                            #";
			map[7]  = "#                                                                            #";
			map[8]  = "#                                                                            #";
			map[9]  = "#                                                                            #";
			map[10] = "#                                                                            #";
			map[11] = "#                                                                            #";
			map[12] = "#                                                                            #";
			map[13] = "#                                                                            #";
			map[14] = "#                                                                            #";
			map[15] = "#                                                                            #";
			map[16] = "#                                                                            #";
			map[17] = "#                                                                            #";
			map[18] = "#                                                                            #";
			map[19] = "#                                                                            #";
			map[20] = "#                                                                            #";
			map[21] = "#                                                                            #";
			map[22] = "##############################################################################";		
		}

		void Render()
		{

			system("CLS");
			for(int i = 0; i < 23; i++)
			{
				cout << map[i] << endl;
			}
			Sleep(100);	
		}
		void Render(int ms)
		{

			system("CLS");
			for(int i = 0; i < 23; i++)
			{
				cout << map[i] << endl;
			}
			Sleep(ms);	
		}		

};


class Enemy
{
	public:
		int x;
		int y;
		string character;

		Enemy()
		{
			x = RNG(20)+50;
			y = RNG(14)+4;	
			character = "a";
		}
		

		void DrawEnemy(Map map)
		{
			map.map[y].replace(x,1,character);
		}
		void MoveEnemy(Map map)
		{
			if(x > 1)
			{
				HideEnemy(map);
				x--;
				DrawEnemy(map);
			}			
		}
		void HideEnemy(Map map)
		{
			map.map[y].replace(x,1," ");
		}
		void deleteMe()
		{
			delete [] this;
		}

};


class Ninja
{
	public:
		int x;
		int y;
		Ninja()
		{
			x = 1;
			y = 14;
		}

		void Slash(Map map, Enemy *enemies[])
		{
			DrawNinjaSlash(map);
			for(int i = 0; i < 10; i++)
			{
				if(x+21 >= enemies[i]->x && x+9 <= enemies[i]->x && y+3 == enemies[i]->y)
				{
					enemies[i]->x = 0;
					enemies[i]->character = "#";
				}
			}
			map.Render(25);
			HideNinjaSlash(map);
			map.Render(25);
			DrawNinja(map);
			map.Render(25);
		}

		void DrawNinja(Map map)
		{
			//Height = 8
			map.map[y].replace( x,7, "    OOO");
			map.map[y+1].replace(x,6, "   OOO");
			map.map[y+2].replace(x,7, "  o | o");
			map.map[y+3].replace(x,9, "{} |/| {}");
			map.map[y+4].replace(x,6, "   /o\\");
			map.map[y+5].replace(x,8, " o/   \\o");
			map.map[y+6].replace(x,8, " /     \\");
			map.map[y+7].replace(x,11,"o[]     o[]");
		}
		void HideNinja(Map map)
		{
			map.map[y].replace( x,7, "       ");
			map.map[y+1].replace(x,6, "      ");
			map.map[y+2].replace(x,7, "       ");
			map.map[y+3].replace(x,9, "         ");
			map.map[y+4].replace(x,6, "      ");
			map.map[y+5].replace(x,8, "        ");
			map.map[y+6].replace(x,8, "        ");
			map.map[y+7].replace(x,11,"           ");	
		}
		void DrawNinjaSlash(Map map)
		{
			map.map[y].replace( x,7, "    OOO");
			map.map[y+1].replace(x,6, "   OOO");
			map.map[y+2].replace(x,7, "   O| >");
			map.map[y+3].replace(x,9, "   |/| {>");
					map.map[y+3].replace(x+9, 13, "o=[]::::::::>");
			map.map[y+4].replace(x,10,"   /o\\    ");
			map.map[y+5].replace(x,8, "    >  >");
			map.map[y+6].replace(x,8, "   /   \\");
			map.map[y+7].replace(x,11,"  o[]   o[]");
		}
		void HideNinjaSlash(Map map)
		{
			map.map[y+3].replace(x+9, 13, "             ");
		}

	void GetUserInput(Map map, Enemy *enemies[])
	{
		if (_kbhit())
		{
			switch(_getch())
			{
				case ' ':
					Slash(map, enemies);
					break;
				case 'w':
					if(y > 1)
					{
						HideNinja(map);
						y = y - 1;
						DrawNinja(map);
						map.Render(1);
					}

					break;
				case 'a':
					if(x > 1)
					{			
						HideNinja(map);
						x = x - 1;
						DrawNinja(map);
						map.Render(1);
					}		
					break;				
				case 's':
					if(y < 14)
					{
						HideNinja(map);
						y = y + 1;
						DrawNinja(map);
						map.Render(1);
					}			
					break;
				case 'd':
					if(x < 34)
					{
						HideNinja(map);
						x = x + 1;
						DrawNinja(map);
						map.Render(1);
					}
				
					break;				
				case 'c':
					system("CLS");
					exit(0);
					break;
			}
		}
	}
};




Map map;
Ninja ninja;
Enemy *enemies[10];
int numberOfEnemies = 10;

int main()
{
	srand(time(NULL));
	for(int i = 0; i < numberOfEnemies; i++)
	{
		enemies[i] = new Enemy();
	}

	Intro();
	_getch();
	while(true)
	{

		ninja.GetUserInput(map, enemies);
		ninja.DrawNinja(map);
		for(int i = 0; i < numberOfEnemies; i++)
		{
			enemies[i] -> DrawEnemy(map);
		}
		for(int i = 0; i < numberOfEnemies; i++)
		{
			enemies[i] -> MoveEnemy(map);
		}
		map.Render(100);
		
		bool checkIfEnd[numberOfEnemies];
		for(int i = 0; i < numberOfEnemies; i++)
		{
			if(enemies[i]-> x == 0 || enemies[i]-> x == 1)
			{
				checkIfEnd[i] = true;	
			}
		}


		bool allTrue = true;
		bool allFalse = true;
		for(int i = 0; i < numberOfEnemies; i++)
		{
			if(checkIfEnd[i])
			{
				allFalse = false;
			}
			else
			{
				allTrue = false;
			}
		}

		if(allTrue)
		{
			map.Render(100);
			cout << "\n\nlevel 1 complete";
			exit(0);
		}

	}
	
	
	return 0;
}

int RNG(int max)
{
	int randomNumber = rand() % max;
	return randomNumber;
}

void Intro()
{
	system("CLS");
	cout << "\n\n\n\n\n                            "
		 << "Welcome to Console Ninja.\n\n              "
		 << "Hack at the enemy characters until there are none left.\n\n                    "
		 << "Use the W,A,S,D keys to move your ninja. \n                      "
		 << "Press SPACEBAR to slash at the enemy.\n\n                      "
		 << "At any point press type c to exit.\n\n                     "
		 << "Press any key on the keyboard to begin.\n        \n                            "
		 << "Good luck, warrior.\n\n                                     ";
}
