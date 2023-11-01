#include "PreCompile.h"
#include "GameBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

GameBundle::GameBundle()
{

}

GameBundle::~GameBundle()
{

}

void GameBundle::Start()
{
	ButtonBundle::Start();

	CreateButton("Ã¨ÇÇ¾ð Á¤º¸");

	AllButtonColOff();

}