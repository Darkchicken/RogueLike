#pragma once
class Player
{
public:
	Player();
	~Player();

	void init(int level, int health, int attack, int defense, int experience);

	int attack();

	int takeDamage(int attack);
	
	void addExperience(int exp);

	void setPosition(int x, int y);

	void getPosition(int &x, int &y );

private:
	//stats
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;

	//position
	int _x;
	int _y;

};

