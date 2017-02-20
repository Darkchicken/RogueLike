#include "Player.h"
#include <random>
#include <ctime>
#include <iostream>


Player::Player()
{
	_x = 0;
	_y = 0;
}


Player::~Player()
{
}

void Player::init(int level, int health, int attack, int defense, int experience)
{
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}

int Player::attack()
{
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

int Player::takeDamage(int attack)
{
	attack -= _defense;
	//check if attack deals damage
	if (attack > 0)
	{
		_health -= attack;
		//check if dead
		if (_health <= 0)
		{
			return 1;
		}
	}

	return 0;
}

void Player::addExperience(int exp)
{
	_experience += exp;
	// level up as many times as possible with gained exp
	while(_experience > 50)
	{
		std::cout << "\nLeveled up!";		
		_experience -= 50;
		_attack += 10;
		_defense += 5;
		_health += 10;
		_level++;
		system("PAUSE");
	}
}

void Player::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}
