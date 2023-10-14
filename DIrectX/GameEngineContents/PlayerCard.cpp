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
	Transform.AddLocalPosition({0.0f, 0.0f, 100.0f});

	// Card 틀
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("PlayerCardBlue", "PlayerCard", 0.1f, 2, 2, false);
	Renderer->CreateAnimation("PlayerCardRed", "PlayerCard", 0.1f, 6, 6, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	// Unit이미지
	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitImage->SetSprite(Unit->GetUnitName() += "_Icon.png");
	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition(UnitImagePos);
	UnitImage->SetPivotType(PivotType::Bottom);
	UnitImage->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	// atticon
	AttIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	AttIcon->SetSprite("attack_icon.png");
	AttIcon->AutoSpriteSizeOn();
	AttIcon->SetAutoScaleRatio(2.0f);
	AttIcon->Transform.AddLocalPosition(AttIconPos);
	AttIcon->SetPivotType(PivotType::Bottom);
	AttIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	// deficon
	DefIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	DefIcon->SetSprite("armor_icon.png");
	DefIcon->AutoSpriteSizeOn();
	DefIcon->SetAutoScaleRatio(2.0f);
	DefIcon->Transform.AddLocalPosition(DefIconPos);
	DefIcon->SetPivotType(PivotType::Bottom);
	DefIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });


	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	if (TeamType::Blue == Unit->MyTeam)
	{
		Transform.AddLocalPosition({ -HalfWindowScale.X + 79.0f, StartY + BlueYInter });

		Renderer->ChangeAnimation("PlayerCardBlue");

		CreateStatus();

		BlueYInter -= 160.0f;

	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Transform.AddLocalPosition({ HalfWindowScale.X - 79.0f , StartY + RedYInter });

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