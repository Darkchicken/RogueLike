#include "Enemy.h"
#include <random>
#include <ctime>


Enemy::Enemy(std::string name, char tile, int level, int attack, int defense, int health, int exp)
{
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = exp;
}


Enemy::~Enemy()
{
}

int Enemy::attack()
{
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack)
{
	attack -= _defense;
	//check if attack deals damage
	if (attack > 0)
	{
		_health -= attack;
		//check if dead
		if (_health <= 0)
		{
			return _experienceValue;
		}
	}

	return 0;
}

char Enemy::getMove(int playerX, int playerY)
{
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> moveRoll(0,6);
	int distance;
	int dX = _x - playerX;
	int dY = _y - playerY;
	int adx = abs(dX);
	int ady = abs(dY);
	distance = adx+ady;
	if (distance < _attackRange)
	{
		// move along x axis
		if (adx < ady)
		{
			if (dX > 0)
			{
				return 'a';
			}
			else
			{
				return 'd';
			}
		}
		//move along y axis
		else
		{
			if (dY > 0)
			{
				return 'w';
			}
			else
			{
				return 's';
			}
		}
	}

	int randomMove = moveRoll(randomEngine);
	switch (randomMove)
	{
	case 0:
		return 'a';
		break;
	case 1:
		return 'w';
		break;
	case2:
		return 's';
		break;
	case 3:
		return 'd';
		break;
	default:
		return '.';
		break;
	}
}

void Enemy::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Enemy::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}
