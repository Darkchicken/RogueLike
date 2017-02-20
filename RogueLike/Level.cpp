#include "Level.h"

//gets data from file
#include <fstream>
#include <iostream>

Level::Level()
{
}


Level::~Level()
{
}

void Level::load(std::string fileName, Player &player)
{
	std::ifstream file;
	//open file
	file.open(fileName);
	//check if file exists
	if (file.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}
	

	std::string line;
	//gets line from file, stores in line
	while (getline(file, line))
	{
		//adds line to level data
		_levelData.push_back(line);
	}
	//not necessary, but good practice
	file.close();

	//process level
	char tile;
	//loop through each row
	for (int i = 0; i < _levelData.size(); i++)
	{
		// loop through each char in current row
		for (int j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];
			switch (tile)
			{
				
				case '@': //player
					// set position to current x, y
					player.setPosition(j,i);
					break;
				//handle enemies
				case 'S': //snake
					_enemies.push_back(Enemy("Snake", tile, 1,3,1,10,10));
					_enemies.back().setPosition(j, i);
					break;
				case 'G': //Goblin
					_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 50));
					_enemies.back().setPosition(j, i);
					break;
				case 'O': //ogre
					_enemies.push_back(Enemy("Ogre", tile, 4,20,20,200,500));
					_enemies.back().setPosition(j, i);
					break;
				case 'B': //bandit
					_enemies.push_back(Enemy("Bandit", tile, 3, 15 ,10, 100, 250));
					_enemies.back().setPosition(j, i);
					break;
				case 'D': //dragon
					_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
					_enemies.back().setPosition(j, i);
					break;

				default:
					break;

			}
		}
	}
}

void Level::print()
{
	//clear screen
	system("cls");
	//for each row in vector
	for (std::string row : _levelData)
	{
		//print the string (must convert to c_str)
		std::cout << row << std::endl;
	}

	std::cout << std::endl;
}

void Level::movePlayer(char input, Player &player)
{
	int playerX, playerY;
	//overrides input with new values
	player.getPosition(playerX, playerY);
	switch (input)
	{
	case 'w':
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':
	case 'S':
		// check tile right below player
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':
	case 'A':
		// check tile to left of player
		processPlayerMove(player, playerX-1, playerY);
		break;
	case 'd':
	case 'D':
		// check tile to right of player
		processPlayerMove(player, playerX+1, playerY);
		break;
	default:
		std::cout << "Invalid input" << std::endl;
		system("PAUSE");
		break;

	}
}

void Level::updateMonster(Player &player)
{
	char aiMove;
	int playerX, playerY;
	int enemyX, enemyY;
	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);
		aiMove = _enemies[i].getMove(playerX, playerY);

		switch (aiMove)
		{
		case 'w':
			processEnemyMove(player,i, enemyX, enemyY - 1);
			break;
		case 's':
			// check tile right below player
			processEnemyMove(player,i, enemyX, enemyY + 1);
			break;
		case 'a':
			// check tile to left of player
			processEnemyMove(player,i, enemyX - 1, enemyY);
			break;
		case 'd':
			// check tile to right of player
			processEnemyMove(player,i, enemyX + 1, enemyY);
			break;
		default:
			//dont move
			break;
		}
	}
}

char Level::getTile(int x, int y)
{
	return  _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY)
{
	int playerX, playerY;
	//overrides input with new values
	player.getPosition(playerX, playerY);
	// check tile right above player
	char moveTile = getTile(targetX, targetY);
	switch (moveTile)
	{
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;

		
	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int playerX, playerY;
	int enemyX, enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	//overrides input with new values
	player.getPosition(playerX, playerY);
	// check tile right above player
	char moveTile = getTile(targetX, targetY);
	switch (moveTile)
	{
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '#':
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::battleMonster(Player &player, int targetX, int targetY)
{
	int enemyX, enemyY;
	int attackRoll;
	
	for (int i = 0; i <  _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);
		if (targetX == enemyX && targetY == enemyY)
		{
			//battle
			attackRoll = player.attack();
			std::cout << "\nPlayer attacked "<< _enemies[i].getName() << " with a roll of "<< attackRoll<<std::endl;
			int attackResult = _enemies[i].takeDamage(attackRoll);
			//if enemy died
			if (attackResult != 0)
			{
				setTile(targetX, targetY, '.');
				print();
				std::cout << _enemies[i].getName() << " died!"<<std::endl;

				//remove enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				
				system("PAUSE");
				player.addExperience(attackResult);
				
				return;
			}
			attackRoll = _enemies[i].attack();
			std::cout << _enemies[i].getName() << " attacked Player with a roll of " << attackRoll << std::endl;
			system("PAUSE");
			attackResult = player.takeDamage(attackRoll);
			//if player died
			if (attackResult != 0)
			{
				int playerX, playerY;
				player.getPosition(playerX, playerY);
				setTile(playerX, playerY, 'X');
				print();
				std::cout << "YOU DIED!!!" << std::endl;
				system("PAUSE");
				
				exit(0);
			}
			return;
		}
		
	}
}
