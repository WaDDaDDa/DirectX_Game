#include "PreCompile.h"
#include "PythonessHeal.h"


PythonessHeal::PythonessHeal()
{

}

PythonessHeal::~PythonessHeal()
{

}

void PythonessHeal::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Projectile);

	Renderer->CreateAnimation("PythonessHeal", "PythonessAni", 0.2f, 25, 28, true);
	Renderer->CreateAnimation("PythonessHeal2", "PythonessAni", 0.1f, 39, 49, false);
	Renderer->ChangeAnimation("PythonessHeal");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);


	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// 궁극기 대미지
			float Att = Unit->GetUnitAttack();
			Att *= 1.0f;
			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							EnemyUnit = reinterpret_cast<GameUnit*>(_Collision[i]->GetActor());

							if (true == EnemyUnit->HealTarget)
							{
								AttackOn = true;
								LifeTime = 2.0f;
								Renderer->ChangeAnimation("PythonessHeal2");
								reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->HealHP(Att);
								Pos = Transform.GetWorldPosition() - EnemyUnit->Transform.GetWorldPosition();
								Col->Off();
								EnemyUnit->HealTarget = false;
							}

						}
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							EnemyUnit = reinterpret_cast<GameUnit*>(_Collision[i]->GetActor());

							if (true == EnemyUnit->HealTarget)
							{
								AttackOn = true;
								LifeTime = 2.0f;
								Renderer->ChangeAnimation("PythonessHeal2");
								reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->HealHP(Att);
								Pos = Transform.GetWorldPosition() - EnemyUnit->Transform.GetWorldPosition();
								Col->Off();
								EnemyUnit->HealTarget = false;
							}
							
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

void PythonessHeal::Update(float _Delta)
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
		Transform.SetLocalPosition(EnemyUnit->Transform.GetWorldPosition());
		Transform.SetWorldRotation(float4::ZERO);
		return;
	}

	Transform.AddLocalPosition(Dir * Speed * _Delta);

	//이벤트 사용.
	if (TeamType::Blue == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
}