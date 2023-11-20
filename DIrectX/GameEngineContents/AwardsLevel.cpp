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

	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
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
	// ����Ʈ����Ʈ - ���̵�ƿ�
	std::shared_ptr<Awards> NewIntro = CreateActor<Awards>();

	std::shared_ptr<class FadeEffect> FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
	FadeInEffect->SetFadeIn();
}

void AwardsLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}