#include "PreCompile.h"

#include "IntroCut.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

IntroCut::IntroCut()
{

}

IntroCut::~IntroCut()
{

}

void IntroCut::Start()
{
	{
		// 한장씩 사용하고 싶으면.

		//{
		//	GameEngineDirectory Dir;
		//	Dir.MoveParentToExistsChild("GameEngineResources");
		//	Dir.MoveChild("ContentsResources");
		//	Dir.MoveChild("FolderTexture");
		//	// 상위폴더를 입력해야 하위 폴더들을 로드할수있다.
		//	// Intro 로드한다고 치면 Intro상위 폴더를 지정해야한다.
		//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		//	for (size_t i = 0; i < Directorys.size(); i++)
		//	{
		//		// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
		//		GameEngineDirectory& Dir = Directorys[i];

		//		GameEngineSprite::CreateFolder(Dir.GetStringPath());

		//	}

		//	GameEngineSprite::CreateSingle("cutscene1.png");
		//}

		//MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		//	MainSpriteRenderer->SetSprite("cutscene1.png");

		// 애니메이션을 사용하고 싶으면
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();

		MainSpriteRenderer->CreateAnimation("Intro", "Intro", 1.0f);
		MainSpriteRenderer->ChangeAnimation("Intro");
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	MainSpriteRenderer->Transform.SetLocalScale(WindowScale);

	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void IntroCut::Update(float _Delta)
{
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}
}