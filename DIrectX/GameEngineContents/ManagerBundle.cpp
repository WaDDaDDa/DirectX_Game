#include "PreCompile.h"
#include "ManagerBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

ManagerBundle::ManagerBundle()
{

}

ManagerBundle::~ManagerBundle()
{

}

void ManagerBundle::Start()
{
	ButtonBundle::Start();

	CreateButton("역사");
	CreateButton("소식함");

	AllButtonColOff();

}

void ManagerBundle::Update(float _Delta)
{
	ButtonBundle::Update(_Delta);

}
