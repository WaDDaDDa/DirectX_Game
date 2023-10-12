#include "PreCompile.h"
#include "PlayerCard.h"
#include "GameUnit.h"
#include "PlayerCard_Status.h"

float PlayerCard::BlueYInter = 0.0f;
float PlayerCard::RedYInter = 0.0f;

PlayerCard::PlayerCard()
{

}

PlayerCard::~PlayerCard()
{

}

void PlayerCard::Start()
{
	{
		// 싱글 스프라이트 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Stadium\\Unit_Icon");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Archer_Icon.png");
		GameEngineSprite::CreateSingle("Knight_Icon.png");
		GameEngineSprite::CreateSingle("Monk_Icon.png");
		GameEngineSprite::CreateSingle("Fighter_Icon.png");
		GameEngineSprite::CreateSingle("Ninja_Icon.png");
		GameEngineSprite::CreateSingle("Priest_Icon.png");
		GameEngineSprite::CreateSingle("Pyromancer_Icon.png");
		GameEngineSprite::CreateSingle("Pythoness_Icon.png");
		GameEngineSprite::CreateSingle("Swordman_Icon.png");
	}
}

void PlayerCard::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayerCard::CreateStatus()
{
	GetLevel()->CreateActor<PlayerCard_Status>()->Setting(GetDynamic_Cast_This<PlayerCard>());
}


void PlayerCard::Init()
{
	// Card 틀
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("PlayerCardBlue", "PlayerCard", 0.1f, 2, 2, false);
	Renderer->CreateAnimation("PlayerCardRed", "PlayerCard", 0.1f, 6, 6, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);

	//// Status 틀
	//Renderer2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	//Renderer2->CreateAnimation("PlayerCardBlueStatus", "PlayerCard", 0.1f, 0, 0, false);
	//Renderer2->CreateAnimation("PlayerCardRedStatus", "PlayerCard", 0.1f, 1, 1, false);
	//Renderer2->AutoSpriteSizeOn();
	//Renderer2->SetAutoScaleRatio(2.0f);

	// Unit이미지
	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitImage->SetSprite(Unit->GetUnitName() += "_Icon.png");
	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition({ -45.0f,0.0f });


	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	if (TeamType::Blue == Unit->MyTeam)
	{
		Transform.SetLocalPosition({ -HalfWindowScale.X + 79.0f, StartY + BlueYInter });

		Renderer->ChangeAnimation("PlayerCardBlue");

		CreateStatus();

		BlueYInter -= 160.0f;

	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Transform.SetLocalPosition({ HalfWindowScale.X - 79.0f , StartY + RedYInter });

		Renderer->ChangeAnimation("PlayerCardRed");

		CreateStatus();

		RedYInter -= 160.0f;

	}
}

void PlayerCard::Update(float _Delta)
{

}

void PlayerCard::LevelEnd(GameEngineLevel* _NextLevel)
{

}