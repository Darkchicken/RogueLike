#pragma once

#include "Player.h"
#include "Level.h"
#include <string>


class GameManager
{
public:
	GameManager(std::string levelFile);
	~GameManager();

	void playGame();
	void playerMove();
private:
	Level _level;
	Player _player;
	

};

