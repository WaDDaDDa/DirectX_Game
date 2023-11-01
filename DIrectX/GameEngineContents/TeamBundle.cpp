#include "PreCompile.h"
#include "TeamBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

TeamBundle::TeamBundle()
{

}

TeamBundle::~TeamBundle()
{

}

void TeamBundle::Start()
{
	ButtonBundle::Start();

	CreateButton("선수 영입");
	CreateButton("훈련");
	CreateButton("선수단");

	AllButtonColOff();

}