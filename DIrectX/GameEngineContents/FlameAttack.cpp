#include "PreCompile.h"
#include "FlameAttack.h"


FlameAttack::FlameAttack()
{

}

FlameAttack::~FlameAttack()
{

}

void FlameAttack::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Projectile);

	Renderer->CreateAnimation("FlameAttackEffect", "PyromancerEffect", 0.1f , 29, 37, false);
	Renderer->ChangeAnimation("FlameAttackEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Projectile) });

	// 사운드
	GameEngineSound::SoundPlay("Fire bolt 17.WAV");

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// 궁극기 대미지
			float Att = Unit->GetUnitAttack();
			Att *= 1.0f;
			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att, Unit);
						}
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att, Unit);
						}
					});
			}
		};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

}

void FlameAttack::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void FlameAttack::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
	}

	//이벤트 사용.
	if (TeamType::Blue == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
}