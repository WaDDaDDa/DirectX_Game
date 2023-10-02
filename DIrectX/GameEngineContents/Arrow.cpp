#include "PreCompile.h"
#include "Arrow.h"


Arrow::Arrow()
{

}

Arrow::~Arrow()
{

}

void Arrow::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Projectile);

	Renderer->SetSprite("Arrow.png");
	Renderer->AutoSpriteSizeOn();

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
							AttackOn = true;
							LifeTime = 2.0f;
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
							EnemyUnit = reinterpret_cast<GameUnit*>(_Collision[i]->GetActor());
							Pos = Transform.GetWorldPosition() - EnemyUnit->Transform.GetWorldPosition();
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
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
							EnemyUnit = reinterpret_cast<GameUnit*>(_Collision[i]->GetActor());
							Pos = Transform.GetWorldPosition() - EnemyUnit->Transform.GetWorldPosition();

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

void Arrow::Update(float _Delta)
{
	LifeTime -= _Delta;


	if (0.0f >= LifeTime)
	{
		Death();
		return;
	}

	if (true == AttackOn && 0.0f >= LifeTime )
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