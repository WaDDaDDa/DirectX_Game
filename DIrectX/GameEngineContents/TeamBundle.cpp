#include "PreCompile.h"
#include "TeamBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"
#include "PlayerRecruitmentUI.h"

TeamBundle::TeamBundle()
{

}

TeamBundle::~TeamBundle()
{

}

void TeamBundle::Start()
{
	ButtonBundle::Start();

	Button1 = CreateButton("���� ����");
	Button2 = CreateButton("�Ʒ�");
	Button3 = CreateButton("������");

	AllButtonColOff();

}

void TeamBundle::Update(float _Delta)
{
	ButtonBundle::Update(_Delta);

	if (true == Button1->GetIsClick())
	{
		GetLevel()->CreateActor<PlayerRecruitmentUI>();
	}
	
}
