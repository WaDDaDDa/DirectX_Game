#include "PreCompile.h"
#include "PythonessSkillBomb.h"


PythonessSkillBomb::PythonessSkillBomb()
{

}

PythonessSkillBomb::~PythonessSkillBomb()
{

}

void PythonessSkillBomb::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Projectile);

	Renderer->CreateAnimation("PythonessSkillBombEffect", "PythonessAni", 0.2f , 54, 60, false);
	Renderer->ChangeAnimation("PythonessSkillBombEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);

	// �̺�Ʈ ����
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// �ñر� �����

			Att *= 1.0f;
			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
						}
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
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

void PythonessSkillBomb::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void PythonessSkillBomb::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
	}

	Transform.SetLocalPosition(Unit->Transform.GetWorldPosition());

	//�̺�Ʈ ���.
	if (TeamType::Blue == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
}