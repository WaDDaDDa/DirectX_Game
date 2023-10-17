#include "PreCompile.h"
#include "BanPickCard.h"
#include "GameUnitStatus.h"

float BanPickCard::XInter = 0.0f;


BanPickCard::BanPickCard()
{

}

BanPickCard::~BanPickCard()
{

}

void BanPickCard::Start()
{
	UI_Button::Start();

	{
		// �̱� ��������Ʈ �ε�
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Stadium\\Unit_Icon");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		// �ʻ�ȭ �ε�
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

	// Card ���
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("BanPickCard_Null", "BanPick", 0.1f, 15, 15, false);
	Renderer->CreateAnimation("BanPickCard_Blue", "BanPick", 0.1f, 9, 9, false);
	Renderer->CreateAnimation("BanPickCard_Red", "BanPick", 0.1f, 10, 10, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	//Renderer->SetPivotType(PivotType::Bottom);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	Renderer->ChangeAnimation("BanPickCard_Null");

	SetButtonColScale(ColScale);

	Transform.AddLocalPosition(StartPos);

	// �̺�Ʈ ����
	ColEvent.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// ó���ѹ� ����.
			if (false == IsSelect)
			{
				UnitImage->ChangeAnimation(GetUnitName() += "_Idle");
			}
		};

	ColEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// Ŀ�� �ö��ִ� �� ����.
			if (GameEngineInput::IsDown(VK_LBUTTON, this))
			{
				UnitImage->ChangeAnimation(GetUnitName() += "_Att");
				IsSelect = true;
			}
		};

	ColEvent.Exit = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// Ŀ�� �ö��ִٰ� ���������� ����.
			if (false == IsSelect)
			{
				UnitImage->ChangeAnimation(GetUnitName() += "_Stay");
			}

		};
}

void BanPickCard::LevelStart(GameEngineLevel* _PrevLevel)
{
	XInter = 0.0f;
}

void BanPickCard::Init(const GameUnitStatus& _Status)
{
	UnitName = _Status.UnitName;

	// Unit�̹���
	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitImage->CreateAnimation(GetUnitName() += "_Stay", GetUnitName() += "Ani", 0.2f, 0, 0, false);
	UnitImage->CreateAnimation(GetUnitName() += "_Idle", GetUnitName() += "Ani", 0.2f, 0, 4, true);
	UnitImage->CreateAnimation(GetUnitName() += "_Att", GetUnitName() += "Ani", 0.2f, 13, 16, false);
	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition(UnitImagePos);
	UnitImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitImage->ChangeAnimation(GetUnitName() += "_Stay");

	Transform.AddLocalPosition({ XInter, 0.0f });

	XInter += 80.0f;

}

void BanPickCard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BanPickCard::IdleStart()
{

}

void BanPickCard::IdleUpdate(float _Delta)
{

}

void BanPickCard::StayStart()
{

}

void BanPickCard::StayUpdate(float _Delta)
{
	
}

void BanPickCard::ClickStart()
{

}

void BanPickCard::ClickUpdate(float _Delta)
{

}
