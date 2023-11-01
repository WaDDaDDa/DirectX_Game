#include "PreCompile.h"
#include "SystemBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

SystemBundle::SystemBundle()
{

}

SystemBundle::~SystemBundle()
{

}

void SystemBundle::Start()
{
	ButtonBundle::Start();

	CreateButton("타이틀로");
	CreateButton("환경 설정");
	CreateButton("내 팀 정보 수정");

	AllButtonColOff();

}