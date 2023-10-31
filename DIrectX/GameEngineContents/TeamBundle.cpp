#include "PreCompile.h"
#include "TeamBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"

TeamBundle::TeamBundle()
{

}

TeamBundle::~TeamBundle()
{

}

void TeamBundle::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	Recruitment = GetLevel()->CreateActor<BundleButton>();
	Recruitment->SetButtonText("선수 영입");
	Recruitment->Transform.AddLocalPosition(ButtonPos);
	ButtonPos += ButtonYInter;
	Recruitment->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());

}

void TeamBundle::Update(float _Delta)
{

}
