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

	CreateButton("���� ����");
	CreateButton("�Ʒ�");
	CreateButton("������");

	AllButtonColOff();

}