#include "PreCompile.h"
#include "TextArrow.h"


TextArrow::TextArrow()
{

}

TextArrow::~TextArrow()
{

}

void TextArrow::Start()
{
	Transform.SetLocalPosition({ 1240.0f , -680.0f , -500.0f });

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Intro");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineDirectory& Dir = Directorys[i];

 			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	Renderer->CreateAnimation("TextArrow", "TextArrow", 0.2f);
	Renderer->ChangeAnimation("TextArrow");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.5f);

}

void TextArrow::Update(float _Delta)
{

}