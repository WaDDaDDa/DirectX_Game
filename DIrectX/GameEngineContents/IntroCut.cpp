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
		// ���徿 ����ϰ� ������.

		//{
		//	GameEngineDirectory Dir;
		//	Dir.MoveParentToExistsChild("GameEngineResources");
		//	Dir.MoveChild("ContentsResources");
		//	Dir.MoveChild("FolderTexture");
		//	// ���������� �Է��ؾ� ���� �������� �ε��Ҽ��ִ�.
		//	// Intro �ε��Ѵٰ� ġ�� Intro���� ������ �����ؾ��Ѵ�.
		//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		//	for (size_t i = 0; i < Directorys.size(); i++)
		//	{
		//		// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
		//		GameEngineDirectory& Dir = Directorys[i];

		//		GameEngineSprite::CreateFolder(Dir.GetStringPath());

		//	}

		//	GameEngineSprite::CreateSingle("cutscene1.png");
		//}

		//MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		//	MainSpriteRenderer->SetSprite("cutscene1.png");

		// �ִϸ��̼��� ����ϰ� ������
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