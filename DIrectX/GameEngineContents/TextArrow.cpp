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
	Transform.SetLocalPosition({ 1240.0f , -680.0f});

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Intro");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineDirectory& Dir = Directorys[i];

 			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	Renderer->CreateAnimation("TextArrow", "TextArrow", 0.2f);
	Renderer->ChangeAnimation("TextArrow");
	//Renderer->SetImageScale({ 10.0f, 100.0f });

	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.5f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });


}

void TextArrow::Update(float _Delta)
{
	
}