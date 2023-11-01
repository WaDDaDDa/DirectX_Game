#include "PreCompile.h"
#include "BattleBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

BattleBundle::BattleBundle()
{

}

BattleBundle::~BattleBundle()
{

}

void BattleBundle::Start()
{
	ButtonBundle::Start();

	CreateButton("일정");
	CreateButton("순위표");

	AllButtonColOff();

}