#pragma once
#include <vector>
#include <string>

#include "Player.h"
#include "Enemy.h"
class Level
{
public:
	Level();
	~Level();
	
	void load(std::string fileName, Player &player);

	void print();

	void movePlayer(char input, Player &player);
	void updateMonster(Player &player);
	
	char getTile(int x, int y);
	void setTile(int x, int y, char tile);
private:
	//each element holds a row of the level
	std::vector<std::string> _levelData;
	std::vector<Enemy> _enemies;

	void processPlayerMove(Player &player, int targetX, int targetY);
	void processEnemyMove(Player &player,int enemyIndex, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);
};

