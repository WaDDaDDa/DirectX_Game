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

	CreateButton("Ÿ��Ʋ��");
	CreateButton("ȯ�� ����");
	CreateButton("�� �� ���� ����");

	AllButtonColOff();

}