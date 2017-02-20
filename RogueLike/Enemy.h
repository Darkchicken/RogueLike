#pragma once
#include <string>
class Enemy
{
public:
	Enemy(std::string name, char tile, int level, int attack, int defense, int health, int exp);
	~Enemy();

	int attack();
	// returned int is experience gained
	int takeDamage(int attack);

	void setPosition(int x, int y);

	void getPosition(int &x, int &y);

	inline std::string getName() { return _name; }

	//gets ai move command (enemies press w, s, a ,d)
	char getMove(int playerX, int playerY);

	char getTile() { return _tile; }

private:
	// could be set for individual monster
	const int _attackRange = 5;
	std::string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;

	//position
	int _x;
	int _y;
	
	
};

