// RogueLike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>

#include "GameManager.h"


int main()
{
	GameManager gameManager("Level1.txt");
	gameManager.playGame();
    return 0;
}

