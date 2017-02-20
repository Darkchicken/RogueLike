#include "GameManager.h"

#include <iostream>
#include <conio.h>
// constructor is setup
GameManager::GameManager(std::string levelFile)
{
	// set initial player properties
	_player.init(1, 100, 10, 10 ,0);
	// load level
	_level.load(levelFile, _player);
	//_level.print();
	//system("PAUSE");
}


GameManager::~GameManager()
{
}

void GameManager::playGame()
{
	bool isDone = false;
	//game loop
	while (!isDone)
	{
		_level.print();
		playerMove();
		_level.updateMonster(_player);
		
	}
}

void GameManager::playerMove()
{
	char input;
	std::cout << "Enter a move command:";
	input = _getch();
	_level.movePlayer(input, _player);
}
