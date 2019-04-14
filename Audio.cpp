#include <iostream>
using namespace std;
#include "Audio.h"
#include <Windows.h>
#include <mmsystem.h>

Game::Game()
{
	PlaySound(TEXT("solid.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//PlaySound(NULL, 0, 0);
}

Game::~Game()
{

}
