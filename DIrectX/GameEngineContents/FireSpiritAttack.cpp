#include "PreCompile.h"
#include "FireSpiritAttack.h"


FireSpiritAttack::FireSpiritAttack()
{

}

FireSpiritAttack::~FireSpiritAttack()
{

}

void FireSpiritAttack::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Projectile);

	Renderer->CreateAnimation("FireSpiritAttack", "FireSpiritEffect", 0.2f, 12, 14, true);
	Renderer->CreateAnimation("FireSpiritAttack2", "FireSpiritEffect", 0.2f, 15, 17, false);
	Renderer->ChangeAnimation("FireSpiritAttack");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Projectile) });

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// 궁극기 대미지
			float Att = Unit->Att;
			Att *= 0.4f;
			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							AttackOn = true;
							LifeTime = 2.0f;
							Renderer->ChangeAnimation("FireSpiritAttack2");
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
							EnemyUnit = reinterpret_cast<GameUnit*>(_Collision[i]->GetActor());
							Pos = Transform.GetWorldPosition() - EnemyUnit->Transform.GetWorldPosition();
							Col->Off();
						}
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							AttackOn = true;
							LifeTime = 2.0f;
							Renderer->ChangeAnimation("FireSpiritAttack2");
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
							EnemyUnit = reinterpret_cast<GameUnit*>(_Collision[i]->GetActor());
							Pos = Transform.GetWorldPosition() - EnemyUnit->Transform.GetWorldPosition();

							Col->Off();
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

void FireSpiritAttack::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void FireSpiritAttack::Update(float _Delta)
{
	LifeTime -= _Delta;


	if (0.0f >= LifeTime)
	{
		Death();
		return;
	}

	if (true == AttackOn && true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}

	if (true == AttackOn)
	{
		Transform.SetLocalPosition(EnemyUnit->Transform.GetWorldPosition() + Pos);
		return;
	}

	Transform.AddLocalPosition(Dir * Speed * _Delta);
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