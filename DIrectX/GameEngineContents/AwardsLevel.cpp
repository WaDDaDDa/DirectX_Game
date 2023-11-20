#include "PreCompile.h"
#include "AwardsLevel.h"
#include "Awards.h"
#include "UI_Mouse.h"
#include <GameEngineCore/FadePostEffect.h>
#include "EnemyInfo.h"


AwardsLevel::AwardsLevel()
{

}

AwardsLevel::~AwardsLevel()
{

}

void AwardsLevel::Start()
{
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	CreateActor<UI_Mouse>();
}

void AwardsLevel::Update(float _Delta)
{

}

void AwardsLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// 포스트이펙트 - 페이드아웃
	std::shared_ptr<Awards> NewIntro = CreateActor<Awards>();

	std::shared_ptr<class FadeEffect> FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
	FadeInEffect->SetFadeIn();
}

void AwardsLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}