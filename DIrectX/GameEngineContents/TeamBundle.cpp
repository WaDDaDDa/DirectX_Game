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
	Recruitment->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());
	ButtonPos += ButtonYInter;

	Traning = GetLevel()->CreateActor<BundleButton>();
	Traning->SetButtonText("선수 영입");
	Traning->Transform.AddLocalPosition(ButtonPos);
	Traning->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());
	ButtonPos += ButtonYInter;

	Squad = GetLevel()->CreateActor<BundleButton>();
	Squad->SetButtonText("선수 영입");
	Squad->Transform.AddLocalPosition(ButtonPos);
	Squad->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());
	ButtonPos += ButtonYInter;

}

void TeamBundle::Update(float _Delta)
{

}
