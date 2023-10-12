#include "PreCompile.h"
#include "PythonessAttack.h"


PythonessAttack::PythonessAttack()
{

}

PythonessAttack::~PythonessAttack()
{

}

void PythonessAttack::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Projectile);

	Renderer->CreateAnimation("PythonessAttack", "PythonessAni", 0.2f, 21, 24, true);
	Renderer->CreateAnimation("PythonessAttack2", "PythonessAni", 0.2f, 33, 38, false);
	Renderer->ChangeAnimation("PythonessAttack");
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
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							AttackOn = true;
							LifeTime = 2.0f;
							Renderer->ChangeAnimation("PythonessAttack2");
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
							Renderer->ChangeAnimation("PythonessAttack2");
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

void PythonessAttack::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


void PythonessAttack::Update(float _Delta)
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
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
}